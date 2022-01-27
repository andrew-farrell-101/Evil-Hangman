cc = GCC
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o bit_flags.o

string_driver : $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm string_driver $(OBJECTS)
bit_flags.o: bit_flags.c

