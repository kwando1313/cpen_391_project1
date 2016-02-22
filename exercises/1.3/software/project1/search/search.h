#ifndef SEARCH_H_
#define SEARCH_H_

#include <string.h>
#include <graph.h>

#define MAX_CHAR 26 - 1 // n - 1 because of index; Change n to be the longest node name
#define X 50
#define Y 260
#define INCR 20 // Change this so that MAX_CHAR letters fits

#define MAX_MATCHES 10
#define SEARCH_THRESHHOLD 3 // Both of these can be changed later

typedef struct matched_list{
	name_list* head;
} matched_list;

char query_string[MAX_CHAR];
matched_list matched_names;
int sel; // selected index of matched_names
#define MN_COUNT mn_count(matched_names.head)

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
void del_matches_helper(name_list* nl);
void destroy_matches();
bool is_matched(char name[]);
bool ready();
int mn_count();

#endif /* SEARCH_H_ */
