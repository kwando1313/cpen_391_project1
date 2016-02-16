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
	printf("\nTest 1: ");
	if (hashmapCount(hmap) != 0){
		printf("Failed. Hashmap does not initialize to empty.");
		return -1;
	}
	printf("Passed. Hashmap initializes empty.");

	hashmapInsert(hmap, 1, 1);
	printf("\nTest 2: ");
	if (hashmapCount(hmap) != 1){
		printf("Failed. Hashmap does not have proper count of elements.");
		return -1;
	}
	printf("Passed. Hashmap has proper count of elements.");

	int test = 0;

	test = (int *) hashmapGet(hmap, 1);

	printf("\nTest 3: ");
	if (test != 1){
		printf("Failed. Value found inside was actually %d ", test);
		return -1;
	}
	printf("Passed. Value found inside was 1.");

	hashmapInsert(hmap, "Word", 2);

	char* word;

	word = (char*) hashmapGet(hmap, 2);
	printf("\nTest 4: ");
	if (strcmp(word, "Word") != 0){
		printf("Failed. The word found inside was actually %s", word);
		return -1;
	}
	printf("Passed. Word found inside was Word.");

	test = (int*) hashmapRemove(hmap, 1);

	printf("\nTest 5: ");
	if (test == -1){
		printf("Failed. HASHMAPERROR returned.");
		return -1;
	}
	if (hashmapCount(hmap) != 1){
		printf("Failed. Hashmap value not actually removed");
		return -1;
	}
	printf("Passed. Value was properly removed from the hashmap.");


	printf("\nTest 6: ");
	hashmapInsert(hmap, 2, 1);
	test = (int *) hashmapGet(hmap, 1);
	if (test != 2){
		printf("Failed. Value was not inserted.");
		return -1;
	}
	printf("Passed. Value was properly inserted.");

	printf("\nTest 7: ");
	hashmapInsert(hmap, 7, 1);
	test = (int *) hashmapGet(hmap, 1);
	if (test != 7){
		printf("Failed. Value was not replaced.");
		return -1;
	}
	printf("Passed. Value was properly replaced.");

	printf("\nTest 8: ");
	hashmapInsert(hmap, 'd', 13);
	char c = (char) hashmapGet(hmap, 13);
	if (c != 'd'){
		printf("Failed. Char 'd' was not properly inserted");
		return -1;
	}
	printf("Passed. Char 'd' was properly inserted");

	printf("\nTest 9: ");
	hashmapInsert(hmap, 9, 4294967295);
	test = (int *) hashmapGet(hmap, 4294967295);
	if (test != 9){
		printf("Failed. 9 was not inserted");
		return -1;
	}
	printf("Passed. 9 was properly inserted");

	test = hashmapRemove(hmap, 11);

	printf("\nTest 10: ");
	if (test != -1){
		printf("Failed. ERROR should be returned.");
		return -1;
	}
	printf("Passed. ERROR was thrown, as we were removing something that doesn't exist.");

	test = hashmapGet(hmap, 11);

	printf("\nTest 11: ");
	if (test != -1){
		printf("Failed. ERROR should be returned.");
		return -1;
	}
	printf("Passed. ERROR was thrown, as we were retrieving something that doesn't exist.");

	printf("\nTest 12: ");
	hashmapDelete(hmap);

	hashmap* hmap2 = hashmapCreate(10);
	int x = 0;
	while(x < 200){
		hashmapInsert(hmap2, x, x);
		int test2 = (int*) hashmapGet(hmap, x);
		if (test2 != x){
			printf("Failed. Improper value retrieved.");
			return -1;
		}
		x++;
	}
	printf("Passed. Hashmap re-sizes and retrieves proper values.");
	printf("\nTest 13: ");
	x = 0;
	while (x< 200){
		hashmapGet(hmap, 1);
		int test2 = (int*) hashmapGet(hmap, 1);
		if (test2 != 1){
			printf("Failed. Constant retrieval does not work.");
			return -1;
		}
		x++;
	}
	printf("Passed. Constant retrieval works.");

	printf("\nTest 14: ");
	x = 0;
	while (x < 200){
		int test2 = (int*) hashmapRemove(hmap, x);
		if (test2 == -1){
			printf("Failed. ERROR was thrown, when it shouldn't have been.");
			return -1;
		}
		x++;
	}
	printf("Passed. Hashmap properly removes all these values.");
	printf("\n\nAll tests passed!\n");
	return 0;
}
