#ifndef RS232_H_
#define RS232_H_

#define RS232_Control (*(volatile unsigned char *)(0x84000200))
#define RS232_Status  (*(volatile unsigned char *)(0x84000200))
#define RS232_TxData  (*(volatile unsigned char *)(0x84000202))
#define RS232_RxData  (*(volatile unsigned char *)(0x84000202))
#define RS232_Baud    (*(volatile unsigned char *)(0x84000204))

#include "altera_up_avalon_rs232.h"

// Call this before attempting to read or write via the RS232 port
void Init_RS232(void){
	// set up 6850 Control Register to utilise a divide by 16 clock,
	// set RTS low, use 8 bits of data, no parity, 1 stop bit,
	// transmitter interrupt disabled
	// program baud rate generator to use 115k baud
	// enabling rx irq for now
	RS232_Baud = 0x01;
	RS232_Control = 0x95;
}

int putcharRS232(int c) {
	//wait for tx data to be ready
	while (RS232_Status & 0x2);
	RS232_TxData = c;

	return c;
}

int getcharRS232(void){
	// wait for Rx bit
	while (RS232_Status & 0x1);

	return RS232_RxData;
}

// returns true if Rx data available
int RS232TestForReceivedData(void){
	return (RS232_Status & 0x1);
}

#endif /* RS232_H_ */
