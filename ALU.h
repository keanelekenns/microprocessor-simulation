/*
UVIC Spring 2019 CSC350 Project 2: Team Stony Lake - Intel 8008 microprocessor Simulation
This is the header file for the Arithmetic Logical Unit (ALU) component.

Each operational function (everything but get_flip_flops) returns the result of the operation 
except for COMPARE(), which sets flag bits accordingly.

Filename: ALU.h
Created by: Keanelek Enns
Last Edited: March 19, 2019
Last Edited by: Keanelek Enns
*/

#include "ALU.c"

/*
The flip_flops byte contains the carry, zero, sign, and parity
flags in its lower 4 bits. Carry = bit 0, zero = bit 1, sign = bit 2,
and parity = bit 3. flip_flops = 0b0000PSZC
*/
uint8_t get_flip_flops();

uint8_t ADD(uint8_t arg1, uint8_t arg2);

uint8_t ADD_with_carry(uint8_t arg1, uint8_t arg2);

uint8_t SUBTRACT(uint8_t arg1, uint8_t arg2);

uint8_t SUBTRACT_with_borrow(uint8_t arg1, uint8_t arg2);

uint8_t AND(uint8_t arg1, uint8_t arg2);

uint8_t EXCLUSIVE_OR(uint8_t arg1, uint8_t arg2);

uint8_t OR(uint8_t arg1, uint8_t arg2);

// Compare accumulator (arg1) with other value (arg2)
// If arg1 == arg2, zero flag is set (unset otherwise)
// If arg1 < arg2, carry flag is set (unset otherwise)
void COMPARE(uint8_t arg1, uint8_t arg2);

uint8_t INCREMENT(uint8_t arg1);

uint8_t DECREMENT(uint8_t arg1);

/*
The rotate instructions are not technically part of the ALU, but if we want
the ALU to be the only modifier of the flip_flops, then they must be here. 
Note also that the rotate instructions are only supposed to work on the 
Accumulator, but since I do not know how the ALU will access it, I am just 
listing the accumulator as an argument (we can change this once we know).
*/
uint8_t RLC(uint8_t accumulator);

uint8_t RRC(uint8_t accumulator);

uint8_t RAL(uint8_t accumulator);

uint8_t RAR(uint8_t accumulator);