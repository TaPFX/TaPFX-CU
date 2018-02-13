all: CU-Server.o

CU-Server.o: TaPFX-CU_Server.c UDPServer.c PWM_TLC59711.c CU-AnalogSet.c
	gcc TaPFX-CU_Server.c UDPServer.c PWM_TLC59711.c CU-AnalogSet.c -lwiringPi -o CU-Server
	
