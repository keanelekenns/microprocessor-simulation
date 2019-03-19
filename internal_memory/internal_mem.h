#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#ifndef INTERNAL_MEMORY_STRUCTS
#define INTERNAL_MEMORY_STRUCTS

struct scratchpad
{ 
	uint8_t Accumulator[8];
	uint8_t B[8];
	uint8_t C[8];
	uint8_t D[8];
	uint8_t E[8];
	uint8_t H[8];
	uint8_t L[8];
};

struct address_stack
{
	// Stores current program counter
	uint8_t Address_Counter[3];

	// 8 14-bit slocks to store addresses
	uint8_t Address_Stack[8][14];

};


#endif

