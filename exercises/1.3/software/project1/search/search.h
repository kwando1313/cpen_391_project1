#ifndef SEARCH_H_
#define SEARCH_H_

#include <string.h>

#define MAX_CHAR 20 - 1 // n - 1 because of index; Change n to be the longest node name
#define X 50
#define Y 260
#define INCR 20 // Change this so that MAX_CHAR letters fits

#define FILENAME "file"
#define MAX_MATCHES 10
#define SEARCH_THRESHHOLD 3 // All of should be changed later


char query_string[MAX_CHAR];
char matched_names[MAX_MATCHES][MAX_CHAR];
int mni; // back index of matched_names
int si; // selected index of matched_names

// fcns for query string
void reset_query();
int qs_length();
bool has_space();
void add_letter(char letter);
void del_letter();
void draw_word();

// fcns for search matcher
void add_matches();
void del_matches();
bool is_matched(char name[]);
int mn_count();

#endif /* SEARCH_H_ */
