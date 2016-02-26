#ifndef MISC_HELPERS_H_
#define MISC_HELPERS_H_

#include <stdbool.h>
#include <altera_up_sd_card_avalon_interface.h>

#define M_PI 3.14159265358979323846264338327

#define NO_RESPONSE 0
#define INFO 1
#define DIR 2
#define PHOTO 3
#define ABOUT 4

#define RADIUS 15//6.0827

typedef struct{int x, y; } Point;

bool points_equal(Point a, Point b);

int alphaBetize (char *a, char *b);

void load_file(char* filename, void (*func)(short));

void read_bytes_from_file(unsigned char* str, int len, short file);

alt_up_sd_card_dev* get_device_reference();

double convert_to_radians(double angle);

float sub_and_sqre(int x, int y);

//includes == case
int falls_between(int item, int edge, int otherEdge);

void to_caps(char* from, char* to);

int avg_val(int x, int y, int z);

void swap_ints(int* x, int* y);

int min(int x, int y);
int max(int x, int y);

int abs(int a);
int sign(int a);

bool str_begins(char* str, char* begins);

#endif /* MISC_HELPERS_H_ */
