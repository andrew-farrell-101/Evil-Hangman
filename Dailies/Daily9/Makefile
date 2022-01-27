cc = GCC
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o priority_queue.o 


driver : $(OBJECTS)
	$(CC) $(CFLAGS) -o driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm driver $(OBJECTS)
priority_queue.o : priority_queue.h priority_queue.c
