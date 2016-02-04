// The following lines are for testing the SD Card, hence why they are commented out for now.

#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
int main(void) {
	printf("start\n\n");
	clear_screen(BLACK);

	init_control();
	listen();


	printf("\n\nend\n");

	return 0;
}
