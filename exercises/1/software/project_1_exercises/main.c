#include <stdio.h>
#include "exercises.h"
#include "altera_up_avalon_character_lcd.h"
#include "altera_avalon_pio_regs.h"

#define buttons (volatile int *) 0x2040
#define switches (volatile int *) 0x2060
#define leds_g (char *) 0x2050

int main() {
	//exercise_two();

	alt_up_character_lcd_dev * char_lcd_dev;
	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");
	if ( char_lcd_dev == NULL)
	alt_printf ("Error: could not open character LCD device\n");
	else
	alt_printf ("Opened character LCD device\n");
	/* Initialize the character display */
	alt_up_character_lcd_init (char_lcd_dev);
	/* Write "Reading Buttons" in the first row */
	char first_row[] = "Reading Buttons\0";
	alt_up_character_lcd_string(char_lcd_dev, first_row);

	int button_value;
	while(1){
		button_value = *(buttons);
		alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);

		/* Write to LCD, the button being pressed
		 * 0x2 is key[1], 0x4 is key[2], 0x9 is key[3]
		 */
		if (button_value & 0x2)
			alt_up_character_lcd_string(char_lcd_dev, "1");
		else if (button_value & 0x4)
			alt_up_character_lcd_string(char_lcd_dev, "2");
		else if (button_value & 0x9)
			alt_up_character_lcd_string(char_lcd_dev, "3");
		else
			alt_up_character_lcd_string(char_lcd_dev, "X");


	}

	return 0;
}
