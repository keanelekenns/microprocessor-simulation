#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include "memory.h"
#include "ALU.h"


void print_memory_chunk(int beginning, int end){
	if(beginning < 0x00){//check for out of range
		beginning = 0x00;
	}
	if(end > 0x3FFF){
		end = 0x3FFF;
	}
	for(int i = beginning; i <= end; i++){
		printf("0x%04x    ", i);
		for(int j = 7; j >= 0; j--){
			printf("%u", (mem.memory[i] >> j) & 0x01);
		}
		printf("\n");
	}
}

void print_program_counter(){
	printf("Program Counter: 0x%04x\n\n", mem.address_stack[mem.program_counter]);
	
	print_memory_chunk(mem.address_stack[mem.program_counter] - 3, mem.address_stack[mem.program_counter] - 1);
	
	printf("0x%04x    ", mem.address_stack[mem.program_counter]);
	for(int j = 7; j >= 0; j--){
		printf("%u", (mem.memory[mem.address_stack[mem.program_counter]] >> j) & 0x01);//isolates desired bit
	}
	printf(" <---\n");
	
	print_memory_chunk(mem.address_stack[mem.program_counter] + 1, mem.address_stack[mem.program_counter] + 3);
}

void print_scratch_pad(){
	printf("Scratch Pad:\n\nRegister    Value\n");
	char c = 'A';
	for(int i = 0; i < 7 ; i++){
		printf("%8c    ", c);
		for(int j = 7; j >= 0; j--){
				printf("%u", (mem.scratch_pad[i] >> j) & 0x01);
			}
		printf("\n");
		c++;
		if(i == 4){
			c = 'H';
		}else if(i == 5){
			c = 'L';
		}
	}
}

void print_control_bits(){
	printf("Control Bits:\n\n");
	printf("Flip-Flop    Value\n");
	printf("    Carry    %u\n", get_flip_flops() & 0x01);
	printf("     Zero    %u\n", (get_flip_flops()>>1) & 0x01);
	printf("     Sign    %u\n", (get_flip_flops()>>2) & 0x01);
	printf("   Parity    %u\n", (get_flip_flops()>>3) & 0x01);
}

void print_instruction_reg(){
	printf("Instruction Register: ");
	for(int j = 7; j >= 0; j--){
		printf("%u", (mem.instruction_reg >> j) & 0x01);
	}
	printf("\n");
}

void print_memory(){
	printf("Data Memory:\n\n");
	int end;
	int zero_counter = 0;
	for(int i = 0x0100; i < 0x4000; i++){//Data memory begins at 0x0100 = 256 and ends at 0x3FFF = 16383
		if(mem.memory[i] == 0x00){
			continue;
		}
		end = i;
		while(zero_counter < 4 && end < 0x4000){
			end++;
			if(mem.memory[end] == 0x00){
				zero_counter++;
			}else{
				zero_counter = 0;
				//reset counter, since we are looking for 
				//4 consecutive zeros to indicate the end 
				//of a relevant chunk of memory
			}
		}
		print_memory_chunk(i, end - 4);//print memory from first non zero byte to last non zero byte
		printf("...\n");
		zero_counter = 0;
		i = end; //skip forward to where we left off
	}
}

void print_misc_values(){
	printf("Miscellaneous Values:\n\n");
	printf(" Variable    Value\n");
	printf("    reg a    ");
	for(int j = 7; j >= 0; j--){
		printf("%u", (mem.reg_a >> j) & 0x01);
	}
	printf("\n");
	printf("    reg b    ");
	for(int j = 7; j >= 0; j--){
		printf("%u", (mem.reg_b >> j) & 0x01);
	}
	printf("\n");
	printf(" mem high    ");
	for(int j = 7; j >= 0; j--){
		printf("%u", (mem.mem_high >> j) & 0x01);
	}
	printf("\n");
	printf("  mem low    ");
	for(int j = 7; j >= 0; j--){
		printf("%u", (mem.mem_low >> j) & 0x01);
	}
	printf("\n");
}
/*
This function is used to print out the contents of memory in a concise manner
that lends itself to the demonstration of the software. 
*/
void print_all_contents(){
	printf("\n========================================\n\n");
	print_program_counter();
	printf("\n========================================\n\n");
	print_instruction_reg();
	printf("\n========================================\n\n");
	print_scratch_pad();
	printf("\n========================================\n\n");
	print_control_bits();
	printf("\n========================================\n\n");
	print_memory();
	printf("\n========================================\n\n");
	print_misc_values();
	printf("\n========================================\n\n");
}

int readFile(char* filename){
	
	FILE* fp = fopen(filename, "rb");
	if(fp == NULL){
		printf("File \"%s\" could not be read\n", filename);
		return -1;
	}
	uint8_t byte = 0x00;
	int i, j, c;
	for(i = 0; i <= 0xFF; i++){//program area of memory is from 0x00 up to 0xFF (inclusive)
		for(j = 7; j >= 0; j--){
			c = fgetc(fp);
			while(!((c == 0x30)||( c == 0x31))){
				if(c == EOF){
					j = 0;
					break;//we're done reading, so exit all loops
				}
				c = fgetc(fp);
			}
			if(c == 0x31){
				byte = byte | (1 << j);
			}
		}
		if(c == EOF){
			break;
		}
		mem.memory[i] = byte;
		byte = 0x00;
	}
	fclose(fp);
	return i;
}

int main(int argc, char** argv){
	if(argc < 2){
		printf("ERROR:\nA program filename must be included as an argument\n");
	}
	readFile(argv[1]);
	printf("\nBefore:\n");
	print_all_contents();
	mem.address_stack[mem.program_counter] += 5;
	mem.scratch_pad[3] = 34;
	ADD(250, 2);
	for(int i = 0; i < 35; i++){
		for(int j = 1; j < i*2%20; j++){
			mem.memory[(j + i*35 + 300)] = (j*100)%256;
		}
	}
	printf("\nAfter:\n");
	print_all_contents();
	
    return 0;
}