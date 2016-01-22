#include <stdio.h>
#include "rs232.h"

int main(void) {

	test_rs232();

	return 0;
}


// The following lines are for testing the SD Card, hence why they are commented out for now.

//#include <stdio.h>
//#include <altera_up_sd_card_avalon_interface.h>
//int main(void){
//	alt_up_sd_card_dev* device_reference = NULL;
//	int connected = 0;
//	printf("Opening SDCard\n");
//	if ((device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0")) == NULL){
//		printf("SDCard Open FAILED\n");
//		return 0 ;
//	}
//	else
//		printf("SDCard Open PASSED\n");
//
//	if(device_reference != NULL ) {
//		while(1) {
//			if((connected == 0) && (alt_up_sd_card_is_Present())){
//				printf("Card connected.\n");
//
//				if(alt_up_sd_card_is_FAT16()) {
//					printf("FAT16 file system detected.\n");
//
//					char * name;
//					if (alt_up_sd_card_find_first("/", name) == 0){
//						printf(name);
//						short int file = alt_up_sd_card_fopen(name, false);
//						if (file == -1){
//							printf("This file could not be opened.");
//						}
//						else if (file == -2){
//							printf("This file is already opened.");
//						}
//						else {
//							printf("Reading file...");
//							while(alt_up_sd_card_read(file) > 0){
//								printf("Continuing to read file...");
//							}
//							printf("Finished reading file!");
//						}
//						while(alt_up_sd_card_find_next(name) == 0){
//							printf(name);
//							short int file = alt_up_sd_card_fopen(name, false);
//							if (file == -1){
//								printf("This file could not be opened.");
//							}
//							else if (file == -2){
//								printf("This file is already opened.");
//							}
//							else {
//								printf("Reading file...");
//								while(alt_up_sd_card_read(file) > 0){
//									continue;
//								}
//								printf("Finished reading file!");
//							}
//						}
//					}
//					else if (alt_up_sd_card_find_first("/", name) == -1){
//						printf("No files were found in this directory.");
//						printf("Going to create a file in this directory...");
//						short int file = alt_up_sd_card_fopen("test.txt", true);
//
//						if (file == -1){
//							printf("This file could not be opened.");
//						}
//						else if (file == -2){
//							printf("This file is already opened.");
//						}
//						else {
//							printf("File created!");
//							for (int x = 0; x < 1024; x++){
//								if (alt_up_sd_card_write(file, 'A') == 0){
//									printf("There was an error writing to the file...");
//									return 0;
//								}
//							}
//							alt_up_sd_card_fclose(file);
//						}
//
//					}
//					else if (alt_up_sd_card_find_first("/", name) == 1){
//						printf("This is an invalid directory.");
//					}
//					else if (alt_up_sd_card_find_first("/", name) == 2){
//						printf("The SD card has either been disconnected, or is NOT a FAT16 type.");
//					}
//				}
//
//
//				else{
//					printf("Unknown file system.\n");
//				}
//				connected = 1;
//			} else if((connected == 1) && (alt_up_sd_card_is_Present() == 0)){
//				printf("Card disconnected.\n");
//				connected =0;
//			}
//		}
//	}
//	else{
//		printf("Can't open device\n");
//	}
//	return 0;
//}


