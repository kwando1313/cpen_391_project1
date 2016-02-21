#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "gps.h"
#include "rs232.h"

#define push_buttons123 (volatile int *) 0x80001060
#define hex0_1			(*(volatile unsigned char *)(0x80001110))
#define hex2_3			(*(volatile unsigned char *)(0x80001100))
#define hex4_5			(*(volatile unsigned char *)(0x800011b0))
#define hex6_7			(*(volatile unsigned char *)(0x800011a0))

#define GPS_Status 		(*(volatile unsigned char *)(0x84000210))
#define GPS_Control 	(*(volatile unsigned char *)(0x84000210))
#define GPS_TxData 		(*(volatile unsigned char *)(0x84000212))
#define GPS_RxData 		(*(volatile unsigned char *)(0x84000212))
#define GPS_Baud    	(*(volatile unsigned char *)(0x84000214))

void wait_for_header(void);
gps_data* get_new_gps_data(void);

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


void test_command_gps (void){
	Init_GPS();
	char str;
	char readlog[] = "$PMTK622,1*29\r\n";	//command for readlog
	int len = strlen(readlog);
	int i = 0;
	bool end_readlog = false;

	while (1){
/*
 * 	We send in the read log command but it won't actually
 * 	give us any useful info yet.
 *
 */
		if (!end_readlog){
			putcharGPS (readlog[i]);
			i++;
			if (i == len){
				end_readlog = true;
			}
		}
			str = getcharGPS();
			printf("%c", str);

	}
}

void gps_data_1(alt_up_character_lcd_dev * char_lcd_dev, char *lati, char *NS, char *longi, char *EW){

	alt_up_character_lcd_string(char_lcd_dev, "Lat:");
	alt_up_character_lcd_string(char_lcd_dev, lati);
	alt_up_character_lcd_string(char_lcd_dev, " ");
	alt_up_character_lcd_string(char_lcd_dev, NS);

	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, "Lon:");
	alt_up_character_lcd_string(char_lcd_dev, longi);
	alt_up_character_lcd_string(char_lcd_dev, " ");
	alt_up_character_lcd_string(char_lcd_dev, EW);

}

void gps_data_2(alt_up_character_lcd_dev * char_lcd_dev, char *time, char *alt){
	alt_up_character_lcd_string(char_lcd_dev, "Time:");
	alt_up_character_lcd_string(char_lcd_dev, time);
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, "Alt:");
	alt_up_character_lcd_string(char_lcd_dev, alt);
}

void gps_data_3(alt_up_character_lcd_dev * char_lcd_dev, char *numSat, char *pos){
	alt_up_character_lcd_string(char_lcd_dev, "#Sat:");
	alt_up_character_lcd_string(char_lcd_dev, numSat);
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, "Pos:");
	alt_up_character_lcd_string(char_lcd_dev, pos);
}

void test_read_gps(void){
	alt_up_character_lcd_dev * char_lcd_dev;
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");
	alt_up_character_lcd_init (char_lcd_dev);

	printf("Test GPS\n");
	Init_GPS();

	gps_data* data = get_gps_data();


	/*	This is for printing onto the lcd
	 */

	int old_button = -1;
	while (1){
		int button_value = *(push_buttons123); // get button value

		if (button_value != old_button){
			if (button_value == 3){
				alt_up_character_lcd_init (char_lcd_dev);
				gps_data_1 (char_lcd_dev, data->lati, data->NS, data->longi, data->EW);
			}
			else if (button_value == 5){
				alt_up_character_lcd_init (char_lcd_dev);
				gps_data_2 (char_lcd_dev, data->time, data->alt);
			}
			else if (button_value == 6){
				alt_up_character_lcd_init (char_lcd_dev);
				gps_data_3 (char_lcd_dev, data->numSat, data->pos);
			}
			else if (button_value == 7){
				alt_up_character_lcd_init (char_lcd_dev);
				alt_up_character_lcd_string(char_lcd_dev, "Press buttons:");
				alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
				alt_up_character_lcd_string(char_lcd_dev, "KEY0:new data");
			}
		}

		old_button = button_value;
	}
}
void read_gps(void) {
	gps_data* data = get_gps_data();

	double lati;
	double longi;
	//convert the latitude and longitude data to completely be in degrees
	minutes_to_degrees (data->lati, data->longi, &lati, &longi);
	printf ("Lati: %lf, Longi: %lf\n", lati, longi);
	return;
}
void wait_for_header(void) {
	char str[] = "$GPGGA";
	char buf[7];
	buf[6] = 0;
	while (true){
		for (int i = 0; i < 6; i++) {
			buf[i] = getcharGPS();
			if (buf[0] != '$')
				break;
		}
		if (strcmp(str,buf) == 0) {
			return;
		}
	}
}

