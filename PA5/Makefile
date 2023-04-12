

CC=gcc
CFLAGS=-Wall

clean:
	rm -rf *.o
	rm -rf pc

pc: prodcon.o
	$(CC) $(CFLAGS) -o pc prodcon.o

prodcon.o: prodcon.c buffer_item.h
	$(CC) $(CFLAGS) -c prodcon.c

