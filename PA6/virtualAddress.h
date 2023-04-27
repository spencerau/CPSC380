#include <stdint.h>

#define PAGE_TABLE_SIZE 256

typedef struct virtualAddress {
    uint32_t unused : 16;
    uint32_t pageNum : 8;
    uint32_t offset : 8;
} virtualAddress;

int checkTLB(int pageNum);
int checkPageTable(int pageNum);
int loadFromBS(int pageNum, int offset);
void printPageFaultRate();
void printTLBHitRate();
void printTLB();
void printPageTable();

// unions the two data types of ul and bf
typedef union {
    // unsigned long
    uint32_t ul;
    // bit field
    uint32_t bf;
} virtualAddr;
// can use memcpy() instead of union

// virtualAddress.bf.pageNum gives page number
// virtualAddress.bf.offset gives offset

// create an array for physical memory of size 64k

// initialize TLB to all -1 and page table to all -1 array of int

// if page is not in physical memory, load it from BACKING_STORE.bin, 
// update TLB and page table

/*
for 16916, which is 4214, with page number 42 and offset 14, or 
in decimal page number 66 and offset 20, go to BACKING_STORE.bin and
read the 256 bytes starting at byte 66 * 256 = 16896, and then
read the next 20 bytes to get the value at 16916.
*/


// access BACKING_STORE.bin as a binary file
// use fseek to move to the correct page
// perform fseek() in blocks of 256 bytes

// each page is 256 bytes; 0 - 255

