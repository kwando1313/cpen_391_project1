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

void handle_nodes(short file, graph* graph, hashmap* hashmap){
	char c = "";
	int x = 0;
	int y = 0;
	short data =0;
	char* node_name = "A";
	int x_coord = 0;
	int y_coord = 0;

	char* text = "";
	bool stop = false;
	while(data >= 0 && stop==false){
		data = alt_up_sd_card_read(file);
		c = (char)data;
		if (c == '$'){
			x = 0;
			y = 0;
			stop = true;
		}
		else if (c == ','){
			printf("%s\n", text);
			if (y == 0){
				strcpy(node_name, text);
				printf("%s\n", node_name);
			}
			else if (y == 1){
				x_coord = atoi(text) + 100;
				printf("X Coordinate: %d\n", x_coord);
			}

			memset(&text[0], 0, sizeof(text));
			y++;
		}
		else if (c == ';'){
			printf("%s\n", text);
			if (y == 2){
				y_coord = atoi(text);
				printf("Y Coordinate: %d\n", y_coord);
				vertex* v = init_vertex(x_coord, y_coord, 0, node_name, x_coord, y_coord);
				printf("Vertex name: %s\n", v->name);
				int v_id = add_vertex(graph, v);
				printf("Inserted vertex ID: %d\n", v_id);
				int node_key = keyify(v->name);
				if (strcmp("point1", v->name) == 0){
					printf("My name is point1!\n");
				}
				if (strcmp("point2", v->name) == 0){
					printf("My name is point2!\n");
				}
				if (strcmp("point3", v->name) == 0){
					printf("My name is point3!\n");
				}
				printf("Node key for %d (%s) is %d\n", v_id, v->name, node_key);

				hashmapInsert(hashmap, v_id, node_key);
				printf(hashmapGet(hashmap, node_key));
				memset(&text[0], 0, sizeof(text));
				y=0;
				x++;
			}

		}
		else if (c == '\n'){
			continue;
		}
		else if (c == '\r'){
			continue;
		}
		else {
			text = strncat(text, &c, 1);

		}
	}
	stop = false;
}

void handle_edges(short file, graph* graph, hashmap* hashmap){
	int x = 0;
	int y = 0;
	int node1_key = 0;
	int node2_key = 0;
	int weight = 0;
	short data = 0;
	char c = "";
	char* text = "A";
	while(data >= 0){
		data = alt_up_sd_card_read(file);
		c = (char)data;
		if (c == '$'){
			data = -1;
		}
		else if (c == ','){
			if (y == 0){
				node1_key = keyify(text);
				printf("Node 1 Key: %d\n", node1_key);
			}
			else if (y == 1){
				node2_key = keyify(text);
				printf("Node 2 Key: %d\n", node2_key);
			}
			memset(&text[0], 0, sizeof(text));
			y++;
		}
		else if (c == ';'){
			if (y == 2){
				weight = atoi(text);
			}
			printf(hashmapGet(hashmap, 3778));
			printf("\n");
			int v1_id = (int*)hashmapGet(hashmap, node1_key);
			int v2_id = (int*)hashmapGet(hashmap, node2_key);
			printf("Vertex 1 ID: %d\n", v1_id);
			printf("Vertex 2 ID: %d\n", v2_id);
			cost cost1 = {weight};
			printf("Cost: %d\n", cost1.distance_cost);
			if (v1_id != -1 && v2_id != -1){
				add_edge(graph, v1_id, v2_id, cost1);
			}
			memset(&text[0], 0, sizeof(text));
			y=0;
			x++;
		}
		else if (c == '\n'){
			continue;
		}
		else if (c == '\r'){
			continue;
		}
		else {
			text = strncat(text, &c, 1);

		}
	}

}

void handle_data(short file, graph* graph, hashmap* hashmap){
	handle_nodes(file, graph, hashmap);
	handle_edges(file, graph, hashmap);

	for(int i = 0; i<graph->num_vertices; i++) {
		vertex* v = get_vertex(graph, i);
		WriteAPixel(v->x, v->y, CYAN);
		adjacencyList* adjList = v->adjList;
		int num_edges = adjList->num_neighbours;
		printf("h\n");
		printf("Edges: %d ", num_edges);
		for (int j = 0; j<num_edges; j++) {
			vertex* w = get_vertex(graph, adjList->neighbours[j]);
			Line(v->x, v->y, w->x, w->y, RED);
		}
	}

	printf("Finished reading file!\n");
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
			printf("SDCard Open FAILED\n");
			return NULL;
	}

	printf("SDCard Open PASSED\n");
	return device_reference;

}


void load_graph(char* filename){
	graph* graph = init_graph(40);
	hashmap* hashmap = hashmapCreate(40);
	int test = keyify("point1");
	int test2 = keyify("point2");

	printf("%d %d", test, test2);

	hashmapInsert(hashmap, "point1", test);
	printf(hashmapGet(hashmap, test));
	//return;
	alt_up_sd_card_dev* device_reference = get_device_reference();
	if (device_reference == NULL){
		printf("Can't open device\n");
		return;
	}

	//Init_Touch();
	//clear_screen(WHITE);
	int connected = 0;
	printf("Opening SDCard\n");


	if((connected == 0) && (alt_up_sd_card_is_Present())){
		printf("Card connected.\n");

		if(alt_up_sd_card_is_FAT16()) {
			printf("FAT16 file system detected.\n");
			char * name = "A";


			if (alt_up_sd_card_find_first("/", name) == 0){

				short int file = alt_up_sd_card_fopen(name, false);
				if (file == -1){
					printf("This file could not be opened.\n");
				}
				else if (file == -2){
					printf("This file is already opened.\n");
				}
				else {
					if (strcmp(name, filename)== 0){
						handle_data(file, graph, hashmap);
					}
					alt_up_sd_card_fclose(file);
				}
				while(alt_up_sd_card_find_next(name) == 0){
					printf("NOW I FOUND: %s\n", name);
					if (strcmp(name, filename) == 0){
						short int file = alt_up_sd_card_fopen(name, false);
						if (file == -1){
							printf("This file could not be opened.\n");
						}
						else if (file == -2){
							printf("This file is already opened.\n");
						}
						else {
							if (strcmp(name, filename)== 0){
								handle_data(file, graph, hashmap);
							}
							else {
								printf("Finished reading file!\n");
							}
						}
						alt_up_sd_card_fclose(file);
					}
				}
				return;

			}
			else if (alt_up_sd_card_find_first("/", name) == 1){
				printf("This is an invalid directory.\n");
			}
			else if (alt_up_sd_card_find_first("/", name) == 2){
				printf("The SD card has either been disconnected, or is NOT a FAT16 type.\n");
			}
		}

		else{
			printf("Unknown file system.\n");
		}
		connected = 1;
	} else if((connected == 1) && (alt_up_sd_card_is_Present() == 0)){
		printf("Card disconnected.\n");
		connected =0;
	}


}
