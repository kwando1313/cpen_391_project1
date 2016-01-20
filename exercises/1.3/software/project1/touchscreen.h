#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_
#include <unistd.h>

#define Touchscreen_Status 		(*(volatile unsigned char *)(0x84000230))
#define Touchscreen_Control 	((volatile unsigned char *)(0x84000230))
#define Touchscreen_TxData 		(*(volatile unsigned char *)(0x84000233))
#define Touchscreen_RxData 		((volatile unsigned char *)(0x84000233))
#define Touchscreen_Baud    	(*(volatile unsigned char *)(0x84000238))


/**************************************************************************
***
**  Initialise touch screen controller
*****************************************************************************/
void Init_Touch(void){
	// Program 6850 and baud rate generator to communicate with touchscreen (Default baud rate)
	Touchscreen_Baud = 0x05;

	// send touchscreen controller an "enable touch" command
	* Touchscreen_Control = 0x55;
	*(Touchscreen_Control+1) = 0x01;
	*(Touchscreen_Control+2) = 0x12;
}
/*****************************************************************************
**   test if screen touched
*****************************************************************************/
int ScreenTouched( void){
	// return TRUE if any data received from 6850 connected to touchscreen
	// or FALSE otherwise
	if (*(Touchscreen_RxData) & 0x81) // some value received, 0x81 = 10000001 = pen down command
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
/* a data type to hold a point/coord */
typedef struct{int x, y; } Point;
/*****************************************************************************
* This function waits for a touch screen press event and returns X,Y coord
*****************************************************************************/
Point GetPress(void){
	Point p1;
	// wait for a pen down command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	WaitForTouch();
	//Get value here for x, y
	//Read first 2(?) bytes
	while (!(Touchscreen_Status & 0x00));
	int x_first_half = *(Touchscreen_RxData+1);
	while (!(Touchscreen_Status & 0x00));
	int x_second_half = *(Touchscreen_RxData+2);
	while (!(Touchscreen_Status & 0x00));
	int y_first_half = *(Touchscreen_RxData+3);
	while (!(Touchscreen_Status & 0x00));
	int y_second_half = *(Touchscreen_RxData+4);

	p1.x = (x_second_half * 128) + (x_first_half);
	p1.y = (y_second_half * 128) + (y_first_half);
	return p1;
}
/*****************************************************************************
* This function waits for a touch screen release event and returns X,Y coord
*****************************************************************************/
Point GetRelease(void){
	Point p1;
	// wait for a pen up command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	GetPress();
	WaitForRelease();

	while (!(Touchscreen_Status & 0x00));
	int x_first_half = *(Touchscreen_RxData+1);
	while (!(Touchscreen_Status & 0x00));
	int x_second_half = *(Touchscreen_RxData+2);
	while (!(Touchscreen_Status & 0x00));
	int y_first_half = *(Touchscreen_RxData+3);
	while (!(Touchscreen_Status & 0x00));
	int y_second_half = *(Touchscreen_RxData+4);

	p1.x = (x_second_half * 128) + (x_first_half);
	p1.y = (y_second_half * 128) + (y_first_half);
	return p1;
}

void test_touch(void){
	printf("Test touchscreen\n");
	Init_Touch();

	while(1) {
		if(ScreenTouched()){
			//printf("%c\n", *Touchscreen_RxData);
			printf("touching\n");
		}
		// Point p1 = GetRelease();
		// printf("Released Coordinate: (%i, %i)\n", p1.x, p1.y);
	}
}

#endif /* TOUCHSCREEN_H_ */
