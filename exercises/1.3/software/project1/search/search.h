#ifndef SEARCH_H_
#define SEARCH_H_

#include <string.h>

#define MAX_CHAR 10 - 1 // n - 1 because of index
#define x_i 50
#define y_i 260
#define x_incr 20

char query_string[MAX_CHAR];

void reset_query();

int length();
bool has_space();

void add_letter(char letter);
void del();
void draw_word();

#endif /* SEARCH_H_ */
