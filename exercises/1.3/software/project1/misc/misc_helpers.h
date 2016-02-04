#ifndef MISC_HELPERS_H_
#define MISC_HELPERS_H_

#define M_PI 3.14159265358979323846264338327

#define NO_RESPONSE 0
#define INFO 1
#define DIR 2
#define PHOTO 3
#define ABOUT 4

typedef struct{int x, y; } Point;

double convert_to_radians(double angle);

//includes == case
int falls_between(int item, int edge, int otherEdge);

int avg_val(int x, int y, int z);

void swap_ints(int* x, int* y);

int min(int x, int y);
int max(int x, int y);

int abs(int a);
int sign(int a);

#endif /* MISC_HELPERS_H_ */
