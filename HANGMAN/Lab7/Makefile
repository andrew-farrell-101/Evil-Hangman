cc = GCC
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o my_string.o generic_vector.o associative_array.o

string_driver : $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o
my_string.o : my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
generic_vector.o : generic_vector.h generic_vector.c generic.h
	$(CC) $(CFLAGS) -c generic_vector.c -o generic_vector.o
associative_array.o : associative_array.h associative_array.c
	$(CC) $(CFLAGS) -c associative_array.c -o associative_array.o
clean:
	rm string_driver $(OBJECTS)
