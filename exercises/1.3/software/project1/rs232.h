#include <stdio.h>

#ifndef RS232_H_
#define RS232_H_

#define RS232_Control (*(volatile unsigned char *)(0x84000200))
#define RS232_Status  (*(volatile unsigned char *)(0x84000200))
#define RS232_TxData  (*(volatile unsigned char *)(0x84000202))
#define RS232_RxData  (*(volatile unsigned char *)(0x84000202))
#define RS232_Baud    (*(volatile unsigned char *)(0x84000204))


// Call this before attempting to read or write via the RS232 port
void Init_RS232(void){
	// set up 6850 Control Register to utilise a divide by 16 clock,
	// set RTS low, use 8 bits of data, no parity, 1 stop bit,
	// transmitter interrupt disabled
	// program baud rate generator to use 115k baud
	// enabling rx irq for now
	RS232_Baud = 0x01;
	RS232_Control = 0x15;
}

void putcharRS232(char c) {
	//wait for tx data to be ready
	while (!(RS232_Status & 0x2));
	RS232_TxData = c;
}

char getcharRS232(void){
	// wait for Rx bit
	while (!(RS232_Status & 0x1));
	return RS232_RxData;
}

// returns true if Rx data available
int RS232TestForReceivedData(void){
	return (RS232_Status & 0x1);
}

void test_rs232(void) {
	//printf("Test RS232\n");
	Init_RS232();
	while(1) {
		char val = getcharRS232();
		putcharRS232(val);
		//printf("received: %c\n", val);
	}
}

#endif /* RS232_H_ */
