/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h UUUUUUUUU

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for CPU_IDLEn pin ***/
#define CPU_IDLEn_Set()               (LATESET = (1U<<7))
#define CPU_IDLEn_Clear()             (LATECLR = (1U<<7))
#define CPU_IDLEn_Toggle()            (LATEINV= (1U<<7))
#define CPU_IDLEn_OutputEnable()      (TRISECLR = (1U<<7))
#define CPU_IDLEn_InputEnable()       (TRISESET = (1U<<7))
#define CPU_IDLEn_Get()               ((PORTE >> 7) & 0x1U)
#define CPU_IDLEn_PIN                  GPIO_PIN_RE7

/*** Macros for DEBUG_UART2_TX pin ***/
#define DEBUG_UART2_TX_Get()               ((PORTC >> 2) & 0x1U)
#define DEBUG_UART2_TX_PIN                  GPIO_PIN_RC2

/*** Macros for PWM_OUT pin ***/
#define PWM_OUT_Get()               ((PORTE >> 8) & 0x1U)
#define PWM_OUT_PIN                  GPIO_PIN_RE8

/*** Macros for LED_REDn pin ***/
#define LED_REDn_Set()               (LATBSET = (1U<<5))
#define LED_REDn_Clear()             (LATBCLR = (1U<<5))
#define LED_REDn_Toggle()            (LATBINV= (1U<<5))
#define LED_REDn_OutputEnable()      (TRISBCLR = (1U<<5))
#define LED_REDn_InputEnable()       (TRISBSET = (1U<<5))
#define LED_REDn_Get()               ((PORTB >> 5) & 0x1U)
#define LED_REDn_PIN                  GPIO_PIN_RB5

/*** Macros for AFSK_IN pin ***/
#define AFSK_IN_Get()               ((PORTB >> 4) & 0x1U)
#define AFSK_IN_PIN                  GPIO_PIN_RB4

/*** Macros for LED_GREENn pin ***/
#define LED_GREENn_Set()               (LATBSET = (1U<<1))
#define LED_GREENn_Clear()             (LATBCLR = (1U<<1))
#define LED_GREENn_Toggle()            (LATBINV= (1U<<1))
#define LED_GREENn_OutputEnable()      (TRISBCLR = (1U<<1))
#define LED_GREENn_InputEnable()       (TRISBSET = (1U<<1))
#define LED_GREENn_Get()               ((PORTB >> 1) & 0x1U)
#define LED_GREENn_PIN                  GPIO_PIN_RB1

/*** Macros for LED_BLUEn pin ***/
#define LED_BLUEn_Set()               (LATBSET = (1U<<0))
#define LED_BLUEn_Clear()             (LATBCLR = (1U<<0))
#define LED_BLUEn_Toggle()            (LATBINV= (1U<<0))
#define LED_BLUEn_OutputEnable()      (TRISBCLR = (1U<<0))
#define LED_BLUEn_InputEnable()       (TRISBSET = (1U<<0))
#define LED_BLUEn_Get()               ((PORTB >> 0) & 0x1U)
#define LED_BLUEn_PIN                  GPIO_PIN_RB0

/*** Macros for DisplayDataCmdn pin ***/
#define DisplayDataCmdn_Set()               (LATASET = (1U<<9))
#define DisplayDataCmdn_Clear()             (LATACLR = (1U<<9))
#define DisplayDataCmdn_Toggle()            (LATAINV= (1U<<9))
#define DisplayDataCmdn_OutputEnable()      (TRISACLR = (1U<<9))
#define DisplayDataCmdn_InputEnable()       (TRISASET = (1U<<9))
#define DisplayDataCmdn_Get()               ((PORTA >> 9) & 0x1U)
#define DisplayDataCmdn_PIN                  GPIO_PIN_RA9

/*** Macros for DisplayResetn pin ***/
#define DisplayResetn_Set()               (LATFSET = (1U<<13))
#define DisplayResetn_Clear()             (LATFCLR = (1U<<13))
#define DisplayResetn_Toggle()            (LATFINV= (1U<<13))
#define DisplayResetn_OutputEnable()      (TRISFCLR = (1U<<13))
#define DisplayResetn_InputEnable()       (TRISFSET = (1U<<13))
#define DisplayResetn_Get()               ((PORTF >> 13) & 0x1U)
#define DisplayResetn_PIN                  GPIO_PIN_RF13

