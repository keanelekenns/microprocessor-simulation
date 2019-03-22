#include <stdint.h>

#ifndef __MEMORY_STRUCTS__
#define __MEMORY_STRUCTS__

struct memory
{
	
	// scratchpad[0]: accumulator
	// scratchpad[1]: B
	// scratchpad[2]: C
	// scratchpad[3]: D
	// scratchpad[4]: E
	// scratchpad[5]: H
	// scratchpad[6]: L
	uint8_t scratchpad[7];


	// 8 14-bit slots to store addresses; we only use 14 bits of each of these.
	uint16_t ProgramCounter[8];

	// External memory array
	uint8_t ExternalMemory[16384];

	// Instruction register
	uint16_t InstructionRegister;

};

void init_memory(struct memory Memory);

#endif

