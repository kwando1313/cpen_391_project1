#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

#include "misc_helpers.h"

#define Touchscreen_Status 		(*(volatile unsigned char *)(0x84000230))
#define Touchscreen_Control 	(*(volatile unsigned char *)(0x84000230))
#define Touchscreen_TxData 		(*(volatile unsigned char *)(0x84000232))
#define Touchscreen_RxData 		(*(volatile unsigned char *)(0x84000232))
#define Touchscreen_Baud    	(*(volatile unsigned char *)(0x84000234))


/**************************************************************************
***
**  Initialise touch screen controller
*****************************************************************************/
void putChar_touch(char c);

char getChar_touch();

void init_touch(void);

/*****************************************************************************
**   test if PEN DOWN
*****************************************************************************/
int ScreenTouched(void);

/*****************************************************************************
**   test if PEN UP
*****************************************************************************/
int ScreenIdle(void);

/*****************************************************************************
**   wait for screen to be touched
*****************************************************************************/
void WaitForTouch();

/*****************************************************************************
**   wait for screen to be released
*****************************************************************************/
void WaitForRelease();

/*****************************************************************************
**   wait for screen ready to be read
*****************************************************************************/
void WaitForReadStatus();

/*****************************************************************************
* This function waits for a touch screen press event and returns X,Y coord
*****************************************************************************/
Point GetPress(void);

/*****************************************************************************
* This function waits for a touch screen release event and returns X,Y coord
*****************************************************************************/
Point GetRelease(void);

void test_touch(void);

int real_data;

#endif /* TOUCHSCREEN_H_ */