/*** Macros for LOOP_SAMPLE_IN pin ***/
#define LOOP_SAMPLE_IN_Set()               (LATDSET = (1U<<14))
#define LOOP_SAMPLE_IN_Clear()             (LATDCLR = (1U<<14))
#define LOOP_SAMPLE_IN_Toggle()            (LATDINV= (1U<<14))
#define LOOP_SAMPLE_IN_OutputEnable()      (TRISDCLR = (1U<<14))
#define LOOP_SAMPLE_IN_InputEnable()       (TRISDSET = (1U<<14))
#define LOOP_SAMPLE_IN_Get()               ((PORTD >> 14) & 0x1U)
#define LOOP_SAMPLE_IN_PIN                  GPIO_PIN_RD14

/*** Macros for AFSK_OUT_ENn pin ***/
#define AFSK_OUT_ENn_Set()               (LATDSET = (1U<<15))
#define AFSK_OUT_ENn_Clear()             (LATDCLR = (1U<<15))
#define AFSK_OUT_ENn_Toggle()            (LATDINV= (1U<<15))
#define AFSK_OUT_ENn_OutputEnable()      (TRISDCLR = (1U<<15))
#define AFSK_OUT_ENn_InputEnable()       (TRISDSET = (1U<<15))
#define AFSK_OUT_ENn_Get()               ((PORTD >> 15) & 0x1U)
#define AFSK_OUT_ENn_PIN                  GPIO_PIN_RD15

/*** Macros for DisplayCsn pin ***/
#define DisplayCsn_Set()               (LATDSET = (1U<<10))
#define DisplayCsn_Clear()             (LATDCLR = (1U<<10))
#define DisplayCsn_Toggle()            (LATDINV= (1U<<10))
#define DisplayCsn_OutputEnable()      (TRISDCLR = (1U<<10))
#define DisplayCsn_InputEnable()       (TRISDSET = (1U<<10))
#define DisplayCsn_Get()               ((PORTD >> 10) & 0x1U)
#define DisplayCsn_PIN                  GPIO_PIN_RD10

/*** Macros for DisplaySpiClk pin ***/
#define DisplaySpiClk_Get()               ((PORTD >> 1) & 0x1U)
#define DisplaySpiClk_PIN                  GPIO_PIN_RD1

/*** Macros for DisplaySpiMosi pin ***/
#define DisplaySpiMosi_Get()               ((PORTD >> 3) & 0x1U)
#define DisplaySpiMosi_PIN                  GPIO_PIN_RD3

/*** Macros for LOOP_KEY_OUT pin ***/
#define LOOP_KEY_OUT_Set()               (LATDSET = (1U<<4))
#define LOOP_KEY_OUT_Clear()             (LATDCLR = (1U<<4))
#define LOOP_KEY_OUT_Toggle()            (LATDINV= (1U<<4))
#define LOOP_KEY_OUT_OutputEnable()      (TRISDCLR = (1U<<4))
#define LOOP_KEY_OUT_InputEnable()       (TRISDSET = (1U<<4))
#define LOOP_KEY_OUT_Get()               ((PORTD >> 4) & 0x1U)
#define LOOP_KEY_OUT_PIN                  GPIO_PIN_RD4

/*** Macros for PTTn pin ***/
#define PTTn_Set()               (LATDSET = (1U<<5))
#define PTTn_Clear()             (LATDCLR = (1U<<5))
#define PTTn_Toggle()            (LATDINV= (1U<<5))
#define PTTn_OutputEnable()      (TRISDCLR = (1U<<5))
#define PTTn_InputEnable()       (TRISDSET = (1U<<5))
#define PTTn_Get()               ((PORTD >> 5) & 0x1U)
#define PTTn_PIN                  GPIO_PIN_RD5


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/


#define    GPIO_PORT_A  (0)
#define    GPIO_PORT_B  (1)
#define    GPIO_PORT_C  (2)
#define    GPIO_PORT_D  (3)
#define    GPIO_PORT_E  (4)
#define    GPIO_PORT_F  (5)
#define    GPIO_PORT_G  (6)
typedef uint32_t GPIO_PORT;

typedef enum
{
    GPIO_INTERRUPT_ON_MISMATCH,
    GPIO_INTERRUPT_ON_RISING_EDGE,
    GPIO_INTERRUPT_ON_FALLING_EDGE,
    GPIO_INTERRUPT_ON_BOTH_EDGES,
}GPIO_INTERRUPT_STYLE;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/


