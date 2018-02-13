#include "CU-AnalogSet.h"

// gpio wpi 0 - phys 11 - A2
// gpio wpi 2 - phys 13 - Dig
// gpio wpi 3 - phys 15 - A4
// gpio wpi 21 - phy 29 - com red
// gpio wpi 22 - phy 31 - A3
// gpio wpi 23 - phy 33 - A1
// gpio wpi 24 - phy 35 - com green



signed char aInit(){
		
	if(initSPI() != 0)
		return -1;
	pinMode (11, OUTPUT);
	pinMode (13, OUTPUT);
	pinMode (15, OUTPUT);
	pinMode (29, OUTPUT);
	pinMode (31, OUTPUT);
	pinMode (33, OUTPUT);
	pinMode (35, OUTPUT);

	digitalWrite(11,0);
	digitalWrite(13,0);
	digitalWrite(15,0);
	digitalWrite(29,0);
	digitalWrite(31,0);
	digitalWrite(33,0);
	digitalWrite(35,0);
	
	setAnalog(1,0);
	setAnalog(2,0);
	setAnalog(3,0);
	setAnalog(4,0);

	return 0;
}

signed char setAnalog(char aChan, char dutyCycle){
	char ledState;
	int pwmVal;
	
	if(aChan > 4 || aChan < 1)
		return -2;
	
	if(dutyCycle > 100 || dutyCycle < 0)
		return -2;
	
	dutyCycle = 100 - dutyCycle;
	if( dutyCycle == 100){
		ledState = 0;
		pwmVal = 65535;
	}else{
		ledState = 1;
		pwmVal = (int)((double)dutyCycle/100*65535);}
	switch (aChan) {
		case 1: digitalWrite(33,ledState); aChan = 4;break;
		case 2: digitalWrite(11,ledState); aChan = 1;break;
		case 3: digitalWrite(31,ledState); aChan = 2;break;
		case 4: digitalWrite(15,ledState); aChan = 3;break;
		default: break;}
	
	
	if(setChannel(aChan*3-1, pwmVal) != 0)
		return -1;
	if(setChannel(aChan*3-2, pwmVal) != 0)
		return -1;
	if(setChannel(aChan*3-3, pwmVal) != 0)
		return -1;	

	return 0;
}

