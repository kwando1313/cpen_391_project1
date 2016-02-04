#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"

int main(void) {
	printf("start\n");
	init_control();

	listen();

	return 0;
}
