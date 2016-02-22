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

// Get all the names that match with the query string
void add_matches(){
	sel = 1;
	graph* graph = get_graph();
	name_list* nl = get_names(graph);

	matched_names.head = NULL;
	name_list* m_nl;
	name_list* curr;

	while(nl != NULL){
		if(is_matched(nl->name)){
			m_nl = malloc(sizeof(name_list));
			m_nl->name = nl->name;
			m_nl->next = NULL;

			if(matched_names.head == NULL){
				matched_names.head = m_nl;
			}
			else{
				curr->next = m_nl;
			}
			curr = m_nl;
		}
		nl = nl->next;
	}
	print_nl(matched_names.head);
	printf("%i\n", MN_COUNT);
	match_screen(sel, MN_COUNT);
}

///* Delete names that no longer match
// * Pre: nl is matched and not NULL
// */
//void del_matches_helper(name_list* nl){
//	if(nl->next == NULL)
//		return;
//
//	// Set the next matched name in the matched list
//	name_list* curr = nl->next;
//	printf("%s\n", curr->name);
//	name_list* temp;
//	while(curr != NULL && !(is_matched(curr))){
//		temp = curr->next;
//		//print_nl(curr);
//		free(curr);
//		curr = temp;
//	}
//	nl->next = curr;
//
//	if(curr != NULL)
//		del_matches_helper(curr);
//}

void del_matches(){
	sel = 1;
	name_list* curr = matched_names.head;
	name_list* prev;
	name_list* temp;

	// Updates the head to be the first match in matched list
	while(curr != NULL && !(is_matched(curr->name)) ){
		temp = curr->next;
		free(curr);
		curr = temp;
	}
	matched_names.head = curr;
	prev = curr;
	curr = curr->next;

	while(curr != NULL){
		if(!is_matched(curr->name)){
			prev->next = curr->next;
			free(curr);
		}
		else{
			prev = prev->next;
		}
		curr = prev->next;
	}

	print_nl(matched_names.head);
	printf("%i\n", MN_COUNT);
	match_screen(sel, MN_COUNT);
}

void destroy_matches(){
	name_list* nl = matched_names.head;
	name_list* temp;
	while(nl != NULL){
		temp = nl->next;
		free(nl);
		nl = temp;
	}
}

// Search ready to be entered if we have at least one matching entry
bool ready(){
	return(MN_COUNT > 0);
}

// Return the number of names in the name list
int mn_count(name_list* nl){
	int count = 0;
	while(nl != NULL){
		nl = nl->next;
		count++;
	}
	return count;
}

