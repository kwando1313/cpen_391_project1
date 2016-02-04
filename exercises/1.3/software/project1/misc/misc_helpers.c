#include "misc_helpers.h"
#include <math.h>

double convert_to_radians(double angle){
	return (angle*M_PI/180);
}

float sub_and_sqre(int x, int y){
	return pow(x-y, 2);
}

//includes == case
int falls_between(int item, int edge, int otherEdge){
	int lower = min(edge, otherEdge);
	int upper = max(edge, otherEdge);
	return (lower <= item && item <= upper);
}
int avg_val(int x, int y, int z){
	return (x+y+z)/3;
}

void swap_ints(int* x, int* y){
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

int min(int x, int y) {
	if (x <= y) {
		return x;
	} else {
		return y;
	}
}

int max(int x, int y) {
	if (x >= y) {
		return x;
	} else {
		return y;
	}
}

int abs(int a)
{
    if(a < 0)
        return -a ;
    else
        return a ;
}

int sign(int a)
{
    if(a < 0)
        return -1 ;
    else if (a == 0)
        return 0 ;
    else
        return 1 ;
}
