#include "misc_helpers.h"

int alphaBetize_test(void){
	printf("Starting alphaBetize test...\n");

	if (alphaBetize("testa", "TeStb") >= 0){
		printf("Test failed. Should return a value less than zero, since testa is less than TeStb");
		return -1;
	}

	if (alphaBetize("a", "B") >= 0){
		printf("Test failed. Should return a value less than zero, since a is less than b");
		return -1;
	}

	if (alphaBetize("b", "A") <= 0){
		printf("Test failed. Should return a value greater than zero, since b is bigger than a");
		return -1;
	}

	if (alphaBetize("a", "a") != 0){
		printf("Test failed. Should return zero because they are equal.");
		return -1;
	}

	if (alphaBetize("a", "A") >= 0){
		printf("Test failed. Lower case letters are smaller than upper case letters.");
		return -1;
	}
	printf("All tests passed!");
	return 0;
}
