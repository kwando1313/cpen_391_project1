#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "menu.h"
#include "graphics.h"
#include "touchscreen.h"

int main(void) {
	printf("start\n");
	init_touch();
	init_screen();

	// Listen for button inputs
	while(1){
		Point p_i = GetPress();
		int a = p_i.x;
		int b = p_i.y;
		printf("Pressed Coordinates: (%i, %i)\n", a, b);

		// Info Button
		if(a >= IL && a <= IR && b > IU && b <= ID){
			Point p_f = GetRelease();
			int c = p_f.x;
			int d = p_f.y;
			printf("Released Coordinates: (%i, %i)\n", c, d);

			if(c >= IL && c <= IR && d > IU && d <= ID){
				info_screen();
			}
		}

		// Directions Button
		if(a > DL && a <= DR && b >= DU && b < DD){
			Point p_f = GetRelease();
			int c = p_f.x;
			int d = p_f.y;
			printf("Released Coordinates: (%i, %i)\n", c, d);

			if(c > DL && c <= DR && d >= DU && d < DD){
				directions_screen();
			}
		}

		// Photo Button
		if(a >= PL && a <= PR && b >= PU && b <= PD){
			Point p_f = GetRelease();
			int c = p_f.x;
			int d = p_f.y;
			printf("Released Coordinates: (%i, %i)\n", c, d);

			if(c >= PL && c <= PR && d >= PU && d <= PD){
				photo_screen();
			}
		}

		// About Button
		if(a > AL && a <= AR && b >= AU && b <= AD){
			Point p_f = GetRelease();
			int c = p_f.x;
			int d = p_f.y;
			printf("Released Coordinates: (%i, %i)\n", c, d);

			if(c > AL && c <= AR && d >= AU && d <= AD){
				about_screen();
			}
		}

	}

	printf("end\n");
	return 0;
}
