#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#ifndef __mem_h__
#define __mem_h__
uint8_t regA;
uint8_t regB;
uint8_t scratchPad[7];
uint8_t simMemory[16384];
uint8_t highAddress;
uint8_t lowAddress;

#endif
