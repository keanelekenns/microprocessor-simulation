CC=gcc
CFLAGS=-pedantic-errors -Wall -Werror -std=c11 -g

# Examples for a more complicated Makefile
DEPS = state.h memory.h
OBJ = main.o state.o memory.o 
SOURCES = main.c state.c memory.c
#./io/File.o: ./io/File.c
#	$(CC) -c -o $@ $< $(CFLAGS)

#%.o: $(SOURCES) $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

# %.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

# main: $(OBJ)
# 	$(CC) -o $@ $^ $(CFLAGS)

main:
	gcc -o main main.c state.c memory.c $(CFLAGS)