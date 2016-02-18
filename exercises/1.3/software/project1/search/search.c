#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "control.h"
#include "graphics.h"
#include "misc_helpers.h"
#include "button.h"
#include "search.h"


// Reset the query string to be empty
void reset_query(){
	while(length() > 0){
		del();
	}
}

// Return the current length of the query string
int length(){
	return strlen(query_string);
}

// Check if the query string has space to still add letters
bool has_space(){
	return(length() <= MAX_CHAR);
}

// adds a letter to the end of the query string
void add_letter(char letter){
	if(has_space())
		strncat(query_string, &letter, 1);
	draw_word();
}

// delete the end of the query string
void del(){
    int back_index = length()-1;
    OutGraphicsCharFont2a((x_i + back_index*x_incr), y_i, 255, 255, query_string[back_index], 0); // 255 is WHITE
    query_string[back_index] = '\0';
}

// Draw the query string above the pop up keyboard
void draw_word(){
	int x = x_i;
	for (int i = 0; i < length(); i++){
		OutGraphicsCharFont2a(x, y_i, BLACK, 255, query_string[i], 0);
		x += x_incr;
	}
}
