#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"
#include "search.h"
#include "gps.h"
#include "system.h"
#include "sys/alt_irq.h"
#include <stdlib.h>
#include "io.h"

void interruptPrint(void){
	printf ("interrupt enabled\n");
	//Setting the Timeout back to 0 so that the timer
	//can run again. Offset is 0
	IOWR_16DIRECT(TIMER_1_BASE, 0, 0x0);
}

int main(void) {
	//register and enable the IRQ line for our timer
	//Obviously, change the register function to use read_gps instead of interruptPrint
	//using interruptPrint since I don't have the gps right now
	alt_irq_register(TIMER_1_IRQ, NULL, (void *)interruptPrint);
	alt_irq_enable(TIMER_1_IRQ);
	//set our timer to start, be continuous, and enable it's IRQ line. offset is 1
	IOWR_16DIRECT(TIMER_1_BASE, 1, 0x7);

	while(1);

	printf("\nDONE\n");
	return 0;
}
