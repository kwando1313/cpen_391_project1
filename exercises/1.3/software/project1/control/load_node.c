#include "graph.h"
#include "string.h"
#include "hashmap.h"
#include "Colours.h"
#include <stdbool.h>
#include <stdlib.h>
#include <altera_up_sd_card_avalon_interface.h>
#include "graphics.h"

int keyify(char* name);

void handle_nodes(short file, graph* graph, hashmap* hashmap){
	char c = "";
	int x = 0;
	int y = 0;
	short data = 0;
	char* node_name = "A";
	int x_coord = 0;
	int y_coord = 0;
	int altitude = 0;
	int longitude = 0;
	int latitude = 0;

	char* text = "";
	while(data >= 0){
		data = alt_up_sd_card_read(file);
		c = (char)data;

		if (c == '$'){
			data = -1;
		}

		if (c == ','){
			if (y == 0){
				strcpy(node_name, text);
			}
			else if (y == 1){
				x_coord = atoi(text);
			}
			else if (y == 2){
				y_coord = atoi(text);
			}
			else if (y == 3){
				altitude = atoi(text);
			}
			else if (y == 4){
				longitude = atoi(text);
			}
			memset(&text[0], 0, sizeof(text));
			y++;
		}
		else if (c == ';'){
			latitude = atoi(text);
			vertex* v = init_vertex(latitude, longitude, altitude, node_name, x_coord, y_coord);
			int v_id = add_vertex(graph, v);
			int node_key = keyify(v->name);
			hashmapInsert(hashmap, v_id, node_key);
			memset(&text[0], 0, sizeof(text));
			y=0;
			x++;
		}
		else if (c != '\n' && c != '\r'){
			text = strncat(text, &c, 1);
		}
	}
}

void handle_edges(short file, graph* graph, hashmap* hashmap){
	int x = 0;
	int y = 0;
	int v1_id = 0;
	int v2_id = 0;
	int weight = 0;
	short data = 0;
	char c = "";
	char* text = "A";
	memset(&text[0], 0, sizeof(text));
	while(data >= 0){
		data = alt_up_sd_card_read(file);
		c = (char)data;
		if (c == '$'){
			data = -1;
		}
		else if (c == ','){
			if (y == 0){
				v1_id = atoi(text);
			}
			else if (y == 1){
				v2_id = atoi(text);
			}
			memset(&text[0], 0, sizeof(text));
			y++;
		}
		else if (c == ';' && y == 2){
			weight = atoi(text);
			cost cost1 = {weight};
			if (v1_id != -1 && v2_id != -1){
				if (v1_id == 2530 || v2_id == 2530){
					printf("On line %d\n", x);
				}
				add_edge(graph, v1_id, v2_id, cost1);
			}
			memset(&text[0], 0, sizeof(text));
			y=0;
			x++;
		}
		else if (c != '\n' && c != '\r'){
			text = strncat(text, &c, 1);
		}

	}

}

void handle_data(short file){
	//clear_screen(255);
	graph* graph = init_graph(DEFAULT_GRAPH_SIZE);
	hashmap* hashmap = hashmapCreate(DEFAULT_GRAPH_SIZE);
	handle_nodes(file, graph, hashmap);
	handle_edges(file, graph, hashmap);
	//clear_screen(255);
	draw_graph(graph, BLUE, RED);
	printf("Graph loaded.\n");
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

alt_up_sd_card_dev* get_device_reference(){
	alt_up_sd_card_dev* device_reference = NULL;
	if ((device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0")) == NULL){
		return NULL;
	}

	return device_reference;
}


void load_graph(char* filename){
	void (*func)(short) = &handle_data;
	load_file(filename, func);
}
