#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "control.h"
#include "graphics.h"
#include "misc_helpers.h"
#include "button.h"
#include "search.h"
#include <string.h>


// Reset the query string to be empty
void reset_query(){
	while(qs_length() > 0){
		del();
	}
}

// Return the current length of the query string
int qs_length(){
	return strlen(query_string);
}

// Check if the query string has space to still add letters
bool has_space(){
	return(qs_length() <= MAX_CHAR);
}

// adds a letter to the end of the query string
void add_letter(char letter){
	if(has_space())
		strncat(query_string, &letter, 1);
	draw_word();
}

// delete the end of the query string
void del_letter(){
    int back_index = qs_length()-1;
    OutGraphicsCharFont2a((X + back_index*INCR), Y, 255, 255, query_string[back_index], 0); // 255 is WHITE
    query_string[back_index] = '\0';
}

// Draw the query string above the pop up keyboard
void draw_word(){
	int x = X;
	for (int i = 0; i < qs_length(); i++){
		OutGraphicsCharFont2a(x, Y, BLACK, 255, query_string[i], 0);
		x += INCR;
	}
}

// A match occurs when the string query maps to a name by substring
bool is_matched(char name[]){
	bool matches = true;
	if(strstr(name, query_string) == NULL)
		matches = false;
	return matches;
}

// Return the current number of matched names
int mn_count(){
	return mni+1;
}

// Get all the names that match with the query string
void add_matches(){
	FILE* f = fopen(FILENAME, "r");
	int line = 0;
	mni = 0;

	char name[MAX_CHAR];

	while(fgets(name, MAX_CHAR, f)){
		if(is_matched(name)){
			matched_names[mni] = name;
			mni++;
		}
		line++;
	}

	match_screen();
	fclose(f);
}

// Update and delete names that no longer match
void del_matches(){
	for(int i = 0; i < mn_count(); i++){
		if(!is_matched(matched_names[i])){
			matched_names[i] = "\0";
			//sort
			mni--;
		}
	}
	match_screen();
}

