#ifndef __STATE_STRUCTS__
#define __STATE_STRUCTS__

#define MAXNUMSTATES 15

struct state
{
	int state_queue[MAXNUMSTATES];
	int next_state_queue[MAXNUMSTATES];
	int states_remaining;
	int next_states_remaining;

	int current_state_index;
	int current_state;
};


void init_state(struct state State);
void update_state(struct state State);
void end_state(struct state State);

#endif
