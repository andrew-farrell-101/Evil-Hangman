cc = GCC
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o my_string.o

string_driver : $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm string_driver $(OBJECTS)
unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o
my_string.o : my_string.h my_string.c
