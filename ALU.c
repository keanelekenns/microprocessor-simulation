/*
UVIC Spring 2019 CSC350 Project 2: Team Stony Lake - Intel 8008 microprocessor Simulation
This file implements the functionality of the Arithmetic Logical Unit (ALU) component.

Filename: ALU.c
Created by: Keanelek Enns
Last Edited: March 19, 2019
*/

uint8_t temp_A, temp_B; //temporary registers used by the ALU
uint8_t flip_flops = 0;

/*
The flip_flops byte contains the carry, zero, sign, and parity
flags in its lower 4 bits. Carry = bit 0, zero = bit 1, sign = bit 2,
and parity = bit 3. flip_flops = 0b0000PSZC
*/
uint8_t get_flip_flops(){
	return flip_flops;
}

uint8_t ADD(uint8_t arg1, uint8_t arg2){
	temp_A = arg1 + arg2;
	if(temp_A < arg1){
		flip_flops = flip_flops | 0b00000001;//set carry flag
	}else{
		flip_flops = flip_flops & 0b11111110;//unset carry flag
	}
	if(!temp_A){
		flip_flops = flip_flops | 0b00000010;//set zero flag
	}else{
		flip_flops = flip_flops & 0b11111101;//unset zero flag
	}
	if(temp_A & 0b10000000){
		flip_flops = flip_flops | 0b00000100;//set sign flag
	}else{
		flip_flops = flip_flops & 0b11111011;//unset sign flag
	}
	if(!(temp_A & 0b00000001)){
		flip_flops = flip_flops | 0b00001000;//set parity flag
	}else{
		flip_flops = flip_flops & 0b11110111;//unset parity flag
	}
	return temp_A;
}

uint8_t ADD_with_carry(uint8_t arg1, uint8_t arg2){
	temp_A = arg1 + arg2 + (flip_flops & 0b00000001);
	if(temp_A < arg1){
		flip_flops = flip_flops | 0b00000001;//set carry flag
	}else{
		flip_flops = flip_flops & 0b11111110;//unset carry flag
	}
	if(!temp_A){
		flip_flops = flip_flops | 0b00000010;//set zero flag
	}else{
		flip_flops = flip_flops & 0b11111101;//unset zero flag
	}
	if(temp_A & 0b10000000){
		flip_flops = flip_flops | 0b00000100;//set sign flag
	}else{
		flip_flops = flip_flops & 0b11111011;//unset sign flag
	}
	if(!(temp_A & 0b00000001)){
		flip_flops = flip_flops | 0b00001000;//set parity flag
	}else{
		flip_flops = flip_flops & 0b11110111;//unset parity flag
	}
	return temp_A;
}

uint8_t SUBTRACT(uint8_t arg1, uint8_t arg2){
	temp_A = arg1 - arg2;
	if(temp_A > arg1){
		flip_flops = flip_flops | 0b00000001;//set carry flag
	}else{
		flip_flops = flip_flops & 0b11111110;//unset carry flag
	}
	if(!temp_A){
		flip_flops = flip_flops | 0b00000010;//set zero flag
	}else{
		flip_flops = flip_flops & 0b11111101;//unset zero flag
	}
	if(temp_A & 0b10000000){
		flip_flops = flip_flops | 0b00000100;//set sign flag
	}else{
		flip_flops = flip_flops & 0b11111011;//unset sign flag
	}
	if(!(temp_A & 0b00000001)){
		flip_flops = flip_flops | 0b00001000;//set parity flag
	}else{
		flip_flops = flip_flops & 0b11110111;//unset parity flag
	}
	return temp_A;
}

uint8_t SUBTRACT_with_borrow(uint8_t arg1, uint8_t arg2){
	temp_A = arg1 - arg2 - (flip_flops & 0b00000001);
	if(temp_A > arg1){
		flip_flops = flip_flops | 0b00000001;//set carry flag
	}else{
		flip_flops = flip_flops & 0b11111110;//unset carry flag
	}
	if(!temp_A){
		flip_flops = flip_flops | 0b00000010;//set zero flag
	}else{
		flip_flops = flip_flops & 0b11111101;//unset zero flag
	}
	if(temp_A & 0b10000000){
		flip_flops = flip_flops | 0b00000100;//set sign flag
	}else{
		flip_flops = flip_flops & 0b11111011;//unset sign flag
	}
	if(!(temp_A & 0b00000001)){
		flip_flops = flip_flops | 0b00001000;//set parity flag
	}else{
		flip_flops = flip_flops & 0b11110111;//unset parity flag
	}
	return temp_A;
}

uint8_t AND(uint8_t arg1, uint8_t arg2){
	temp_A = arg1 & arg2;
	//logical ops cannot set carry bit I don't think
	if(!temp_A){
		flip_flops = flip_flops | 0b00000010;//set zero flag
	}else{
		flip_flops = flip_flops & 0b11111101;//unset zero flag
	}
	if(temp_A & 0b10000000){
		flip_flops = flip_flops | 0b00000100;//set sign flag
	}else{
		flip_flops = flip_flops & 0b11111011;//unset sign flag
	}
	if(!(temp_A & 0b00000001)){
		flip_flops = flip_flops | 0b00001000;//set parity flag
	}else{
		flip_flops = flip_flops & 0b11110111;//unset parity flag
	}
	return temp_A;
}

