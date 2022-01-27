cc = GCC
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o my_string.o

#hello : main.c
#	gcc -Wall --std=c99 main.c -o hello
string_driver : $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm string_driver $(OBJECTS)
my_string.o : my_string.h my_string.c
