#ifndef _TAPWOLFSERVER_H_
#define _TAPWOLFSERVER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "UDPServer.h"
#include "CU-AnalogSet.h"


#define DEFAULTPORT 5555



int debug;
char* Mode;  // 1 (A) Analog Mode, 2 (D) Digital Mode, 3 HikiKomori, 4 Hexenjagt
char* Command; //Command for Digital Mode or Specific use
char Channel;  // Selected Channel in Analog Mode
char DutyCycle; // DutyCicle for Analog Channel;

#endif
