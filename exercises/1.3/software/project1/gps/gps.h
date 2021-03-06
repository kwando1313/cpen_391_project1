#ifndef GPS_H_
#define GPS_H_
#include "altera_up_avalon_character_lcd.h"

// TODO: some kind of error-handling
// if we lose gps connection, and stuck in a while loop,
// is there a way to detect this?
typedef struct __gps_data{
	char time[11];
	char lati[10];
	char longi[11];
	char NS[2];
	char EW[2];
	char pos[2];
	char numSat[3];
	char HDOP[5];
	char alt[5];
	char altUnit[2];
	char geo[5];
	char geoUnit[2];
} gps_data;


void Init_GPS(void);

void putcharGPS(char c);

char getcharGPS(void);

void print_gps_data(gps_data* data);
gps_data* get_gps_data(void);

void gps_data_1(alt_up_character_lcd_dev * char_lcd_dev, char *lati, char *NS, char *longi, char *EW);
void gps_data_2(alt_up_character_lcd_dev * char_lcd_dev, char *time, char *alt);
void gps_data_3(alt_up_character_lcd_dev * char_lcd_dev, char *numSat, char *pos);

void test_command_gps (void);
void test_read_gps (void);
void read_gps(void);
void get_current_coordinates(int* longitude, int* latitude);
gps_data* init_gps_data(void);
void minutes_to_degrees (char* latitude, char* longitude, double* lati, double* longi);

#endif /* GPS_H_ */
