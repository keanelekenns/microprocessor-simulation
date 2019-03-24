#include "memory.h"

void init_memory(struct mem Memory){

	// Set program counter to be first stack slot
	mem.program_counter = 0x00;

	// Initialize program counter to zero
	mem.address_stack[mem.program_counter] = 0x0000;

}
