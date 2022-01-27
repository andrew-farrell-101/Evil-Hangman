cc = GCC
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o
hello : main.o
	$(CC) $(CFLAGS) -o hello main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean: 
	rm hello $(OBJECTS)

