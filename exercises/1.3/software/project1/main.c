#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"

int main(void) {
	printf("start\n\n");

	clear_screen(255);
	Point x = {0,0};
	load_image(x, "WTF.BMP");

	printf("\n\nend\n");
	return 0;
}
