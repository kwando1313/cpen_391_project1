#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#define Bluetooth_Status 		(*(volatile unsigned char *)(0x84000220))
#define Bluetooth_Control 		(*(volatile unsigned char *)(0x84000220))
#define Bluetooth_TxData 		(*(volatile unsigned char *)(0x84000222))
#define Bluetooth_RxData 		(*(volatile unsigned char *)(0x84000222))
#define Bluetooth_Baud    		(*(volatile unsigned char *)(0x84000224))

/**************************************************************************
***
**  Initialise bluetooth
*****************************************************************************/
void putCharBluetooth(char c);

char getCharBluetooth();

void Init_Bluetooth(void);

void WaitForReadStat();

/*****************************************************************************
**   Switch modes
*****************************************************************************/
void commandMode(void);

void dataMode(void);

void endCommand();

void setName();

/*****************************************************************************
**   Set name/security pin
*****************************************************************************/
void changeName(char *name[]);

void changePassword(char *pw[]);


void testBluetooth(void);
#endif /* BLUETOOTH_H_ */
