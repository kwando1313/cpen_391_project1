#include <stdio.h>
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"
#include "control.h"
#include "load_node.h"
#include "search.h"
#include "gps.h"

#define amd_base (*(volatile int *)(0x8040000))

int main(void) {
	int x = amd_base;
	printf("%d\n", x);
	amd_base = 32;
	int y = amd_base;
	printf("%d\n", y);

	printf("\nDONE\n");
	return 0;
}
