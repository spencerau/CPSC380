# Thread Synchronization

+ Uses 2 named Semaphores, empty and full, and a Mutex Lock in order to enable
sychronization for a solution to the producer/consumer problem

+ First arg is the sleep time, 2nd arg is amount of producer threads created, and
third arg is the amount of consumer threads created

## Identifying Information

+ Name: Spencer Au
+ Student ID: 2385256
+ Email: spau@chapman.edu
+ Course: CPSC 380
+ Assignment: PA5 - Thread Synchronization

## Source Files

+ buffer_item.h
+ prodcon.c
+ Makefile

## References

+

## Known Errors

+

## Build Insructions

### To Compile

+ make pc

### To Remove .o Files

+ make clean

## Execution Instructions

+ ```./pc | Sleep_Time | #_of_Producer_Threads | #_of_Consumer_Threads```
