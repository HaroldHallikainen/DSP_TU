/*******************************************************************************
  Main Source File

  Company:
   W6IWI.ORG
  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <stdio.h>                      // sprintf, etc.
#include <string.h>                     // strlen, etc.
#include "definitions.h"                // SYS function prototypes
#include "PwmAudioOut.h"                // Convert floating sample to PWM duty cycle
#include "dds.h"                        // Generate next sample via Direct Digital Synthesis
#include "biquad.h"                     // biquad filters. Includes typedef for smp_type
#include "DynamicThreshold.h"           // Calculates threshold based on max mark and space levels
#include "agc.h"                        // Input automatic gain control
#include "main.h"
#include "display.h"
#include "xyScope.h"
#include "AfskGen.h" 
#include "BaudotUart.h"
#include "PollSwitchesLeds.h"           // Go poll the front panel
#include "PollEncoder.h"                // Poll the quadrature encoder
#include "UserConfig.h"                 // Tone frequencies, etc.
#include "filters.h"                    // Set up filters and modify based on button presses
#include "AutostartKos.h"               // Handle autostart and KOS

static void MyTimer2Isr(uint32_t intCause, uintptr_t context);

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

// Globals 
volatile int16_t Timer2TimeoutCounter=0; // Derive 8 kHz from timer 2 80 kHz - Decremented by MyTimer2Isr.
int16_t FpPollCounter=0;                // Decrements at 8 kHz telling us when to poll switches and LEDs.
// Audio samples at various stages
uint16_t AdcSample;         // Raw sample from ADC. Converted to AdcSamplef for calculations.
smp_type samplef, TestSamplef, MarkSample, SpaceSample, MarkDemodOut, SpaceDemodOut, DiscrimOut, DdsOut, Threshold;  // These were originally in main but seemed to get corrupted
// What drives the audio output. Usually dds (AFSK tone), but others for debug.  
enum {NONE,ADC, AGC, INPUT_BPF, LIMITER, MARK_FILTER_OUT, SPACE_FILTER_OUT, MARK_DEMOD_OUT, SPACE_DEMOD_OUT, DISCRIM, DDS, THRESHOLD, DISCRIM_LESS_THRESHOLD} AudioOut=DDS;

// Incoming ADC samples converted to smp_type (samplef) then passed thru options to tone filters)
// int UseInputBpf=FALSE;
// int UseLimiter=FALSE;
// int UseAgc=TRUE;


#define UseUartDebug
#ifdef UseUartDebug
  char StringBuf[100];
  int DebugCounter=0;
#endif

int main ( void ){
  int n;
  int MarkHoldTimer=0;        // How long 'til we mark hold
  /* Initialize all modules */
  SYS_Initialize ( NULL );    // Run init code generated by Harmony
  TMR2_CallbackRegister(MyTimer2Isr,0);  // Function to call on timer 2 overflow
  TMR2_Start();               // Timer for 80 kHz PWM output
  OCMP1_Enable();             // PWM generator for audio   
  DynamicThresholdInit();     // Set up LPF used in dynamic threshold
  LoadDefaultConfig();        // Load default user config (tone freuqncies, etc.))
  FiltersInit();              // Initialize all biquads
  AgcInit();                  // Set up automatic gain control
  DisplayInit();         // Initialize display and related fifo
  AudioPwmSet(0.0);           // Initialize PWM to 50% duty cycle representing 0.0.
  ADCHS_ChannelConversionStart(2); // Start a first ADC conversion
  AfskGenInit();      // Initialize a low pass filter between loop current sample and DDS.
  DisplayClear();
  while ( true ){
    if(Timer2TimeoutCounter<1){        // We have timed out 10 times, so it has been 125 us
      IDLEn_Set();                  // CPU not idle, so set RE7 so we can time it 
      // CLRWDT;                     // Clear the watchdog timer
      FpPollCounter--;                // Decrement at 8 kHz so we can poll front panel now and then
      Timer2TimeoutCounter+=10;    // come back in 125 us. PWM frequency is 80 kHz, so change every 10 cycles
      AdcSample=ADCHS_ChannelResultGet(2);      // Get sample as uint16_t
      samplef=(smp_type)(AdcSample-2048)/2048.0;   // Convert to smp_type with mid-scale=0.0
      ADCHS_ChannelConversionStart(2);              // Start next ADC conversion                                               // endif ADC ready
      AfskGen(LoopSenseMark);              // Adjust DDS frequency based on loop condition
      BaudotUartRx(LoopSenseMark);        // Send sensed loop condition (true is mark) to softwaree uart)
      DdsOut=DdsNextSample(); // Run DDS tone generator
      TestSamplef=0.0;                // Output silence if nothing selected
      if(AudioOut==ADC) TestSamplef=samplef;
      if(UserConfig.UseInputBpf==TRUE){
        samplef=BiQuad(samplef,InputBpf);
      }
      if(AudioOut==INPUT_BPF) TestSamplef=samplef;
      if(UserConfig.UseAgc==TRUE){
        samplef=agc(samplef);
      }
      if(AudioOut==AGC) TestSamplef=samplef;
      if(UserConfig.UseLimiter==TRUE){                            // Use limiter or pass input to output
        samplef=(smp_type)copysign(1.0,(double)samplef);            // Limiter. Returns 1.0 if sample positive, =1.0 if negative
      }
      if(AudioOut==LIMITER) TestSamplef=samplef;
      MarkSample=samplef;                         
      SpaceSample=samplef;
      for(n=0;n<NumBpf;n++){
        MarkSample=BiQuad(MarkSample,MarkFilter[n]);       // Mark BPF
        SpaceSample=BiQuad(SpaceSample,SpaceFilter[n]);     // Space BPF
      }
      xyScope(MarkSample,SpaceSample);
      if(AudioOut==MARK_FILTER_OUT) TestSamplef=MarkSample;
      if(AudioOut==SPACE_FILTER_OUT) TestSamplef=SpaceSample;
      MarkDemodOut=BiQuad(fabs(MarkSample), MarkDataFilter);  // Envelope detected and filtered mark
      SpaceDemodOut=BiQuad(fabs(SpaceSample), SpaceDataFilter);    // Same for space
      Threshold=DynamicThresholdGet(MarkDemodOut, SpaceDemodOut);
      if(AudioOut==MARK_DEMOD_OUT) TestSamplef=MarkDemodOut;
      if(AudioOut==SPACE_DEMOD_OUT) TestSamplef=SpaceDemodOut;
             // DiscrimOut is difference between LPF of full wave rectified of mark and space BPFs
      DiscrimOut=MarkDemodOut-SpaceDemodOut;
      if(DiscrimOut-Threshold>UserConfig.MarkHoldThresh){  // we have mark instead of space or noise
        MarkHoldTimer=2400;         // Allow loop key for another 300ms. One character is 163ms long
      }else{
        if(MarkHoldTimer>0) MarkHoldTimer--;
      } 
      if(AudioOut==DISCRIM) TestSamplef=DiscrimOut;
      if(AudioOut==THRESHOLD) TestSamplef=Threshold;
      if(AudioOut==DISCRIM_LESS_THRESHOLD) TestSamplef=DiscrimOut-Threshold;
      if(TX_LED_Get()){     // Hold loop in mark during tx so only keyboard keys loop
        LOOP_KEY_Set();     // Loop switch on
        AFSK_OUT_EN_Set();  // Enable AFSK output
        PTT_Set();          // Close PTT relay
        MarkHoldTimer=0;    // Go into mark hold when dropping out of transmit
      }else{                  // Not in tx, let received data key loop
        AFSK_OUT_EN_Clear();  // Disable AFSK output
        PTT_Clear();          // Release PTT relay                                        
        if(MarkHoldTimer>0){     // Not in mark hold, key loop
          if((DiscrimOut-Threshold)>=0){      // Mark
            LOOP_KEY_Set();     // Loop switch on
          }else{                  // Space
            LOOP_KEY_Clear();     // Loop switch off
          } 
        }else{
          LOOP_KEY_Set();     // Mark hold timed out, so hold mark
        }
      }       // end else not in transmit 
      AutostartKos(DiscrimOut);       // Handle autostart and Keyboard Operated Send only in mark
      if(AudioOut==DDS) TestSamplef=DdsOut;
      AudioPwmSet(TestSamplef);   // Output selected test signal
    } // endif Timer2TimeoutCounter
    DisplayPoll();            // If something in display fifo, send it
    if(FpPollCounter<1){      // Time to poll front panel switches, LEDs, etc.
      PollSwitchesLeds();   // Go poll the switches and LEDs.
      PollShiftMarkHi();    // Change filters if shift or MarkHi changed
      PollEncoder();        // Poll the quadrature encoder updating EncoderCount
      FpPollCounter+=10;  // Each pass is 125us. Come back in 1.25ms
    }
    IDLEn_Clear();      // Exiting DSP code, so make RE7 low so we can see how much time spent there.  
    /* Maintain state machines of all polled MPLAB Harmony modules. */
    SYS_Tasks ( );
  }  // end while(true))
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
  }  // end main())


static void MyTimer2Isr(uint32_t intCause, uintptr_t context){
    // Decrement a counter. Used to count 10 PWM cycles of 80 kHz to update duty cycle at 8 kHz
    // See https://microchipdeveloper.com/harmony3:pic32mzef-getting-started-training-module-step5
    // for info on interrupt callbacks.
    Timer2TimeoutCounter--;
}
/*******************************************************************************
 End of File
*/
