#include "startup.h"

// Purpose: 	Kickoff the program
// Input: 		none
// Output: 		PASS/FAIL returned
int main(void){
	// Infinite loop for everything
	System_Clock_Init();
	while(1) {
		start();
	}
}