uint8_t EXCLUSIVE_OR(uint8_t arg1, uint8_t arg2){
	temp_A = arg1 ^ arg2;
	//logical ops cannot set carry bit I don't think
	if(!temp_A){
		flip_flops = flip_flops | 0b00000010;//set zero flag
	}else{
		flip_flops = flip_flops & 0b11111101;//unset zero flag
	}
	if(temp_A & 0b10000000){
		flip_flops = flip_flops | 0b00000100;//set sign flag
	}else{
		flip_flops = flip_flops & 0b11111011;//unset sign flag
	}
	if(!(temp_A & 0b00000001)){
		flip_flops = flip_flops | 0b00001000;//set parity flag
	}else{
		flip_flops = flip_flops & 0b11110111;//unset parity flag
	}
	return temp_A;
}

uint8_t OR(uint8_t arg1, uint8_t arg2){
	temp_A = arg1 | arg2;
	//logical ops cannot set carry bit I don't think
	if(!temp_A){
		flip_flops = flip_flops | 0b00000010;//set zero flag
	}else{
		flip_flops = flip_flops & 0b11111101;//unset zero flag
	}
	if(temp_A & 0b10000000){
		flip_flops = flip_flops | 0b00000100;//set sign flag
	}else{
		flip_flops = flip_flops & 0b11111011;//unset sign flag
	}
	if(!(temp_A & 0b00000001)){
		flip_flops = flip_flops | 0b00001000;//set parity flag
	}else{
		flip_flops = flip_flops & 0b11110111;//unset parity flag
	}
	return temp_A;
}

// Compare accumulator (arg1) with other value (arg2)
// If arg1 == arg2, zero flag is set (unset otherwise)
// If arg1 < arg2, carry flag is set (unset otherwise)
void COMPARE(uint8_t arg1, uint8_t arg2){ 
	if(arg1 < arg2){
		flip_flops = flip_flops | 0b00000001;//set carry flag
	}else{
		flip_flops = flip_flops & 0b11111110;//unset carry flag
	}
	
	temp_A = arg2 - arg1;
	
	if(!temp_A){
		flip_flops = flip_flops | 0b00000010;//set zero flag
	}else{
		flip_flops = flip_flops & 0b11111101;//unset zero flag
	}
	if(temp_A & 0b10000000){
		flip_flops = flip_flops | 0b00000100;//set sign flag
	}else{
		flip_flops = flip_flops & 0b11111011;//unset sign flag
	}
	if(!(temp_A & 0b00000001)){
		flip_flops = flip_flops | 0b00001000;//set parity flag
	}else{
		flip_flops = flip_flops & 0b11110111;//unset parity flag
	}
}

uint8_t INCREMENT(uint8_t arg1){
	temp_A = arg1 + 1;
	if(!temp_A){
		flip_flops = flip_flops | 0b00000010;//set zero flag
	}else{
		flip_flops = flip_flops & 0b11111101;//unset zero flag
	}
	if(temp_A & 0b10000000){
		flip_flops = flip_flops | 0b00000100;//set sign flag
	}else{
		flip_flops = flip_flops & 0b11111011;//unset sign flag
	}
	if(!(temp_A & 0b00000001)){
		flip_flops = flip_flops | 0b00001000;//set parity flag
	}else{
		flip_flops = flip_flops & 0b11110111;//unset parity flag
	}
	return temp_A;
}

uint8_t DECREMENT(uint8_t arg1){
	temp_A = arg1 - 1;
	if(!temp_A){
		flip_flops = flip_flops | 0b00000010;//set zero flag
	}else{
		flip_flops = flip_flops & 0b11111101;//unset zero flag
	}
	if(temp_A & 0b10000000){
		flip_flops = flip_flops | 0b00000100;//set sign flag
	}else{
		flip_flops = flip_flops & 0b11111011;//unset sign flag
	}
	if(!(temp_A & 0b00000001)){
		flip_flops = flip_flops | 0b00001000;//set parity flag
	}else{
		flip_flops = flip_flops & 0b11110111;//unset parity flag
	}
	return temp_A;
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
	temp_A = accumulator >> 7; //move A7 to A0 location
	accumulator = accumulator << 1;
	accumulator = accumulator | (flip_flops & 0b00000001); //put carry bit in accumulator
	flip_flops = flip_flops & 0b11111110;
	flip_flops = flip_flops | temp_A;//put A7 into carry bit

	return accumulator;
}

uint8_t RAR(uint8_t accumulator){
	temp_A = accumulator & 0b00000001; //mask A0
	accumulator = accumulator >> 1;
	accumulator = accumulator | ((flip_flops & 0b00000001) << 7); //put carry bit in A7
	flip_flops = flip_flops & 0b11111110;
	flip_flops = flip_flops | temp_A;//put A0 into carry bit
	
	return accumulator;
}