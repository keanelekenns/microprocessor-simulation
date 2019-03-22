#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#ifndef INTERNAL_MEMORY_STRUCTS
#define INTERNAL_MEMORY_STRUCTS

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

	// Stores current program counter; we only use three bits of it.
	uint8_t Address_Counter;

	// 8 14-bit slots to store addresses; we only use 14 bits of each of these.
	uint16_t Address_Stack[8];

	// External memory array
	uint8_t Memory[16384];

}




#endif

