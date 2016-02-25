#include "graph.h"
#include "string.h"
#include "hashmap.h"
#include "Colours.h"
#include <stdbool.h>
#include <stdlib.h>
#include <altera_up_sd_card_avalon_interface.h>
#include "graphics.h"

int keyify(char* name);

void handle_nodes(short file, graph* graph){
	char c;
	int y = 0;
	short data = 0;

	char arr[8][30];

	char* text;
	char* info = malloc (sizeof(char)* 200);
	while(data >= 0){
		data = alt_up_sd_card_read(file);
		c = (char)data;
		if (c == '$'){
			data = -1;
		}

		else if (c == ','){
			strcpy(arr[y], text);
			memset(&text[0], 0, sizeof(text));
			y++;
		}
		else if (c == ';'){
			memset(&info[0], 0, 200);
			strcpy(info, text);
			vertex* v = init_vertex(atoi(arr[7]), atoi(arr[6]), atof(arr[5]), arr[0], atoi(arr[3]), atoi(arr[4]), atoi(arr[1]), atoi(arr[2]), info);
			add_vertex(graph, v);
			memset(&text[0], 0, sizeof(text));
			y=0;
		}
		else if (c != '\n' && c != '\r'){
			text = strncat(text, &c, 1);
		}
	}
	free(info);
}

void handle_edges(short file, graph* graph){
	int y = 0;
	short data = 0;
	char c;
	char* text;
	char arr[3][4];
	while(data >= 0){
		data = alt_up_sd_card_read(file);
		c = (char)data;
		if (c == '$'){
			data = -1;
		}
		else if (c == ','){
			strcpy(arr[y], text);
			memset(&text[0], 0, sizeof(text));
			y++;
		}
		else if (c == ';'){
			strcpy(arr[y], text);
			bool road = (atoi(arr[2]) == ROAD_COST);
			add_edge(graph, atoi(arr[0]), atoi(arr[1]), road);
			memset(&text[0], 0, sizeof(text));
			y=0;
		}
		else if (c != '\n' && c != '\r'){
			text = strncat(text, &c, 1);
		}

	}

}

void handle_data(short file){
	if (full_map_graph != NULL){
		printf("Replacing full_map_graph\n");
		destroy_graph(full_map_graph);
	}

	full_map_graph = init_graph(DEFAULT_GRAPH_SIZE);
	handle_nodes(file, full_map_graph);
	handle_edges(file, full_map_graph);
}

int keyify(char* name){
	int length = strlen(name);
	int primes[30] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71 ,73,79,83,89,97,101,103,107,109,113};
	int value = 0;
	for (int x = 0; x < length; x++){
		value += primes[x] * (int)name[x];
	}
	return value;
}

void load_graph(char* filename){
	void (*func)(short) = &handle_data;
	load_file(filename, func);
}
