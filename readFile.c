#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"memory.h"
/*Function for reading in program file into Memory array
  Returns 0 on success, returns -1 on failure
  Format of file must have each byte followed by a newline character
  e.g.
  10101010
  11110001
  11010110
  ...
  11110000
  01010101
*/
int readFile(char* filename){
	
	FILE* fp = fopen(filename, "rb");
	if(fp == NULL){
		printf("File \"%s\" could not be read\n", filename);
		return -1;
	}
	fseek(fp, 0L, SEEK_END);
	size_t file_size = ftell(fp);
	rewind(fp);
	for(int i = 0; i < file_size; i++){
		mem.memory[i] = (uint8_t)fgetc(fp);
		fgetc(fp); //ignore the newline character after the byte
	}
	fclose(fp);
	return 0;
}

int main(int argc, char** argv){
	if(argc < 2){
		printf("ERROR:\nA program filename must be included as an argument\n");
	}
    printf("%d %s\n", argc, argv[1]);
	readFile(argv[1]);
	for(int i = 0; i < sizeof(mem.memory); i++){
		printf("%x\n", mem.memory[i]);
	}
    return 0;
}