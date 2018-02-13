#include <unistd.h> 
#include "TaPFX-CU_Server.h"

extern char *optarg;

int main(int argc, char *argv[]){
	int i, run;
	int opt;
	int port = DEFAULTPORT;
	char recvmsg[BUFSIZE];


	while ((opt = getopt(argc, argv, "p:dih")) != -1) {
		switch (opt) {
		case 'p':
			if(optarg != NULL)
				port = atoi(optarg);
			break;
		case 'd':
			debug = 1;
			break;		
		case 'i':
			invert = 1;
			break;
		case 'h':
			printf("Help for HJ-Server\n");
			printf("Usage: %s [-p port number] [-d] debug mode [-h] show Help\n", argv[0]);
			return 0;
			break;
		default: /* '?' */
			printf("Usage: %s [-p portnumber] [-d] debug mode [-i] invert pwm output [-h] show Help\n", argv[0]);
			return -2;
    }
  }
	printf("port: %d\n",port);
	printf("debug: %d\n",debug);
	
	if(initUDPServer(port) != 0){
		printf("ERROR while init UDP-Server\n");
		return -1;}
	
	if(aInit() != 0){
		printf("ERROR while init analog Channel\n");
		return -1;}

	digitalWrite(35,1);

	printf("Start CU-Server\n");
	run = 1;

	while(run){
		bzero(recvmsg, BUFSIZE);
		printf("Wait for command\n");
		waitForClient(recvmsg);
		printf("command \"%s\" recived\n",recvmsg);
		
		if(parseCommand(recvmsg) != 0){
			printf("ERROR wrong Syntax\n");
			continue;
		}
		
		switch (Mode) {
		case A:
			setAnalog(Channel, DutyCycle);
			printf("Case A is selected\n");	
			break;
		case D:
			printf("Case D is selected\n");	
			break;		
		case HK:
			printf("Case HK is selected\n");
			break;
		case HJ:
			printf("Case HK is selected\n");
			break;
		case CUend:
			printf("Case end is selected\n");
			run = 0;
			break;
		
		default: /* '?' */
			printf("Usage: %s [-p portnumber] [-d] debug mode [-i] invert pwm output [-h] show Help\n", argv[0]);
			return -2;
    }
		printf("\n");
		}
	
	digitalWrite(35,0);
	return 0;
}

signed char parseCommand(char command[BUFSIZE]){
	int i;
	char copycommand[BUFSIZE];
	char *splitCommand;
	
	char bufMode = 0;
	char bufCommand = 0;
	char bufChannel = 0;
	char bufDutyCycle = 0;


	for(i=0;i<BUFSIZE;i++)
		copycommand[i] = command[i];
	
	// Testen ob Komando mit TaPFX-CU beginnt, ansonsten verwerfen.
	splitCommand=strtok(copycommand,";");
	if(strcmp(splitCommand, "TaPFX-CU") != 0)
		return -1;
	printf("TapCU\n");
	splitCommand=strtok(NULL,";");
	
	if(strcmp(splitCommand, "A") == 0){ 				// A Analog Mode Mode 1
		bufMode = A;
		// Channel select
		splitCommand=strtok(NULL,";");
		if(splitCommand == NULL)
			return -1;
		bufChannel = atoi(splitCommand);
		if(bufChannel < 1 && bufChannel > 4)
			return -1;
		// DC Value select
		splitCommand=strtok(NULL,";");
		if(splitCommand == NULL)
			return -1;
		bufDutyCycle = atoi(splitCommand);
		if(bufDutyCycle < 0 && bufDutyCycle > 100)
			return -1;
		printf("DC Set\n");;
		Channel = bufChannel;
		DutyCycle = bufDutyCycle;								
	
	}else if(strcmp(splitCommand, "D") == 0){
		bufMode = D;								// D Digital Mode Mode 2
		if(strcmp(splitCommand, "nothing") == 0)
			Command = splitCommand;
		else
			return -1;
	
	}else if(strcmp(splitCommand, "HK") == 0) {
		bufMode = HK;								// HK - Hikikomori Mode 3
		if(	strcmp(splitCommand, "down") == 0 || \
			strcmp(splitCommand, "up")== 0)
			Command = splitCommand;
		else 
			return -1;
	
	}else if(strcmp(splitCommand, "HJ") == 0){
		bufMode = HJ;								// HJ - Hexenjagt Mode 3
		if(	strcmp(splitCommand, "MagSideOFF") == 0 || \
			strcmp(splitCommand, "MagMidOFF") == 0 || \
			strcmp(splitCommand, "MagON") == 0)
			Command = splitCommand;
		else 
			return -1;
	
	}else if(strcmp(splitCommand, "CUend") == 0){
		bufMode = CUend;							// HJ - Hexenjagt Mode 3
	
	}else 
		return -1;

			
	Mode = bufMode;
	
	return 0;
}

