#include "ColourPallette.h"
#include "hashmap.h"

#define NUM_COLOURS 256


// maps 24bit RGB to 8bit pallette addr
hashmap* colours_hashmap;

void setUpPallete(void){
	colours_hashmap = hashmapCreate(NUM_COLOURS);
	for (int i = 0; i<NUM_COLOURS; i++){
		printf("inserting colour: i %d, rgb %x\n", i, (long)getRGB(i));
		hashmapInsert(colours_hashmap, (void*)i, (long)getRGB(i));
	}
}

int getPalleteAddr(int RGB){
	return (int)hashmapGet(colours_hashmap, (long)(RGB));
}

int getRGB(int addr){
	return ColourPalletteData[addr];
}
