#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"

int main(void) {
	clear_screen(255);
	Point x = {0,0};
	//load_image(x, "ubcnew.BMP");
	load_image(x, "ubc1.BMP");

	printf("\n\nend\n");
	return 0;
}
