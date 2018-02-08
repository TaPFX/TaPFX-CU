/* Wraper File for the Magnets in "Hexenjagt"
 * The PWM Channels are bind in pairs of three 
 * to easy connect multiple  PowerMOSFET to the 
 * same PWM signal.
 * 
 */


#ifndef _ANALOGSET_H_
#define _ANALOGSET_H_

#include "PWM_TLC59711.h"

char invert;

signed char aInit();
signed char setAnalog(int magChan, char dutyCycle);

#endif

/*Magnet Channels are include the following PWM Channels
 * MagChan 1 = 0,1,2
 * MagChan 2 = 3,4,5
 * MagChan 3 = 6,7,8
 * MagChan 4 = 9,10,11
 *
 */
