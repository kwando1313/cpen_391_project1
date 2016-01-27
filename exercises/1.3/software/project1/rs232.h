#include <stdio.h>

#ifndef RS232_H_
#define RS232_H_

// Call this before attempting to read or write via the RS232 port
void Init_RS232(void);

void putcharRS232(char c);

//waits for a char to be available, then retrieves it
char getcharRS232(void);

// returns true if Rx data available
int RS232TestForReceivedData(void);

void test_rs232(void);


#endif /* RS232_H_ */
