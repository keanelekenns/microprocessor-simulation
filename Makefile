CC=gcc
CFLAGS= -Wall -Werror -g

# Examples for a more complicated Makefile
DEPS = memory.h alu.h decode.h execute.h
OBJ = main.o memory.o ALU.o decode.o execute.o
SOURCES = main.c memory.c ALU.c decode.c execute.c

%.o: $(SOURCES) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Compile test cases for execute functions
execute_test: execute_test.o memory.o ALU.o decode.o execute.o

# Clean up binary and object files
clean:
	rm -f *.o main execute_test readFile
