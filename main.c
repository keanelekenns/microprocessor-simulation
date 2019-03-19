#include <stdio.h>
#include <stdlib.h>
#include "internal_memory/internal_mem.h"
#include "devices.h"
#include "i_o.h"


#define MAXNUMSTATES 15


struct scratchpad spad;
struct address_stack stack;


int main(){

	int state_queue[MAXNUMSTATES];
	int next_state_queue[MAXNUMSTATES];
	int states_remaining;
	int next_states_remaining;

	int current_state_index;
	int current_state;

	//Pre-load state queue to fetch first instruction from memory.
	state_queue[0] = 1;
	state_queue[1] = 2;
	state_queue[2] = 3;
	states_remaining = 3;
	// Pre-load next state queue for testing
	next_state_queue[0] = 1;
	next_state_queue[1] = 2;
	next_state_queue[2] = 3;
	next_states_remaining = 3;

	current_state_index = 0;

	// Main program loop; each iteration of the loop is one processor state.
	for (;;)
	{
		// 
		current_state = state_queue[current_state_index];



		current_state_index++;
		states_remaining--;
		if (states_remaining == 0){
			// Copy next_state_queue to state_queue and new_states_remaining to states_remaining
			for (int i=0; i< MAXNUMSTATES; i++){
				state_queue[i] = next_state_queue[i];
			}
			states_remaining = next_states_remaining;
			current_state_index = 0;
		}
	}


	exit(0);
}

