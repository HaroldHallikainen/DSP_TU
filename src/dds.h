/* 
 * File:   dds.h
 * Author: Harold_Win7
 *
 * Created on February 12, 2022, 8:04 PM
 */

#ifndef DDS_H
#define	DDS_H

#include "main.h" // has typedef for smp_type

smp_type DdsNextSample(void); // Return the next sample (-1.0 to +1.0))
void DdsFreqSet(smp_type freq); // Set DdsRadiansPerSample so there is less math in DdsNextSample


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* DDS_H */

