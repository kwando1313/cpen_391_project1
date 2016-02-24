#include <stdio.h>
#include "touchscreen.h"

#define Touchscreen_Status 		(*(volatile unsigned char *)(0x84000230))
#define Touchscreen_Control 	(*(volatile unsigned char *)(0x84000230))
#define Touchscreen_TxData 		(*(volatile unsigned char *)(0x84000232))
#define Touchscreen_RxData 		(*(volatile unsigned char *)(0x84000232))
#define Touchscreen_Baud    	(*(volatile unsigned char *)(0x84000234))

#define push_buttons123 (volatile int *) 0x80001060

int button_value;
int old_button;
/**************************************************************************
***
**  Initialise touch screen controller
*****************************************************************************/

void putChar_touch(char c){
	while((Touchscreen_Status & 0x02) != 0x02);
	Touchscreen_TxData = c & 0xFF;
}

char getChar_touch(){
	while ((Touchscreen_Status & 0x01) != 0x01);
	return Touchscreen_RxData;
}

void init_touch(void){
	// Program 6850 and baud rate generator to communicate with touchscreen
	// send touchscreen controller an "enable touch" command

	Touchscreen_Control = 0x15;
	Touchscreen_Baud = 0x05;
	usleep(1000000);

	putChar_touch(0x55);
	putChar_touch(0x01);
	putChar_touch(0x12);
}

/*****************************************************************************
**   test if PEN DOWN
*****************************************************************************/
int ScreenTouched(void){
	// return TRUE if any data received from 6850 connected to touchscreen
	// or FALSE otherwise
	button_value = (*push_buttons123);
	if (button_value != old_button){
		if (button_value == 5){
			button_iteration = (button_iteration+1)% 4;
		}
		old_button = button_value;
	}
	return ((getChar_touch() & 0x81) == 0x81); // some value received //0x81 = 10000001 = pen down command
}

/*****************************************************************************
**   test if PEN UP
*****************************************************************************/
int ScreenIdle(void){
	// return TRUE if any data received from 6850 connected to touchscreen
	// or FALSE otherwise
	return ((getChar_touch() & 0x81) == 0x80); // some value received //0x80 = 10000000 = pen up command
}

/*****************************************************************************
**   wait for screen to be touched
*****************************************************************************/
void WaitForTouch(){
	while(!ScreenTouched()){



	}
}

/*****************************************************************************
**   wait for screen to be released
*****************************************************************************/
void WaitForRelease(){
	while(!ScreenIdle());
}

/*****************************************************************************
**   wait for screen ready to be read
*****************************************************************************/
void WaitForReadStatus(){
	while((Touchscreen_Status & 0x00));
}


/*****************************************************************************
* This function waits for a touch screen press event and returns X,Y coord
*****************************************************************************/
Point GetPress(void){
	Point p1;
	// wait for a pen down command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	WaitForTouch();
	//Get value here for x
	//Read first 2(?) bytes

	WaitForReadStatus();
	int x_first_half = getChar_touch();
	WaitForReadStatus();
	int x_second_half = getChar_touch();
	WaitForReadStatus();
	int y_first_half = getChar_touch();
	WaitForReadStatus();
	int y_second_half = getChar_touch();

	p1.x = ((x_second_half) * 128 + (x_first_half+1) ) / 5.12;
	p1.y = ((y_second_half) * 128 + (y_first_half+1) ) / 8.5333;
	return p1;
}
/*****************************************************************************
* This function waits for a touch screen release event and returns X,Y coord
*****************************************************************************/
Point GetRelease(void){
	Point p1;
	// wait for a pen up command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	WaitForTouch();
	WaitForRelease();

	WaitForReadStatus();
	int x_first_half = getChar_touch();
	WaitForReadStatus();
	int x_second_half = getChar_touch();
	WaitForReadStatus();
	int y_first_half = getChar_touch();
	WaitForReadStatus();
	int y_second_half = getChar_touch();

	p1.x = ((x_second_half) * 128 + (x_first_half+1) ) / 5.12;
	p1.y = ((y_second_half) * 128 + (y_first_half+1) ) / 8.5333;

	return p1;
}

void test_touch(void){
	//printf("%d\n", Touchscreen_Status);
	printf("Test touchscreen\n");
	init_touch();
	printf("Touch Initialized\n");

	while(1){
		char c = getChar_touch();

		while(ScreenTouched()){
			printf("touching: %d\n", c);
			//wait();
		}


		Point p1 = GetPress();
		//Point p1 = GetRelease();
		printf("Coordinate: (%i, %i)\n", p1.x, p1.y);

		wait();
	}
}
