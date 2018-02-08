/* Header File for TLC59711
 * 12-Channel 16-Bit PWM Driver Chip
 * communication over SPI using wiringPi
 * Adafruit LED Driver SPI Board
 */
#ifndef _PWM_TLC59711_H_
#define _PWM_TLC59711_H_

#include <stdio.h>
#include <stdlib.h>

// Wiring PI Includes
#include <wiringPi.h>
#include <wiringPiSPI.h>

// SPI Definitions
#define LEN 28
int spiChan;
int spiSpeed;

// Buffer for SPI communication
unsigned char spiBuff[LEN];       //Buffer for W/R Comand
unsigned char spiBuffSend[LEN];   //Buffer for Send
unsigned char spiBuffLastSend[LEN];   //Buffer for Send
unsigned char spiBuffRecive[LEN]; // Buffer for Recive

// functions
signed char initSPI();
signed char spiBuffwr();
signed char setChannel(int channel, int pwmVal);
signed char clearAll();
signed char setAllChan(int pwmVal);
signed char fullON();

// debug functions 
void printSPIBuff();
#endif
/* According to the Datasheet
 * and the nummeration on the Adafruit board
 * the channel numbering is
 * 
 * Name = Channel
 * R0 = 0
 * G0 = 1
 * B0 = 2
 * R1 = 4
 * G0 = 5
 * ...
 * G3 = 10
 * B3 = 11
 * 
 * pwm Value can be 0 to 65536 (16 bit Integer)
 */
