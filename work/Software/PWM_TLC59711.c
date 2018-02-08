/* Function File for TLC59711
 * 12-Channel 16-Bit PWM Driver Chip
 * communication over SPI using wiringPi
 * Adafruit LED Driver SPI Board
 */

#include "PWM_TLC59711.h"

int spiChan = 1;
int spiSpeed = 1000000;



signed char initSPI(){
//Zaehlervariablen	
	int i;

// Init SPI Connection
	wiringPiSetupPhys();
	if( wiringPiSPISetup(spiChan, spiSpeed) == -1){
		printf("Coud not initialise SPI\n");
		return -1;}

// definieren des Initialvectors
	// Erstes Byte des Buffers 
	spiBuff[0] = 0x96;
	spiBuff[1] = 0xdf;
	spiBuff[2] = 0xff;
	spiBuff[3] = 0xff;

	// Restlicher Buffer
	for(i=4;i<LEN;i++)
		spiBuff[i] = 0x00;
	// Buffer in andere Buffer Kopieren
	for(i=0;i<LEN;i++){
		spiBuffSend[i]   = spiBuff[i];
		spiBuffLastSend[i] = spiBuff[i];
		spiBuffRecive[i] = spiBuff[i];}
		
	if(wiringPiSPIDataRW(spiChan, spiBuff, LEN) == -1)
		return -1;

	for(i=0;i<LEN;i++)
		spiBuffRecive[i] = spiBuff[i];

	return 0;
}

signed char spiBuffwr(){
	int i=0;
	
	for(i=0;i<LEN;i++)
		spiBuff[i] = spiBuffSend[i];

	if(wiringPiSPIDataRW(spiChan, spiBuff, LEN) == -1)
		return -1;

	for(i=0;i<LEN;i++)
		spiBuffRecive[i] = spiBuff[i];
	
	for(i=0;i<LEN;i++)
		if(spiBuffRecive[i] != spiBuffLastSend[i])
			return -2;

	for(i=0;i<LEN;i++)
		spiBuffLastSend[i] = spiBuffSend[i];


	return 0;
}


signed char setChannel(int channel, int pwmVal){
	int i = 0;

	if(channel >= 12 || channel < 0)
		return -2;
	
	if(pwmVal > 65536 || pwmVal < 0)
		return -2;

	spiBuffSend[LEN-2-(channel*2)] = pwmVal>>8;
	spiBuffSend[LEN-1-(channel*2)] = pwmVal;
	
	if(spiBuffwr() != 0)
		return -2;

	return 0;

}

signed char clearAll(){
	int i = 0;
	
	for(i=4;i<LEN;i++)
		spiBuffSend[i]=0x0;
	
	if(spiBuffwr() != 0)
		return -2;

	return 0;
}

signed char setAllChan(int pwmVal){
	int i = 0;
	
	if(pwmVal > 0xFFFF || pwmVal < 0)
		return -2;
	
	for(i=0;i<12;i++){
		spiBuffSend[i*2+5]=pwmVal>>8;
		spiBuffSend[i*2+4]=(char)pwmVal;
	}

	if(spiBuffwr() != 0)
		return -2;

	return 0;
}

signed char fullON(){
 	int i = 0;
	
	for(i=4;i<LEN;i++)
		spiBuffSend[i]=0xFF;
	
	if(spiBuffwr() != 0)
		return -2;

	return 0;
}
void printSPIBuff(){
	int i=0;
	printf("\nInit send/lastSend/recive\nBuffer:0,1 %x%x/%x%x/%x%x\n",spiBuffSend[0],spiBuffSend[1],spiBuffLastSend[0],spiBuffLastSend[1],spiBuffRecive[0],spiBuffRecive[1]);
	for(i=2;i<LEN;i++)
		printf("Buffer:%i %x/%x/%x\n",i,spiBuffSend[i],spiBuffLastSend[i],spiBuffRecive[i]);
	return;
}

