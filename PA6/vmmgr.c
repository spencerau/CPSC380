#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
//#include <unordered_map>
//#include <list>

#include "virtualAddress.h"
#include "TLB.h"

/*
Your program is to output the following values:
1. The logical address being translated (the integer value being read from addresses.txt).
2. The corresponding physical address (what your program translates the logical address to).
3. The signed byte value stored at the translated physical address.

After completion, your program is to report (output as well) the following statistics:
1. Page-fault rate—The percentage of address references that resulted in page faults.
2. TLB hit rate—The percentage of address references that were resolved in the TLB.
*/

int tblHit = 0;
int pageFault = 0;
int total = 0;

TLB *tlb;
int *pageTable;
char physicalMem[256][256];

int logicalAd = 0;
int frameIndex = 0;

/*
Other specifics include the following: 
• 2^8 entries in the page table
• Page size of 2^8 bytes
• 16 entries in the TLB
• Frame size of 2^8 bytes
• 256 frames
• Physical memory of 65,536 bytes (256 frames × 256-byte frame size)
2^8 = 256
*/

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./vmmgr txt_file\n");
        exit(1);
    }

    // array for page table with 2^8 entries of pages
    // pageNum is the index, and the value is the frame number
    pageTable = (int *) malloc(PAGE_TABLE_SIZE * sizeof(int));
    memset(pageTable, -1, PAGE_TABLE_SIZE * sizeof(int));

    // array for TLB with 16 entries
    tlb = newTLB();

    // array for physical memory of size 64k
    // index is the frame number
    // value is the byte
    /*
    for (int i = 0; i < 256; i++) {
        physicalMem[i] = (char*)malloc(256 * sizeof(char));
        memset(physicalMem[i], -1, 256 * sizeof(char));
    }
    */

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    
    //while (fread(&logicalAd, sizeof(int), 1, fp) == 1) {
    while (fscanf(fp, "%d", &logicalAd) == 1) {
        // create new virtual address struct
        virtualAddress *virtualAd = (virtualAddress *) malloc(sizeof(virtualAddress));

        // to get the first 2 bytes of the logical address, 
        // shift the logical address right by 8 bits
        virtualAd->pageNum = logicalAd >> 8;

        // to get the last 2 bytes of the logical address
        // use a bit mask of & 0xFF
        virtualAd->offset = logicalAd & 0xFF;

        // fill unused with 0's
        virtualAd->unused = 0;

        // print out logical address and its info
        printf("\nLog Addr in Decimal: %d  ", logicalAd);
        printf("Logic Address in Hex: %X\n", logicalAd);
        printf("Page Number: %X             ", virtualAd->pageNum);
        printf("Page Number in Decimal: %d\n", virtualAd->pageNum);
        printf("Offset: %X                  ", virtualAd->offset);
        printf("Offset in Decimal: %d\n", virtualAd->offset);

        // check TLB for page number
        // if page number is in TLB, get frame number from index pageNum and the byte at offset
        printf("before checkTLB\n");
        int frameNum = checkTLB(virtualAd->pageNum);
        if (frameNum != -1) {
            // TLB hit
            printf("TLB Hit\n");
        } else {
            // TLB miss
            printf("TLB Miss\n");
            // if page is not in TLB (TLB Miss), check page table for page number
            // if page is in page table, get frame number from index pageNum and the byte at offset
            printf("before checkPageTable\n");
            frameNum = checkPageTable(virtualAd->pageNum);
            if (frameNum != -1) {
                // page hit
                printf("Page Hit\n");
            } else {
                // page fault
                printf("Page Fault\n");
                // if page is not in page table (Page Fault), load page from BACKING_STORE.bin
                printf("before loadFromBS\n");
                frameNum = loadFromBS(virtualAd->pageNum, virtualAd->offset);
            }
        }
        // print the signed byte which is the value of the byte at the physical address
        printf("Signed Byte: %X\n", physicalMem[frameNum][virtualAd->offset]);
        free(virtualAd);
        total++;
    }
    // print out statistics
    printf("\n");
    printTLBHitRate();
    printPageFaultRate();
    printf("\n");

    fclose(fp);
    free_TLB(tlb);
    free(pageTable);
    /*
    for (int i = 0; i < 256; i++) {
        free(physicalMem[i]);
    }
    */
}

// if page number is in TLB, get frame number from index pageNum and the byte at offset
int checkTLB(int pageNum) {
    int frameNum = lookup_TLB(tlb, pageNum);
    //printf("after lookup_tlb\n");
    if (frameNum != -1) {
        // TLB hit
        tblHit++;
        return frameNum;
    }
    else {
        // TLB miss
        return -1;
    }
}

// if page is in page table, get frame number from index pageNum and the byte at offset
int checkPageTable(int pageNum) {
    int frameNum = pageTable[pageNum];
    if (frameNum != -1) {
        // page hit
        return frameNum;
    }
    // page fault
    pageFault++;
    return -1;
}

/*
for 16916, which is 4214, with page number 42 and offset 14, or 
in decimal page number 66 and offset 20, go to BACKING_STORE.bin and
read the 256 bytes starting at byte 66 * 256 = 16896, and then
read the next 20 bytes to get the value at 16916.
*/
int loadFromBS(int pageNum, int offset) {
    // access BACKING_STORE.bin as a binary file
    FILE *fp = fopen("BACKING_STORE.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    // perform fseek() in blocks of 256 bytes
    // each page is 256 bytes; 0 - 255
    int seek = fseek(fp, pageNum * 256, SEEK_SET);
    if (seek != 0) {
        printf("Error seeking file\n");
        exit(1);
    }
    // intialize buffer
    char buffer[256];

    // read 256 bytes from BACKING_STORE.bin
    fread(buffer, sizeof(char), 256, fp);

    int frameNum = frameIndex;
    // update TLB
    add_TLB(tlb, pageNum, frameNum);
    // update page table
    pageTable[pageNum] = frameNum;
    // update physical memory
    //physicalMem[frameNum] = buffer;
    memcpy(physicalMem[frameNum], buffer, 256);

    frameIndex++;

    fclose(fp);
    //free(buffer);
    //printf("frameNum assigned from loadFromBS: %d\n", frameNum);
    return frameNum;
}

void printPageFaultRate() {
    printf("Page Fault Rate: %f\n", (double)pageFault / (double)total);
}

void printTLBHitRate() {
    printf("TLB Hit Rate: %f\n", (double)tblHit / (double)total);
}

void printPageTable() {
    for (int i = 0; i < 256; i++) {
        printf("PageTable[%d]: %d\n", i, pageTable[i]);
    }
}
