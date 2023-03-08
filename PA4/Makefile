# makefile for scheduling program
#
# make rr - for round-robin scheduling
# make fcfs - for FCFS scheduling
# make sjf - for SJF scheduling
# make priority - for priority scheduling
# make priority_rr - for priority with round robin scheduling

CC=g++
CFLAGS=-Wall

clean:
	rm -rf *.o
	rm -rf fcfs
	rm -rf sjf
	rm -rf rr
	rm -rf priority
	rm -rf priority_rr

rr: driver.o list.o CPU.o schedule_rr.o
	$(CC) $(CFLAGS) -o rr driver.o schedule_rr.o list.o CPU.o

sjf: driver.o list.o CPU.o schedule_sjf.o
	$(CC) $(CFLAGS) -o sjf driver.o schedule_sjf.o list.o CPU.o

fcfs: driver.o list.o CPU.o schedule_fcfs.o
	$(CC) $(CFLAGS) -o fcfs driver.o schedule_fcfs.o list.o CPU.o

priority: driver.o list.o CPU.o schedule_priority.o
	$(CC) $(CFLAGS) -o priority driver.o schedule_priority.o list.o CPU.o

schedule_fcfs.o: schedule_fcfs.cpp
	$(CC) $(CFLAGS) -c schedule_fcfs.cpp

priority_rr: driver.o list.o CPU.o schedule_priority_rr.o
	$(CC) $(CFLAGS) -o priority_rr driver.o schedule_priority_rr.o list.o CPU.o

driver.o: driver.cpp
	$(CC) $(CFLAGS) -c driver.cpp

schedule_sjf.o: schedule_sjf.cpp
	$(CC) $(CFLAGS) -c schedule_sjf.cpp

schedule_priority.o: schedule_priority.cpp
	$(CC) $(CFLAGS) -c schedule_priority.cpp

schedule_rr.o: schedule_rr.cpp
	$(CC) $(CFLAGS) -c schedule_rr.cpp

list.o: list.cpp list.h
	$(CC) $(CFLAGS) -c list.cpp

CPU.o: CPU.cpp cpu.h
	$(CC) $(CFLAGS) -c CPU.cpp
