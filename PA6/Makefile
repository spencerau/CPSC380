

CC=gcc
CFLAGS= -Wall

clean:
	rm -rf *.o
	rm -rf pc

pc: vmmgr.o
	$(CC) $(CFLAGS) -o pc vmmgr.o

vmmgr.o: vmmgr.c virtualAddress.h
	$(CC) $(CFLAGS) -c vmmgr.c

