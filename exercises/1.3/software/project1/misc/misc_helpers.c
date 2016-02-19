#include "misc_helpers.h"
#include "button.h"
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void read_bytes_from_file(unsigned char* str, int len, short file){
	for(int x=0 ; x<len ; x++){
		str[x]=(unsigned char)(alt_up_sd_card_read(file));
	}
}

double convert_to_radians(double angle){
	return (angle*M_PI/180);
}

void to_caps(char* from, char* to){
	int x = 0;
 	while (from[x] != '\0'){
 		to[x] = (char) toupper(from[x]);
 		x++;
 	}
 	to[x] = '\0';
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

load_file(char* filename, void (*func)(short)){
	bool found_file = false;

	if (get_device_reference() == NULL || !alt_up_sd_card_is_Present() || !alt_up_sd_card_is_FAT16()){
		printf("Can't find device, or device not configured properly\n");
		return;
	}

	char filename_all_caps[strlen(filename)];
	to_caps(filename, filename_all_caps);
	char found_file_name[13];
	if (alt_up_sd_card_find_first(".", found_file_name) != 0){
		printf("Couldn't find root dir\n");
		return;
	}

	do {
		if (strcmp(found_file_name, filename_all_caps)== 0){
			short int file = alt_up_sd_card_fopen(found_file_name, false);
			if (file >= 0){
				printf("found file %s in SD\n", filename_all_caps);
				(*func)(file);
				found_file = true; //want to close file, so use this rather than returning
			}
			alt_up_sd_card_fclose(file);
		}
	}while(!found_file && alt_up_sd_card_find_next(found_file_name) == 0);
}

bool str_begins(char* str, char* begins){
	if(strlen(str) < strlen(begins)){
		return false;
	}

	for(int i = 0; i<strlen(begins); i++){
		printf("str_begins: %c, %c\n", str[i], begins[i]);
		if(toupper(str[i]) != toupper(begins[i])) {
			return false;
		}
	}

	return true;
}

//case insensitive, unless equal, then lowercase first
//shorter == smaller
//assuming no numbers for now
int alphaBetize (char *a, char *b) {
	int i = 0;
	int j = 0;
	//printf("len: %d , %d\n", strlen(a), strlen(b));
	while(i < strlen(a) && j < strlen(b)){
		char curr_a = (char)tolower(a[i]);
		char curr_b = (char)tolower(b[j]);
		if (curr_a != curr_b) {
			//printf("%c, %c\n", curr_a, curr_b);
			return curr_a - curr_b;
		}
		i++;
		j++;
	}

	if (strlen(a) == strlen(b)) {
		return strcmp(b, a); //makes lowercase < uppercase
	} else {
		return strlen(a) - strlen(b);
	}
}
