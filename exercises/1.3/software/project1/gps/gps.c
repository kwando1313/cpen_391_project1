
#define GPS_Status 		(*(volatile unsigned char *)(0x84000210))
#define GPS_Control 	(*(volatile unsigned char *)(0x84000210))
#define GPS_TxData 		(*(volatile unsigned char *)(0x84000212))
#define GPS_RxData 		(*(volatile unsigned char *)(0x84000212))
#define GPS_Baud    	(*(volatile unsigned char *)(0x84000214))

void Init_GPS(void){
	// set up 6850 Control Register to utilise a divide by 16 clock,
	// set RTS low, use 8 bits of data, no parity, 1 stop bit,
	// transmitter interrupt disabled
	// program baud rate generator to use 9600 baud
	// enabling rx irq for now
	GPS_Baud = 0x05;
	GPS_Control = 0x15;
}

void putcharGPS(char c) {
	//wait for tx data to be ready
	while (!(GPS_Status & 0x2));
	GPS_TxData = c;
}

char getcharGPS(void){
	// wait for Rx bit
	while (!(GPS_Status & 0x1));
	return GPS_RxData;
}
