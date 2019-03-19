CC=gcc
DEPS = 
#SOURCES = ./apps ./io
CFLAGS=-pedantic-errors -Wall -Werror -std=c11 -g

#./io/File.o: ./io/File.c
#	$(CC) -c -o $@ $< $(CFLAGS)

#%.o: $(SOURCES) $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

main: main.c
	$(CC) -o $@ $< $(CFLAGS)