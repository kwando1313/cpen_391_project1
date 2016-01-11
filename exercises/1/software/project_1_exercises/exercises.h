#include <stdio.h>
#include <stdlib.h>
#include "sys/alt_timestamp.h"
#include "altera_up_avalon_character_lcd.h"

#define buttons (volatile int *) 0x2040
#define switches (volatile int *) 0x2060
#define leds_g (char *) 0x2050
#define matrixSize 100

void exercise_one();
void exercise_two();
int** createSquareMatrix(int size);


/**
 * Exercise 1.1
 */
void exercise_one() {

	alt_up_character_lcd_dev * char_lcd_dev;
	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");
	if ( char_lcd_dev == NULL)
		alt_printf ("Error: could not open character LCD device\n");
	else
		alt_printf ("Running Exercise 1.1\n");		/* Initialize the character display */
	alt_up_character_lcd_init (char_lcd_dev);
	/* Write "Reading Buttons" in the first row */
	char first_row[] = "Reading KEYS:\0";
	alt_up_character_lcd_string(char_lcd_dev, first_row);

	int button_value;

	while(1){
		button_value = *(buttons);
		alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
		/* Write to LCD, the button being pressed
		 * 0x2 is key[1], 0x4 is key[2], 0x9 is key[3]
		 * If KEY[3] is pressed then position (0,1) says 3
		 * If KEY[2] is pressed then position (1,1) says 2
		 * ...
		 * else the position is blank
		 */

		if (button_value & 0x8)
			alt_up_character_lcd_string(char_lcd_dev, "3");
		else alt_up_character_lcd_string(char_lcd_dev, " ");

		if (button_value & 0x4)
			alt_up_character_lcd_string(char_lcd_dev, "2");
		else alt_up_character_lcd_string(char_lcd_dev, " ");

		if (button_value & 0x2)
			alt_up_character_lcd_string(char_lcd_dev, "1");
		else alt_up_character_lcd_string(char_lcd_dev, " ");

		if (button_value & 0x1)
			alt_up_character_lcd_string(char_lcd_dev, "0");
		else alt_up_character_lcd_string(char_lcd_dev, " ");

		alt_up_character_lcd_cursor_off (char_lcd_dev);
	}
}

/**
 * Exercise 1.2
 */
void exercise_two() {
	printf("Running exercise two\n");

	int** a = createSquareMatrix(matrixSize);
	int** b = createSquareMatrix(matrixSize);
	int** c = createSquareMatrix(matrixSize);

	int sum;

	alt_timestamp_start();

	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			sum = 0;
			for (int k = 0; k < matrixSize; k++) {
				sum += a[i][k]*b[k][j];
			}
			c[i][j] = sum;
		}
	}

	int end = alt_timestamp();
	printf("time taken : %f seconds\n", (float)end / (float)alt_timestamp_freq());
	printf("cycles : %d \n", end);
}

int** createSquareMatrix(int size){
	int a[size][size];
	for (int col = 0; col < size; col++){
		for (int row = 0; row < size; row++) {
			a[col][row] = rand() % 10; //arbitrary upper bound
		}
	}
	return a;
}
