/*
 * load_node.c
 *
 *  Created on: 2016-02-03
 *      Author: kwando1313
 */
#include "graph.h"
#include "string.h"
#include <altera_up_sd_card_avalon_interface.h>



void load_graph(char* filename){
	graph* graph = init_graph(20);
	alt_up_sd_card_dev* device_reference = NULL;
	//Init_Touch();
	//clear_screen(WHITE);
	int connected = 0;
	printf("Opening SDCard\n");
	if ((device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0")) == NULL){
		printf("SDCard Open FAILED\n");
		return;
	}
	else
		printf("SDCard Open PASSED\n");

	if(device_reference != NULL ) {
		while(1) {
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
							char* node_list[3];
							char* edge_list[3];
							int x = 0;
							int y = 0;
							if (strcmp(name, filename)== 0){

								short data =0;
								printf("Current file: %s\n", name);
								printf("My name: %s\n", filename);
								while((char)data != "$"){
									char* text2 = "";
									while((char)data != ";"){
										char* text = "";
										while((char)data != ","){
											data = alt_up_sd_card_read(file);
											strcat(text, (char)data);
										}
										node_list[x][y] = text;
										y++;
										alt_up_sd_card_read(file);
									}
									y = 0;
									x++;
									alt_up_sd_card_read(file);
									alt_up_sd_card_read(file);
									alt_up_sd_card_read(file);//Account for /n
								}
								alt_up_sd_card_read(file);
								alt_up_sd_card_read(file);
								hashmap* hashmap = hashmapCreate(20);

								for (int j = 0; j < x; j++){
									vertex v = init_vertex((int)node_list[j][1], (int)node_list[j][2], 0, node_list[j][0], (int)node_list[j][1], (int)node_list[j][2]);
									int v_id = add_vertex(graph, v);
									hashmapInsert(hashmap, v_id, node_list[j][0]);

								}
								x = 0;
								y = 0;
								while((char)data != "$"){
									char* text2 = "";
									while((char)data != ";"){
										char* text = "";
										while((char)data != ","){
											data = alt_up_sd_card_read(file);
											strcat(text, (char)data);
										}
										edge_list[x][y] = text;
										y++;
										alt_up_sd_card_read(file);
									}
									y = 0;
									x++;
									alt_up_sd_card_read(file);
									alt_up_sd_card_read(file);
									alt_up_sd_card_read(file);//Account for /n
								}
								for (int j = 0; j < x; j++){
									int v1_id = hashmapGet(hashmap, edge_list[j][0]);
									int v2_id = hashmapGet(hashmap, edge_list[j][1]);
									vertex v1 = get_vertex(graph, v1_id);
									vertex v2 = get_vertex(graph, v2_id);
									cost cost1 = {0};
									cost1.distance_cost = (int) edge_list[j][2];
									add_edge(v1, v2, cost);

								}


								printf("Finished reading file!!!!\n");
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

									char* node_list[3];
									char* edge_list[3];
									int x = 0;
									int y = 0;
									if (strcmp(name, filename)== 0){

										short data =0;
										printf("Current file: %s\n", name);
										printf("My name: %s\n", filename);
										while((char)data != "$"){
											char* text2 = "";
											while((char)data != ";"){
												char* text = "";
												while((char)data != ","){
													data = alt_up_sd_card_read(file);
													strcat(text, (char)data);
												}
												node_list[x][y] = text;
												y++;
												alt_up_sd_card_read(file);
											}
											y = 0;
											x++;
											alt_up_sd_card_read(file);
											alt_up_sd_card_read(file);
											alt_up_sd_card_read(file);//Account for /n
										}
										alt_up_sd_card_read(file);
										alt_up_sd_card_read(file);
										hashmap* hashmap = hashmapCreate(20);

										for (int j = 0; j < x; j++){
											vertex v = init_vertex((int)node_list[j][1], (int)node_list[j][2], 0, node_list[j][0], (int)node_list[j][1], (int)node_list[j][2]);
											int v_id = add_vertex(graph, v);
											hashmapInsert(hashmap, v_id, node_list[j][0]);

										}
										x = 0;
										y = 0;
										while((char)data != "$"){
											char* text2 = "";
											while((char)data != ";"){
												char* text = "";
												while((char)data != ","){
													data = alt_up_sd_card_read(file);
													strcat(text, (char)data);
												}
												edge_list[x][y] = text;
												y++;
												alt_up_sd_card_read(file);
											}
											y = 0;
											x++;
											alt_up_sd_card_read(file);
											alt_up_sd_card_read(file);
											alt_up_sd_card_read(file);//Account for /n
										}
										for (int j = 0; j < x; j++){
											int v1_id = hashmapGet(hashmap, edge_list[j][0]);
											int v2_id = hashmapGet(hashmap, edge_list[j][1]);
											vertex v1 = get_vertex(graph, v1_id);
											vertex v2 = get_vertex(graph, v2_id);
											cost cost1 = {0};
											cost1.distance_cost = (int) edge_list[j][2];
											add_edge(v1, v2, cost);

										}

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
	}
	else{
		printf("Can't open device\n");
	}
	return;
}
