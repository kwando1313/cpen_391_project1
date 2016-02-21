#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "control.h"
#include "graphics.h"
#include "misc_helpers.h"
#include "button.h"
#include "search.h"
#include <string.h>
#include "graph.h"


// Reset the query string to be empty
void reset_query(){
	sel = 1;
	while(qs_length() > 0){
		del_letter();
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
bool is_matched(char* name){
	bool matches = true;
	if(strstr(name, query_string) == NULL)
		matches = false;
	return matches;
}

// Initialise the head of the matched names if there is one and return the head
name_list* init_matches(name_list* nl){
	name_list* mn_h = matched_names.head;
	mn_h = NULL;

	while(nl != NULL){
		if(is_matched(nl->name)){
			mn_h = nl;
			mn_h->next = NULL;
			mn_count++;
			nl = nl->next;
			return mn_h;
		}
		nl = nl->next;
	}

	return mn_h;
}
/* Adds names that match; nl is the graph name list
 * Pre: m_nl is matched and not NULL
 */
void add_matches_helper(name_list* nl, name_list* m_nl){
	while(nl != NULL){
		if(is_matched(nl->name)){
			m_nl->next = nl;
			m_nl = m_nl->next;
			mn_count++;
		}
		nl = nl->next;
	}
	m_nl->next = NULL;
}

// Get all the names that match with the query string
void add_matches(){
	mn_count = 0;
	graph* graph = create_test_graph(); //obvs change to access the real graph name list
	name_list* nl = get_names(graph);
	name_list* m_nl = init_matches(nl);

	if(m_nl != NULL)
		add_matches_helper(nl, m_nl);

	match_screen(sel, mn_count);
}

/* Delete names that no longer match
 * Pre: nl is matched and not NULL
 */
void del_matches_helper(name_list* nl){
	if(nl->next == NULL)
		return;

	// Set the next matched name in the matched list
	name_list* temp = nl->next;
	while(!(is_matched(temp)) && temp != NULL){
		temp = temp->next;
		mn_count--;
	}
	nl->next = temp;

	if(temp != NULL)
		del_matches_helper(temp);
}

void del_matches(){
	name_list* m_nl = matched_names.head;

	// Updates the head to be the first match in matched list
	while(!(is_matched(m_nl->name)) && m_nl != NULL ){
		m_nl = m_nl->next;
		mn_count--;
	}

	matched_names.head = m_nl;

	if(m_nl != NULL)
		del_matches_helper(&m_nl);

	match_screen(sel, mn_count);
}

// Search ready to be entered if we have at least one matching entry
bool ready(){
	return(mn_count > 0);
}