#define     GPIO_PIN_RA0  (0U)
#define     GPIO_PIN_RA1  (1U)
#define     GPIO_PIN_RA2  (2U)
#define     GPIO_PIN_RA3  (3U)
#define     GPIO_PIN_RA4  (4U)
#define     GPIO_PIN_RA5  (5U)
#define     GPIO_PIN_RA6  (6U)
#define     GPIO_PIN_RA7  (7U)
#define     GPIO_PIN_RA9  (9U)
#define     GPIO_PIN_RA10  (10U)
#define     GPIO_PIN_RA14  (14U)
#define     GPIO_PIN_RA15  (15U)
#define     GPIO_PIN_RB0  (16U)
#define     GPIO_PIN_RB1  (17U)
#define     GPIO_PIN_RB2  (18U)
#define     GPIO_PIN_RB3  (19U)
#define     GPIO_PIN_RB4  (20U)
#define     GPIO_PIN_RB5  (21U)
#define     GPIO_PIN_RB6  (22U)
#define     GPIO_PIN_RB7  (23U)
#define     GPIO_PIN_RB8  (24U)
#define     GPIO_PIN_RB9  (25U)
#define     GPIO_PIN_RB10  (26U)
#define     GPIO_PIN_RB11  (27U)
#define     GPIO_PIN_RB12  (28U)
#define     GPIO_PIN_RB13  (29U)
#define     GPIO_PIN_RB14  (30U)
#define     GPIO_PIN_RB15  (31U)
#define     GPIO_PIN_RC1  (33U)
#define     GPIO_PIN_RC2  (34U)
#define     GPIO_PIN_RC3  (35U)
#define     GPIO_PIN_RC4  (36U)
#define     GPIO_PIN_RC12  (44U)
#define     GPIO_PIN_RC13  (45U)
#define     GPIO_PIN_RC14  (46U)
#define     GPIO_PIN_RC15  (47U)
#define     GPIO_PIN_RD0  (48U)
#define     GPIO_PIN_RD1  (49U)
#define     GPIO_PIN_RD2  (50U)
#define     GPIO_PIN_RD3  (51U)
#define     GPIO_PIN_RD4  (52U)
#define     GPIO_PIN_RD5  (53U)
#define     GPIO_PIN_RD9  (57U)
#define     GPIO_PIN_RD10  (58U)
#define     GPIO_PIN_RD11  (59U)
#define     GPIO_PIN_RD12  (60U)
#define     GPIO_PIN_RD13  (61U)
#define     GPIO_PIN_RD14  (62U)
#define     GPIO_PIN_RD15  (63U)
#define     GPIO_PIN_RE0  (64U)
#define     GPIO_PIN_RE1  (65U)
#define     GPIO_PIN_RE2  (66U)
#define     GPIO_PIN_RE3  (67U)
#define     GPIO_PIN_RE4  (68U)
#define     GPIO_PIN_RE5  (69U)
#define     GPIO_PIN_RE6  (70U)
#define     GPIO_PIN_RE7  (71U)
#define     GPIO_PIN_RE8  (72U)
#define     GPIO_PIN_RE9  (73U)
#define     GPIO_PIN_RF0  (80U)
#define     GPIO_PIN_RF1  (81U)
#define     GPIO_PIN_RF2  (82U)
#define     GPIO_PIN_RF3  (83U)
#define     GPIO_PIN_RF4  (84U)
#define     GPIO_PIN_RF5  (85U)
#define     GPIO_PIN_RF8  (88U)
#define     GPIO_PIN_RF12  (92U)
#define     GPIO_PIN_RF13  (93U)
#define     GPIO_PIN_RG0  (96U)
#define     GPIO_PIN_RG1  (97U)
#define     GPIO_PIN_RG6  (102U)
#define     GPIO_PIN_RG7  (103U)
#define     GPIO_PIN_RG8  (104U)
#define     GPIO_PIN_RG9  (105U)
#define     GPIO_PIN_RG12  (108U)
#define     GPIO_PIN_RG13  (109U)
#define     GPIO_PIN_RG14  (110U)
#define     GPIO_PIN_RG15  (111U)

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
#define    GPIO_PIN_NONE   (-1)

typedef uint32_t GPIO_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
	 uint32_t xvalue = (uint32_t)value;
    GPIO_PortWrite((pin>>4U), (uint32_t)(0x1U) << (pin & 0xFU), (xvalue) << (pin & 0xFU));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return ((((GPIO_PortRead((GPIO_PORT)(pin>>4U))) >> (pin & 0xFU)) & 0x1U) != 0U);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (((GPIO_PortLatchRead((GPIO_PORT)(pin>>4U)) >> (pin & 0xFU)) & 0x1U) != 0U);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
