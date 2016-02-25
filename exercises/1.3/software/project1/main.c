#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"
#include "search.h"
#include "io.h"
#include "gps.h"
								  //0x84000234
#define amd_base (volatile int *)(0x80080000)

int main(void) {
	int v = 0x8;
	IOWR_32DIRECT(amd_base,0,v); // write the value to the component
	printf("value 1 is now %x\n", IORD_32DIRECT(amd_base,0));

	v = 5;
	IOWR_32DIRECT(amd_base,0,v); // write the value to the component
	printf("value 2 is now %x\n", IORD_32DIRECT(amd_base,0));
	usleep(1000);
	v = 0x97;
	IOWR_32DIRECT(amd_base,0,v); // write the value to the component
	printf("value 3 is now %x\n", IORD_32DIRECT(amd_base,0));
	printf("value is now %x\n", IORD_32DIRECT(amd_base,4));
	v = 0xAA;
	IOWR_32DIRECT(amd_base,0,v); // write the value to the component
	printf("value is now %x\n", IORD_32DIRECT(amd_base,4));
//	return 0;
}
