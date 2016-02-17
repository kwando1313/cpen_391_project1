/*
 * load_node.c
 *
 *  Created on: 2016-02-03
 *      Author: kwando1313
 */
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
	char c;
	int x = 0;
	int y = 0;
	short data = 0;
	char* node_name = "A";
	int x_coord = 0;
	int y_coord = 0;

	char* text;
	while(data >= 0){
		c = (char)alt_up_sd_card_read(file);

		if (c == '$'){
			data = -1;
		}

		else if (c == ','){
			printf("%s\n", text);
			if (y == 0){
				strcpy(node_name, text);
			}
			else if (y == 1){
				x_coord = atoi(text);
			}
			memset(&text[0], 0, sizeof(text));
			y++;
		}
		else if (c == ';' && y == 2){
			y_coord = atoi(text);
			vertex* v = init_vertex(x_coord, y_coord, 0, node_name, x_coord, y_coord);
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
	int node1_key = 0;
	int node2_key = 0;
	int weight = 0;
	short data = 0;
	char c;
	char* text = "A";
	while(data >= 0){
		c = (char)alt_up_sd_card_read(file);
		if (c == '$'){
			data = -1;
		}
		else if (c == ','){
			if (y == 0){
				node1_key = keyify(text);
			}
			else if (y == 1){
				node2_key = keyify(text);
			}
			memset(&text[0], 0, sizeof(text));
			y++;
		}
		else if (c == ';' && y == 2){
			weight = atoi(text);
			int v1_id = (int)hashmapGet(hashmap, node1_key);
			int v2_id = (int)hashmapGet(hashmap, node2_key);
			cost cost1 = {weight};
			if (v1_id != -1 && v2_id != -1){
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

void handle_data(short file, graph* graph, hashmap* hashmap){
	handle_nodes(file, graph, hashmap);
	handle_edges(file, graph, hashmap);
}

int keyify(char* name){
	int length = strlen(name);
	printf(name);
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
	graph* graph = init_graph(DEFAULT_GRAPH_SIZE);
	hashmap* hashmap = hashmapCreate(DEFAULT_GRAPH_SIZE);
	bool found_file = false;

	alt_up_sd_card_dev* device_reference = get_device_reference();
	if (device_reference == NULL || !alt_up_sd_card_is_Present() || !alt_up_sd_card_is_FAT16()){
		printf("Can't find device, or device not configured properly\n");
		return;
	}

	char name[13];
	if (alt_up_sd_card_find_first(".", name) != 0){
		printf("Couldn't find root dir\n");
		return;
	}

	do {
		if (strcmp(name, filename)== 0){
			short int file = alt_up_sd_card_fopen(name, false);
			if (file >= 0){
				printf("found file %s in SD\n", filename);
				handle_data(file, graph, hashmap);
				found_file = true; //want to close file, so use this rather than returning
			}
			alt_up_sd_card_fclose(file);
		}
	}while(!found_file && alt_up_sd_card_find_next(name) == 0);
}