void print_gps_data(gps_data* data) {
	printf ("Time: %s\n", data->time);
	printf ("Latitude: %s\n", data->lati);
	printf ("N/S: %s\n", data->NS);
	printf ("Longitude: %s\n", data->longi);
	printf ("E/W: %s\n", data->EW);
	printf ("Position: %s\n", data->pos);
	printf ("Number of Satellites: %s\n", data->numSat);
	printf ("HDOP: %s\n", data->HDOP);
	printf ("Altitude: %s\n", data->alt);
	printf ("Units: %s\n", data->altUnit);
	printf ("Geoidal Separation: %s\n", data->geo);
	printf ("Units: %s\n", data->geoUnit);
}

gps_data* get_new_gps_data(void){
	int dataNum = 0;
	char rx;
	int i = 0;

	gps_data* new_gps_data = init_gps_data();
	while(true) {
		rx = getcharGPS();
		if (rx == '*'){
			print_gps_data(new_gps_data);
			break;
		}
		else if (rx == ','){
			dataNum++;
			i = 0;
		}
		else{
			if (dataNum == 1){
				new_gps_data->time[i] = rx;
			}
			else if (dataNum == 2){
				new_gps_data->lati[i] = rx;
			}

			else if (dataNum == 3){
				new_gps_data->NS[i] = rx;
			}
			else if (dataNum == 4){
				new_gps_data->longi[i] = rx;
			}
			else if (dataNum == 5){
				new_gps_data->EW[i] = rx;
			}
			else if (dataNum == 6){
				new_gps_data->pos[i] = rx;
			}
			else if (dataNum == 7){
				new_gps_data->numSat[i] = rx;
			}
			else if (dataNum == 8){
				new_gps_data->HDOP[i] = rx;
			}
			else if (dataNum == 9){
				new_gps_data->alt[i] = rx;
			}
			else if (dataNum == 10){
				new_gps_data->altUnit[i] = rx;
			}
			else if (dataNum == 11){
				new_gps_data->geo[i] = rx;
			}
			else if (dataNum == 12){
				new_gps_data->geoUnit[i] = rx;
			}
			i++;
		}

	}

	return new_gps_data;
}

gps_data* get_gps_data(void){
	wait_for_header();
	return get_new_gps_data();
}

/*
 * Initialize new gps dat struct
 */
gps_data* init_gps_data (void){
	gps_data* data = malloc(sizeof(gps_data));

	data->time[10] = 0;
	data->lati[9] = 0;
	data->longi[10] = 0;
	data->NS[1] = 0;
	data->EW[1] = 0;
	data->pos[1] = 0;
	data->numSat[2] = 0;
	data->HDOP[4] = 0;
	data->alt[4] = 0;
	data->altUnit[1] = 0;
	data->geo[4] = 0;
	data->geoUnit[1] = 0;

	return data;
}

void minutes_to_degrees (char* latitude, char* longitude, double *lati, double *longi){
	char bufLat[8];
	char bufLong[8];
	double minsLat;
	double minsLong;
	double degLat;
	double degLong;


	bufLat[0] = latitude[0]; //copy the values already in degrees
	bufLat[1] = latitude[1];
	bufLong[0] = longitude[0];
	bufLong[1] = longitude[1];
	bufLong[2] = longitude[2];

	degLat = atof(bufLat);	//convert degrees values into double from char
	degLong = atof(bufLong);


	strcpy (bufLat, &latitude[2]);	// copy values in minutes degrees
	strcpy (bufLong, &longitude[3]);

	minsLat = atof(bufLat);	//convert minutes degrees to double form char
	minsLong = atof(bufLong);

	*lati = degLat + (minsLat / 60);	//get complete data in degrees
	*longi = degLong + (minsLong / 60);

}
