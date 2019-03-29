#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"memory.h"


void print_program_counter(){
	printf("Program Counter: 0x%04x\n\n", mem.address_stack[mem.program_counter]);
	// The number subtracted and added to the program counter simply changes how many lines of program memory we show
	for(int i = mem.address_stack[mem.program_counter] - 3; i <= mem.address_stack[mem.program_counter] + 3; i++){
		if(i < 0){
			continue; //prevents displaying addresses below 0x00
		}
		if(i == mem.address_stack[mem.program_counter]){
			printf("0x%04x    ", i);
			for(int j = 7; j >= 0; j--){
				printf("%u", (mem.memory[i] >> j) & 0x01);//isolates desired bit (alternative to masking)
			}
			printf(" <---\n");
		}else{
			printf("0x%04x    ", i);
			for(int j = 7; j >= 0; j--){
				printf("%u", (mem.memory[i] >> j) & 0x01);
			}
			printf("\n");
		}
	}
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
/*
This function is used to print out the contents of memory in a concise manner
that lends itself to the demonstration of the software. 
*/
void print_all_contents(){
	printf("========================================\n");
	print_program_counter();
	printf("========================================\n");
	print_scratch_pad();
	printf("========================================\n");
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
	int num_bytes = readFile(argv[1]);
	for(int i = 0; i < num_bytes; i++){
		printf("%x\n", mem.memory[i]);
	}
	printf("\nBefore:\n");
	print_all_contents();
	mem.address_stack[mem.program_counter] += 5;
	printf("\nAfter:\n");
	print_all_contents();
	
    return 0;
}