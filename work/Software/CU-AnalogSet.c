#include "AnalogSet.h"

signed char aInit(){
		
	if(initSPI() != 0)
		return -1;
	if(pinMode (3, OUTPUT) != 0)
		return -1;
	
	if(pinMode (5, OUTPUT) != 0)
		return -1;
	
	if(pinMode (7, OUTPUT) != 0)
		return -1;
	
	if(pinMode (11, OUTPUT) != 0)
		return -1;
	
	if(pinMode (33, OUTPUT) != 0)
		return -1;
	return 0;
}

signed char setAnalog(char aChan, char dutyCycle){
	char ledState;
	int pwmVal;
	
	if(aChan > 4 || aChan < 1)
		return -2;
	
	if(dutyCycle > 100 || dutyCycle < 0)
		return -2;
	
	if( dutyCycle == 0){
		ledState = 0;
		pwmVal = 0;
	}else{
		ledState = 1;
		pwmVal = (int)((double)dutyCycle/100*65535);}
	
	switch (aChan) {
		case 1: digitalWrite(3,ledState); break;
		case 2: digitalWrite(5,ledState); break;
		case 3: digitalWrite(7,ledState); break;
		case 4: digitalWrite(11,ledState); break;
		default: break;}
	
	
	if(setChannel(aChan*3-1, pwmVal) != 0)
		return -1;
	if(setChannel(aChan*3-2, pwmVal) != 0)
		return -1;
	if(setChannel(aChan*3-3, pwmVal) != 0)
		return -1;	
	if(setChannel(aChan*3-3, pwmVal) != 0)
		return -1;

	return 0;
}

