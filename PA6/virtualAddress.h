/**
 * @author Spencer Au
 * ID: 2385256
 * spau@chapman.edu
 * CPSC 380 - Section 1
 * PA6 - Virtual Memory
 * 
 * Header File that represents a virtual address
 **/


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
