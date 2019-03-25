CC=gcc
CFLAGS= -Wall -Werror -g

# Examples for a more complicated Makefile
DEPS = memory.h alu.h decode.h
OBJ = main.o memory.o ALU.o decode.c
SOURCES = main.c memory.c ALU.c decode.c

%.o: $(SOURCES) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o main readFile
