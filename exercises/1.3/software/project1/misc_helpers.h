#ifndef MISC_HELPERS_H_
#define MISC_HELPERS_H_

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

#endif /* MISC_HELPERS_H_ */
