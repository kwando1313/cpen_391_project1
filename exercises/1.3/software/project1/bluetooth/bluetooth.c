#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define Bluetooth_Status 		(*(volatile unsigned char *)(0x84000220))
#define Bluetooth_Control 		(*(volatile unsigned char *)(0x84000220))
#define Bluetooth_TxData 		(*(volatile unsigned char *)(0x84000222))
#define Bluetooth_RxData 		(*(volatile unsigned char *)(0x84000222))
#define Bluetooth_Baud    		(*(volatile unsigned char *)(0x84000224))

void putCharBluetooth(char c){
	while((Bluetooth_Status & 0x02) != 0x02);
	Bluetooth_TxData = c & 0xFF;
}

char getCharBluetooth(){
	while ((Bluetooth_Status & 0x01) != 0x01);
	return Bluetooth_RxData;
}

void Init_Bluetooth(void){
	Bluetooth_Control = 0x15;
	Bluetooth_Baud = 0x01;
}

// Set the bluetooth to command mode.
void commandMode(void){
	usleep(1000000);
	int i;
	for (i = 0; i < 3; i++){
		putCharBluetooth('$');
	}
	usleep(1000000);

	// Print "OK" if successful
	printf("Command Mode\n");
	printf("%d", getCharBluetooth());
	printf("%d\n", getCharBluetooth());
}

// Set the bluetooth to data mode.
void dataMode(void){
	int i;
	for (i = 0; i < 3; i++){
		putCharBluetooth('-');
	}
	endCommand();

	// Print "OK" if successful
	printf("Data Mode\n");
	printf("%d", getCharBluetooth());
	printf("%d\n", getCharBluetooth());
}

// Place at the end of a command while in command mode.
void endCommand(){
	putCharBluetooth("\r");
	putCharBluetooth("\n");
}

// Prepare to give the device a name.
void setName(){
	putCharBluetooth('S');
	putCharBluetooth('N');
	putCharBluetooth(',');
}

// Prepare to give the device a security pin code.
void setPassword(){
	putCharBluetooth('S');
	putCharBluetooth('P');
	putCharBluetooth(',');
}

// Change the device's name
void changeName(char *name[]){
	commandMode();
	setName();

    int i;
    for(i = 0; i<sizeof(name); i++){
        putCharBluetooth(name[i]);
    }
    endCommand();
    // Print "OK" if successful
	printf("Name Changed\n");
	printf("%d", getCharBluetooth());
	printf("%d\n", getCharBluetooth());

	dataMode();
}


// Change the device's password.
void changePassword(char *pw[]){
	commandMode();
	setPassword();

	int i;
    for(i = 0; i<sizeof(pw); i++){
        putCharBluetooth(pw[i]);
    }
    endCommand();

	dataMode();
}

void testBluetooth(void) {
	printf("Test Bluetooth\n");
	Init_Bluetooth();
	printf("Bluetooth Initialized\n");
	char c;

}



