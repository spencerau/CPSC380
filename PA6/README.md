# Virtual Address Manager

+ Virtual Memory Manager that reads from a file of logical addresses and outputs
+ the Logical Address in Decimal and Hex
+ the Page Number in Decimal and Hex
+ the Offset in Decimal and Hex
+ whether there was a TLB hit or miss, and a Page Fault or not
+ the corresponding Physical Address in Hex and the Byte value stored at that address

+ The program also outputs the Page Fault Rate and TLB Hit Rate at the end of the program

## Identifying Information

+ Name: Spencer Au
+ Student ID: 2385256
+ Email: spau@chapman.edu
+ Course: CPSC 380
+ Assignment: PA6 - Virtual Address Manager

## Source Files

+ virtualAddress.h
+ TLB.h
+ vmmgr.c
+ Makefile
+ addresses.txt
+ BACKING_STORE.bin
+ vm.sh

## References

+

## Known Errors

+

## Build Insructions

### To Compile

+ gcc *.c -o vmmgr
+ make vmmgr

### To Remove .o Files

+ make clean

## Execution Instructions

+ ./vmmgr addresses.txt

+ ./vm.sh
