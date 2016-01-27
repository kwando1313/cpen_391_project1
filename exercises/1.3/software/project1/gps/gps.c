
#define GPS_Status 		(*(volatile unsigned char *)(0x84000210))
#define GPS_Control 	(*(volatile unsigned char *)(0x84000210))
#define GPS_TxData 		(*(volatile unsigned char *)(0x84000212))
#define GPS_RxData 		(*(volatile unsigned char *)(0x84000212))
#define GPS_Baud    	(*(volatile unsigned char *)(0x84000214))

void Init_GPS(void){
	// set up 6850 Control Register to utilise a divide by 16 clock,
	// set RTS low, use 8 bits of data, no parity, 1 stop bit,
	// transmitter interrupt disabled
	// program baud rate generator to use 9600 baud
	// enabling rx irq for now
	GPS_Baud = 0x05;
	GPS_Control = 0x15;
}

void putcharGPS(char c) {
	//wait for tx data to be ready
	while (!(GPS_Status & 0x2));
	GPS_TxData = c;
}

char getcharGPS(void){
	// wait for Rx bit
	while (!(GPS_Status & 0x1));
	return GPS_RxData;
}

//angela's bs from main
//TODO refactor this

/*
 #include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "altera_up_avalon_character_lcd.h"

#include "gps.h"
#include "rs232.h"

void test_gps(void){
	alt_up_character_lcd_dev * char_lcd_dev;
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");
	alt_up_character_lcd_init (char_lcd_dev);

	printf("Test GPS\n");
	Init_GPS();
	int dataNum = 0;

	char str[2];
	str[1] = 0;



	char time[15];
	char lati[15];
	char longi[15];
	char NS;
	char EW;
	char pos;
	char numSat[3];
	char HDOP[10];
	char alt[10];
	char altUnit;
	char geo[10];
	char geoUnit;

	strcpy (time, "");
	strcpy (lati, "");
	strcpy (longi, "");
	strcpy (numSat, "");
	strcpy (HDOP, "");
	strcpy (alt, "");
	strcpy (geo, "");

	int len;

	bool header = false;
	bool complete = false;

	while(!complete) {
		if (!header){
			str[0] = getcharGPS();
			if (str[0] == '$'){
				str[0] = getcharGPS();
				if (str[0] == 'G'){
					str[0] = getcharGPS();
					if (str[0] == 'P'){
						str[0] = getcharGPS();
						if (str[0] == 'G'){
							str[0] = getcharGPS();
							if (str[0] == 'G'){
								str[0] = getcharGPS();
								if (str[0] == 'A'){
									header = true;
								}
							}
						}
					}
				}
			}
		}
		else {
			str[0] = getcharGPS();
			if (str[0] == '*'){
				complete = true;
			}
			else if (str[0] == ','){
				dataNum++;
			}
			else{
				if (dataNum == 1){
					//strcat (time, &str);
					len = strlen (time);
					time[len] = str[0];
					printf ("str: %s  len: %d  time: %s\n",str, len, time);

				}/*
				else if (dataNum == 2){
					strcat (lati, &str);
					printf ("%s\n", lati);
				}
				else if (dataNum == 3){
					NS = str;
					printf ("%c\n", NS);

				}
				else if (dataNum == 4){
					strcat (longi, &str);
					printf ("%s\n", longi);
				}
				else if (dataNum == 5){
					EW = str;
					printf ("%c\n", EW);

				}
				else if (dataNum == 6){
					pos = str;
					printf ("%c\n", pos);

				}
				else if (dataNum == 7){
					strcat(numSat, &str);
					//numSat = str;
					printf ("%s\n", numSat);
				}
				else if (dataNum == 8){
					strcat (HDOP, &str);
					printf ("%s\n", HDOP);

				}
				else if (dataNum == 9)
					strcat (alt, &str);
				else if (dataNum == 10)
					altUnit = str;
				else if (dataNum == 11)
					strcat (geo, &str);
				else if (dataNum == 12)
					geoUnit = str;

			}
		}
	}

	printf ("Time: %s\n", time);
	printf ("Latitude: %s\n", lati);
	printf ("N/S: %c\n", NS);
	printf ("Longitude: %s\n", longi);
	printf ("E/W: %c\n", EW);
	printf ("Position: %c\n", pos);
	printf ("Number of Satellites: %s\n", numSat);
	printf ("HDOP: %s\n", HDOP);
	printf ("Altitude: %s\n", alt);
	printf ("Units: %c\n", altUnit);
	printf ("Geoidal Separation: %s\n", geo);
	printf ("Units: %c\n", geoUnit);

	alt_up_character_lcd_string(char_lcd_dev, lati);
	//alt_up_character_lcd_string(char_lcd_dev, " ");
	alt_up_character_lcd_string(char_lcd_dev, NS);


	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, longi);
	//alt_up_character_lcd_string(char_lcd_dev, " ");
	alt_up_character_lcd_string(char_lcd_dev, EW);

}

void test_command_gps (void){
	Init_GPS();
	char str;



}

int main(void) {

	test_gps();

	return 0;
}
 *
 *
 *
 *
 *
 *

 */
