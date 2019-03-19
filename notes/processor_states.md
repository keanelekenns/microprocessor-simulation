# Processor States

For simplification, forget about WAIT, STOPPED, READY, and INTERRUPT for now.

## Model

If we forget about interrupts and the READY state, each instruction takes at most 15 states (3 memory cycles). Each instruction has an associated state array that lists the states the processor will pass through. The main loop theniterates through these states.

Each fetch puts the list of states of the new instruction in next_state_queue and how many states it takes in next_states_remaining.

Whenever we run out of states (states_remaining == 0), copy the contents of next_state_queue into state_queue and num_new_states into states_remaining.