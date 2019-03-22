#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#ifndef INTERNAL_MEMORY_STRUCTS
#define INTERNAL_MEMORY_STRUCTS

struct scratchpad
{ 
	uint8_t Accumulator;
	uint8_t B;
	uint8_t C;
	uint8_t D;
	uint8_t E;
	uint8_t H;
	uint8_t L;
};

struct address_stack
{
	// Stores current program counter; we only use three bits of it.
	uint8_t Address_Counter;

	// 8 14-bit slocks to store addresses
	uint16_t Address_Stack[8];

};


#endif

