#include <stdio.h>
#include "rs232.h"

int main(void) {

	test_rs232();

	return 0;
}

/********************
 * The following lines are for testing the SD Card, hence why they are commented out for now.

#include <stdio.h>
#include <altera_up_sd_card_avalon_interface.h>
int main(void){
	alt_up_sd_card_dev* device_reference = NULL;
	int connected = 0;
	printf("Opening SDCard\n");
	if ((device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0")) == NULL){
		printf("SDCard Open FAILED\n");
		return 0 ;
	}
	else
		printf("SDCard Open PASSED\n");

	if(device_reference != NULL ) {
		while(1) {
			if((connected == 0) && (alt_up_sd_card_is_Present())){
				printf("Card connected.\n");

				if(alt_up_sd_card_is_FAT16()) {
					printf("FAT16 file system detected.\n");
				}


				else{
					printf("Unknown file system.\n");
				}
				connected = 1;
			} else if((connected == 1) && (alt_up_sd_card_is_Present() == false)){
				printf("Card disconnected.\n");
				connected =0;
			}
		}
	}
	else{
		printf("Can't open device\n");
	}
	return 0;
}

 *
 */
