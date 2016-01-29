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
void Init_Bluetooth(void){

}


#endif /* BLUETOOTH_H_ */
