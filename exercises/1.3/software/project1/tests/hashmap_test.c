/*
 * hashmap_test.c
 *
 *  Created on: 2016-02-16
 *      Author: kwando1313
 */

#include "hashmap.h"

int hashmap_test(void) {
	printf("Starting hashmap tests...\n\n");

	hashmap* hmap = hashmapCreate(20);
	if (hashmapCount(hmap) != 0){
		printf("\nTest failed. Hashmap does not initialize to empty.");
		return -1;
	}

	hashmapInsert(hmap, 1, 1);
	if (hashmapCount(hmap) != 1){
		printf("\nTest failed. Hashmap does not have proper count of elements.");
		return -1;
	}
	int test = 0;

	test = (int *) hashmapGet(hmap, 1);

	if (test != 1){
		printf("\nTest failed. Value found inside was actually %d ", test);
		return -1;
	}
	hashmapInsert(hmap, "Word", 2);

	char* word;

	word = (char*) hashmapGet(hmap, 2);
	if (strcmp(word, "Word") != 0){
		printf("\nTest failed. The word found inside was actually %s", word);
		return -1;
	}

	test = (int*) hashmapRemove(hmap, 1);

	printf("\nTest 5: ");
	if (test == -1){
		printf("\nTest failed. HASHMAPERROR returned.");
		return -1;
	}
	if (hashmapCount(hmap) != 1){
		printf("\nTest failed. Hashmap value not actually removed");
		return -1;
	}


	printf("\nTest 6: ");
	hashmapInsert(hmap, 2, 1);
	test = (int *) hashmapGet(hmap, 1);
	if (test != 2){
		printf("\nTest failed. Value was not inserted.");
		return -1;
	}

	hashmapInsert(hmap, 7, 1);
	test = (int *) hashmapGet(hmap, 1);
	if (test != 7){
		printf("\nTest failed. Value was not replaced.");
		return -1;
	}

	hashmapInsert(hmap, 'd', 13);
	char c = (char) hashmapGet(hmap, 13);
	if (c != 'd'){
		printf("\nTest failed. Char 'd' was not properly inserted");
		return -1;
	}

	hashmapInsert(hmap, 9, 4294967295);
	test = (int *) hashmapGet(hmap, 4294967295);
	if (test != 9){
		printf("\nTest failed. 9 was not inserted");
		return -1;
	}

	test = hashmapRemove(hmap, 11);

	if (test != -1){
		printf("\nTest failed. ERROR should be returned.");
		return -1;
	}

	test = hashmapGet(hmap, 11);

	if (test != -1){
		printf("\nTest failed. ERROR should be returned.");
		return -1;
	}
	hashmapDelete(hmap);

	hashmap* hmap2 = hashmapCreate(10);
	int x = 0;
	while(x < 200){
		hashmapInsert(hmap2, x, x);
		int test2 = (int*) hashmapGet(hmap, x);
		if (test2 != x){
			printf("\nTest failed. Improper value retrieved.");
			return -1;
		}
		x++;
	}
	x = 0;
	while (x< 200){
		hashmapGet(hmap, 1);
		int test2 = (int*) hashmapGet(hmap, 1);
		if (test2 != 1){
			printf("\nTest failed. Constant retrieval does not work.");
			return -1;
		}
		x++;
	}
	x = 0;
	while (x < 200){
		int test2 = (int*) hashmapRemove(hmap, x);
		if (test2 == -1){
			printf("\nTest failed. ERROR was thrown, when it shouldn't have been.");
			return -1;
		}
		x++;
	}
	printf("\n\nAll hashmap tests passed!\n");
	hashmapDelete(hmap2);
	return 0;
}
