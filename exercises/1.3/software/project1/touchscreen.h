#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

#define Touchscreen_Status 		(*(volatile unsigned char *)(0x84000230))
#define Touchscreen_Control 	(*(volatile unsigned char *)(0x84000230))
#define Touchscreen_TxData 		(*(volatile unsigned char *)(0x84000232))
#define Touchscreen_RxData 		(*(volatile unsigned char *)(0x84000232))
#define Touchscreen_Baud    	(*(volatile unsigned char *)(0x84000234))


/**************************************************************************
***
**  Initialise touch screen controller
*****************************************************************************/
void Init_Touch(void){
	// Program 6850 and baud rate generator to communicate with touchscreen
	// send touchscreen controller an "enable touch" command

	Touchscreen_Baud = 0x05;
	Touchscreen_Control = 0x55;

	while (!(Touchscreen_Status & 0x1));
	printf("%d\n", Touchscreen_RxData);

	Touchscreen_Control = 0x01;
	Touchscreen_Control = 0x12;
}
/*****************************************************************************
**   test if screen touched
*****************************************************************************/
int ScreenTouched( void){
	// return TRUE if any data received from 6850 connected to touchscreen
	// or FALSE otherwise
	if (Touchscreen_RxData & 0x81) // some value received //0x81 = 10000001 = pen down command
		return 1; //TRUE
	return 0; //FALSE
}
/*****************************************************************************
**   wait for screen to be touched
*****************************************************************************/
void WaitForTouch(){
	while(!ScreenTouched());
}

/*****************************************************************************
**   wait for screen to be released
*****************************************************************************/
void WaitForRelease(){
	while(ScreenTouched());
}

/*****************************************************************************
**   wait for screen to be released
*****************************************************************************/
void WaitForReadStatus(){
	while(!(Touchscreen_Status & 0x00));
}
/* a data type to hold a point/coord */
typedef struct{int x, y; } Point;
/*****************************************************************************
* This function waits for a touch screen press event and returns X,Y coord
*/
#endif /* TOUCHSCREEN_H_ */
