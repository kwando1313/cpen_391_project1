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

void WaitForReadStat(){
	while(!(Bluetooth_Status & 0x01));
}

// Set the bluetooth to command mode.
void commandMode(void){
	printf("Entering Command Mode\n");
	usleep(2000000);
	int i;
	char data[] = "$$$";
	for (i = 0; i < strlen(data); i++){
		putCharBluetooth(data[i]);
	}
	usleep(2000000);

	// Print "OK" if successful
	//WaitForReadStat();
//	char O = getCharBluetooth();
//	printf("%c", O);
//	WaitForReadStat();
//	char K = getCharBluetooth();
//	printf("%c\n", K);
}

// Set the bluetooth to data mode.
void dataMode(void){
	printf("Entering Data Mode\n");
	usleep(2000000);
	char data[] = "---\r\n";
	int i;
	for (i = 0; i < strlen(data); i++){
		putCharBluetooth(data[i]);
	}

	usleep(2000000);

//	// Print "OK" if successful
//	WaitForReadStat();
//	char O = getCharBluetooth();
//	printf("%c", O);
//	WaitForReadStat();
//	char K = getCharBluetooth();
//	printf("%c\n", K);
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
void changeName(char name[]){
	printf("Changing name\n");
	commandMode();
	setName();

    int i;
    for(i = 0; i<strlen(name); i++){
        putCharBluetooth(name[i]);
    }
    usleep(2000000);

    // Print "OK" if successful
//    WaitForReadStat();
//    char O = getCharBluetooth();
//    printf("%c", O);
//    WaitForReadStat();
//    char K = getCharBluetooth();
//    printf("%c\n", K);

	dataMode();
}


// Change the device's password.
void changePassword(char pw[]){
	printf("Changing password\n");
	commandMode();
	setPassword();

	int i;
    for(i = 0; i<strlen(pw); i++){
        putCharBluetooth(pw[i]);
    }
    usleep(2000000);

//    // Print "OK" if successful
//    WaitForReadStat();
//    char O = getCharBluetooth();
//    printf("%c", O);
//    WaitForReadStat();
//    char K = getCharBluetooth();
//    printf("%c\n", K);

	dataMode();
}

void assignBluetooth(void) {
	printf("Test Bluetooth\n");
	Init_Bluetooth();
	printf("Bluetooth Initialized\n");
	char name[] = "DankSquad\r\n";
	char password[] = "0420\r\n";

	changeName(name);
	changePassword(password);
}



