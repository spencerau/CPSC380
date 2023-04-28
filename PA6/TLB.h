/**
 * @author Spencer Au
 * ID: 2385256
 * spau@chapman.edu
 * CPSC 380 - Section 1
 * PA6 - Virtual Memory
 * 
 * Represents a TLB of size 16, with each entry containing a page number, frame number, and timestamp
 **/

#ifndef TLB_H
#define TLB_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define TLB_SIZE 16

typedef struct TLB_Entry {
    int pageNum;
    int frameNum;
    time_t timestamp;
} TLB_Entry;

typedef struct TLB {
    TLB_Entry **tlb_array;
    int size;
} TLB;

TLB *newTLB();
void add_TLB(TLB *tlb, int pageNum, int frameNum);
int lookup_TLB(TLB *tlb, int pageNum);
void print_TLB(TLB *tlb);
void free_TLB(TLB *tlb);

TLB *newTLB() {
    int size = TLB_SIZE;
    TLB *tlb = (TLB*) malloc(sizeof(TLB));
    tlb->tlb_array = (TLB_Entry**) malloc(size * sizeof(TLB_Entry*));
    for (int i = 0; i < TLB_SIZE; i++) {
        tlb->tlb_array[i] = (TLB_Entry*) malloc(sizeof(TLB_Entry));
        tlb->tlb_array[i]->pageNum = -1;
        tlb->tlb_array[i]->frameNum = -1;
        tlb->tlb_array[i]->timestamp = -1;
    }
    tlb->size = 0;
    return tlb;
}

void add_TLB(TLB *tlb, int pageNum, int frameNum) {
    if (tlb->size == TLB_SIZE) {
        // TLB is full, remove the least recently used entry
        int min = 0;
        for (int i = 0; i < TLB_SIZE; i++) {
            if (tlb->tlb_array[i]->timestamp < tlb->tlb_array[min]->timestamp) {
                min = i;
            }
        }
        tlb->tlb_array[min]->pageNum = pageNum;
        tlb->tlb_array[min]->frameNum = frameNum;
        tlb->tlb_array[min]->timestamp = time(NULL);
    } else {
        // TLB is not full, add the entry to the end of the TLB
        tlb->tlb_array[tlb->size]->pageNum = pageNum;
        tlb->tlb_array[tlb->size]->frameNum = frameNum;
        tlb->tlb_array[tlb->size]->timestamp = time(NULL);
        tlb->size++;
    }
}

int lookup_TLB(TLB *tlb, int pageNum) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb->tlb_array[i]->pageNum == pageNum) {
            // found the entry, update the timestamp and return the frameNum
            tlb->tlb_array[i]->timestamp = time(NULL);
            return tlb->tlb_array[i]->frameNum;
        }
    }
    // TLB miss
    return -1;
}

void print_TLB(TLB *tlb) {
    printf("TLB:\n");
    for (int i = 0; i < tlb->size; i++) {
        printf("TLB[%d]: Page %d: frame %d\n", i, tlb->tlb_array[i]->pageNum, tlb->tlb_array[i]->frameNum);
    }
}

void free_TLB(TLB *tlb) {
    for (int i = 0; i < TLB_SIZE; i++) {
        free(tlb->tlb_array[i]);
    }
    free(tlb->tlb_array);
    free(tlb);
}



#endif
