/*
UVIC Spring 2019 CSC350 Project 2: Team Stony Lake - Intel 8008 microprocessor Simulation
This file implements the functionality of the Arithmetic Logical Unit (ALU) component.

Filename: ALU.c
Created by: Keanelek Enns
Last Edited: March 21, 2019
*/

//temporary registers used by the ALU
uint8_t temp_A = 0;
uint8_t temp_B = 0;

//flip flops used for condition checking
uint8_t flip_flops = 0;

/*
The flip_flops byte contains the carry, zero, sign, and parity
flags in its lower 4 bits. Carry = bit 0, zero = bit 1, sign = bit 2,
and parity = bit 3. flip_flops = 0b0000PSZC
*/
uint8_t get_flip_flops(){
	return flip_flops;
}

//getters and setters for the ALU's temp registers
void set_temp_A(uint8_t val){
	temp_A = val;
}

void set_temp_B(uint8_t val){
	temp_B = val;
}

uint8_t get_temp_A(){
	return temp_A;
}

uint8_t get_temp_B(){
	return temp_B;
}

/*
This function takes the result of an ALU operation and determines whether
the Parity, Sign, or Zero flip flops should be set. The carry flip flop
is not modified as it is often dealt with in a more context specific manner.
*/
void set_PSZ_flip_flops(uint8_t result){
	if(!result){
		flip_flops = flip_flops | 0b00000010;//set zero flag
	}else{
		flip_flops = flip_flops & 0b11111101;//unset zero flag
	}
	if(result & 0b10000000){
		flip_flops = flip_flops | 0b00000100;//set sign flag
	}else{
		flip_flops = flip_flops & 0b11111011;//unset sign flag
	}
	if(!(result & 0b00000001)){
		flip_flops = flip_flops | 0b00001000;//set parity flag
	}else{
		flip_flops = flip_flops & 0b11110111;//unset parity flag
	}
}


/* ALU OPERATIONS

All of the ALU operations do work on the accumulator,
this is why the first argument of each function is 
named accumulator (it is necessary for the 
accumulator value to be passed in as the first argument).
Note that arg2 could be the value of another index register,
an immediate value, or a value from memory.

*/

uint8_t ADD(uint8_t accumulator, uint8_t arg2){
	uint8_t temp = accumulator + arg2;
	// if both operands have same sign, but the result's sign does not match them, then we have overflow
	if(((accumulator & 0b10000000) == (arg2 & 0b10000000)) 
		&& ((temp & 0b10000000) != (accumulator & 0b10000000))){
		flip_flops = flip_flops | 0b00000001;//set carry flag
	}else{
		flip_flops = flip_flops & 0b11111110;//unset carry flag
	}
	set_PSZ_flip_flops(temp);
	return temp;
}

uint8_t ADD_with_carry(uint8_t accumulator, uint8_t arg2){
	uint8_t temp = accumulator + arg2 + (flip_flops & 0b00000001);
	// if both operands have same sign, but the result's sign does not match them, then we have overflow/underflow
	if(((accumulator & 0b10000000) == (arg2 & 0b10000000)) 
		&& ((temp & 0b10000000) != (accumulator & 0b10000000))){
		flip_flops = flip_flops | 0b00000001;//set carry flag
	}else{
		flip_flops = flip_flops & 0b11111110;//unset carry flag
	}
	set_PSZ_flip_flops(temp);
	return temp;
}

uint8_t SUBTRACT(uint8_t accumulator, uint8_t arg2){
	uint8_t temp = accumulator - arg2;
	// if operands have different signs, and the result has the sign of arg2, then we have overflow/underflow
	if(((accumulator & 0b10000000) != (arg2 & 0b10000000)) 
		&& ((temp & 0b10000000) == (arg2 & 0b10000000))){
		flip_flops = flip_flops | 0b00000001;//set carry flag
	}else{
		flip_flops = flip_flops & 0b11111110;//unset carry flag
	}
	set_PSZ_flip_flops(temp);
	return temp;
}

