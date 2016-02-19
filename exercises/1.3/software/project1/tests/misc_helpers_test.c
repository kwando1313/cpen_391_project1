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

	if (alphaBetize("a", "A") != 0){
		printf("Test failed. Should return zero because they are equal.");
		return -1;
	}

	if (alphaBetize("a test", "A TEST") != 0){
		printf("Test failed. Should return zero because they are equal.");
		return -1;
	}

	if (alphaBetize("b test", "aTEST") <= 0){
		printf("Test failed. Should return a value greater than zero.");
		return -1;
	}
	if (alphaBetize("123", "1234") >= 0){
		printf("Test failed. Should return a value less than zero.");
		return -1;
	}

	if(alphaBetize("2", "1") <= 0){
		printf("Test failed. Should return a value greater than zero.");
		return -1;
	}

	if(alphaBetize("2A weoifj werw98q3r voiswf", "1 weoijw wog e9gj death") <= 0){
		printf("Test failed. Should return a value greater than zero.");
		return -1;
	}


	if(alphaBetize("a car", "a cat") >= 0){
		printf("Test failed. Should return a value less than zero.");
		return -1;
	}

	if(alphaBetize("a cat", "a car") <= 0){
		printf("Test failed. Should return a value greater than zero.");
		return -1;
	}

	if(alphaBetize("a Cat", "a caT") != 0){
		printf("Test failed. Should return zero.");
		return -1;
	}
	printf("All tests passed!");
	return 0;
}
