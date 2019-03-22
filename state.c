#include "state.h"

void init_state(struct state State){
	//Pre-load state queue to fetch first instruction from memory.
	State.state_queue[0] = 1;
	State.state_queue[1] = 2;
	State.state_queue[2] = 3;
	State.states_remaining = 3;
	// Pre-load next state queue for testing
	State.next_state_queue[0] = 1;
	State.next_state_queue[1] = 2;
	State.next_state_queue[2] = 3;
	State.next_states_remaining = 3;

	State.current_state_index = 0;
}

void update_state(struct state State){
	State.current_state = State.state_queue[State.current_state_index];
}

void end_state(struct state State){
	State.current_state_index++;
	State.states_remaining--;
	if (State.states_remaining == 0){
		// Copy next_state_queue to state_queue and new_states_remaining to states_remaining
		for (int i=0; i< MAXNUMSTATES; i++){
			State.state_queue[i] = State.next_state_queue[i];
		}
		State.states_remaining = State.next_states_remaining;
		State.current_state_index = 0;
	}
}
