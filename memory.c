#include "memory.h"

void init_memory(struct memory Memory){

	// Set program counter to be first stack slot
	Memory.Address_Counter = 0x00;

	// Initialize program counter to zero
	Memory.Address_Stack[Memory.Address_Counter] = 0x0000;

}
