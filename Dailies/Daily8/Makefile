cc = GCC
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o stack.o 


daily_runner : $(OBJECTS)
	$(CC) $(CFLAGS) -o daily_runner $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm daily_runner $(OBJECTS)
stack.o : stack.h stack.c
