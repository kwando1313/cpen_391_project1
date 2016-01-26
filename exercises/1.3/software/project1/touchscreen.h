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
void wait(){
	int i;
	for ( i = 0; i < 10000000; i++ );
}

void putChar_touch(char c){
	while((Touchscreen_Status & 0x02) != 0x02);
	Touchscreen_TxData = c & 0xFF;
}

char getChar_touch(){
	while ((Touchscreen_Status & 0x01) != 0x01);
	return Touchscreen_RxData;
}

void Init_Touch(void){
	// Program 6850 and baud rate generator to communicate with touchscreen
	// send touchscreen controller an "enable touch" command

	Touchscreen_Control = 0x15;
	Touchscreen_Baud = 0x05;
	wait();

	putChar_touch(0x55);
	putChar_touch(0x01);
	putChar_touch(0x12);
}

/*****************************************************************************
**   test if screen touched
*****************************************************************************/
int ScreenTouched( void){
	// return TRUE if any data received from 6850 connected to touchscreen
	// or FALSE otherwise
	return (getChar_touch() & 0x81) // some value received //0x81 = 10000001 = pen down command
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
**   wait for screen ready to be read
*****************************************************************************/
void WaitForReadStatus(){
	while((Touchscreen_Status & 0x00));
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

	// Need to calibrate after
	p1.x = ((x_second_half * 128) + (x_first_half))/256;
	p1.y = ((y_second_half * 128) + (y_first_half))/256;
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

	WaitForReadStatus();
	int x_first_half = getChar_touch();
	WaitForReadStatus();
	int x_second_half = getChar_touch();
	WaitForReadStatus();
	int y_first_half = getChar_touch();
	WaitForReadStatus();
	int y_second_half = getChar_touch();

	// Need to calibrate after
	p1.x = (x_second_half * 128) + (x_first_half);
	p1.y = (y_second_half * 128) + (y_first_half);

	return p1;
}

void test_touch(void){
	//printf("%d\n", Touchscreen_Status);
	printf("Test touchscreen\n");
	Init_Touch();
	printf("Touch Initialized\n");
	char c;

	while(1){
		c = getChar_touch();

		while(ScreenTouched()){
			printf("touching: %d\n", c);
			wait();
		}


//		//Point p1 = GetPress();
//		Point p1 = GetRelease();
//		printf("Coordinate: (%i, %i)\n", p1.x, p1.y);
//
//		wait();
	}
}

#endif /* TOUCHSCREEN_H_ */
