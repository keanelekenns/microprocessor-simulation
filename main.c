#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "state.h"
#include "decode.h"
#include "devices.h"
//#include "ALU.h"


struct state State;

int T1_execute(){
	return 0;
}
int T2_execute(){
	return 0;
}
int T3_execute(){
	return 0;
}
int T4_execute(){
	return 0;
}
int T5_execute(){
	return 0;
}


int main(){

	// Initialize components
	init_state(State);
	//should be able to just call mem.<whatyouneed> to access the variables


	// Main program loop; each iteration of the loop is one processor state.
	for (;;)
	{
		// advance to next TState we have queued
		update_state(State);

		switch (State.current_state){
			case 1: T1_execute();

			case 2: T2_execute();

			case 3: T3_execute();

			case 4: T4_execute();

			case 5: T5_execute();
		}


		end_state(State);
	}


	exit(0);
}