uint8_t SUBTRACT_with_borrow(uint8_t accumulator, uint8_t arg2){
	uint8_t temp = accumulator - arg2 - (flip_flops & 0b00000001);
	// if operands have different signs, and the result has the sign of arg2, then we have overflow/underflow
	if(((accumulator & 0b10000000) != (arg2 & 0b10000000)) 
		&& ((temp & 0b10000000) == (arg2 & 0b10000000))){
		flip_flops = flip_flops | 0b00000001;//set carry flag
	}else{
		flip_flops = flip_flops & 0b11111110;//unset carry flag
	}
	set_PSZ_flip_flops(temp);
	return temp;
}

uint8_t AND(uint8_t accumulator, uint8_t arg2){
	uint8_t temp = accumulator & arg2;
	//logical ops cannot set carry bit I don't think
	set_PSZ_flip_flops(temp);
	return temp;
}

uint8_t EXCLUSIVE_OR(uint8_t accumulator, uint8_t arg2){
	uint8_t temp = accumulator ^ arg2;
	//logical ops cannot set carry bit I don't think
	set_PSZ_flip_flops(temp);
	return temp;
}

uint8_t OR(uint8_t accumulator, uint8_t arg2){
	uint8_t temp = accumulator | arg2;
	//logical ops cannot set carry bit I don't think
	set_PSZ_flip_flops(temp);
	return temp;
}

// Compare accumulator (accumulator) with other value (arg2)
// If accumulator == arg2, zero flag is set (unset otherwise)
// If accumulator < arg2, carry flag is set (unset otherwise)
void COMPARE(uint8_t accumulator, uint8_t arg2){ 
	if(accumulator < arg2){
		flip_flops = flip_flops | 0b00000001;//set carry flag
	}else{
		flip_flops = flip_flops & 0b11111110;//unset carry flag
	}
	
	uint8_t temp = arg2 - accumulator;
	
	set_PSZ_flip_flops(temp);
}

//The documentation says the carry flip flop is not set by INCREMENT or DECREMENT (not entirely sure why)
//@param reg - any register that is not the accumulator
uint8_t INCREMENT(uint8_t reg){
	reg = reg + 1;
	set_PSZ_flip_flops(reg);
	return reg;
}

uint8_t DECREMENT(uint8_t reg){
	reg = reg - 1;
	set_PSZ_flip_flops(reg);
	return reg;
}

/*
The rotate instructions are not technically part of the ALU, but if we want
the ALU to be the only modifier of the flip_flops, then they must be here. 
Note also that the rotate instructions are only supposed to work on the 
Accumulator, but since I do not know how the ALU will access it, I am just 
listing the accumulator as an argument (we can change this once we know).
*/
uint8_t RLC(uint8_t accumulator){
	if(accumulator & 0b10000000){ //determine value of A7
		accumulator = accumulator << 1;
		flip_flops = flip_flops | 0b00000001;//put 1 into A0 and into the carry flip flop
		accumulator = accumulator | 0b00000001;
	}else{
		accumulator = accumulator << 1;
		flip_flops = flip_flops & 0b11111110;//put 0 into A0 and into the carry flip flop
	}
	return accumulator;
}

uint8_t RRC(uint8_t accumulator){
	if(accumulator & 0b00000001){ //determine value of A0
		accumulator = accumulator >> 1;
		flip_flops = flip_flops | 0b00000001;//put 1 into A7 and into the carry flip flop
		accumulator = accumulator | 0b10000000;
	}else{
		accumulator = accumulator >> 1;
		flip_flops = flip_flops & 0b11111110;//put 0 into A7 and into the carry flip flop
	}
	return accumulator;
}

uint8_t RAL(uint8_t accumulator){
	uint8_t temp = accumulator >> 7; //move A7 to A0 location
	accumulator = accumulator << 1;
	accumulator = accumulator | (flip_flops & 0b00000001); //put carry bit in accumulator
	flip_flops = flip_flops & 0b11111110;
	flip_flops = flip_flops | temp;//put A7 into carry bit

	return accumulator;
}

uint8_t RAR(uint8_t accumulator){
	uint8_t temp = accumulator & 0b00000001; //mask A0
	accumulator = accumulator >> 1;
	accumulator = accumulator | ((flip_flops & 0b00000001) << 7); //put carry bit in A7
	flip_flops = flip_flops & 0b11111110;
	flip_flops = flip_flops | temp;//put A0 into carry bit
	
	return accumulator;
}