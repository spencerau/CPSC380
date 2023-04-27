#ifndef TLB_H
#define TLB_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define TLB_SIZE 256

// represents a TLB entry as a linked list node
typedef struct TLB_Entry {
    int pageNum;
    int frameNum;
    struct TLB_Entry *next;
    struct TLB_Entry *prev;
} TLB_Entry;

// represents a double linked list and uses an array of 16 entires
// for O(1) lookup
typedef struct TLB {
    TLB_Entry *head;
    TLB_Entry *tail;
    int size;
    int *TLB_Array;
} TLB;

TLB *newTLB();
void add_entry(TLB *tlb, int pageNum, int frameNum);
int lookup_tlb(TLB *tlb, int pageNum);
void printTLB_Array(int *arr);
void printTLB_LL(TLB *tlb);
void freeTLB(TLB *tlb);

// creates a new TLB
TLB *newTLB() {
    //TLB *tlb = new TLB;
    TLB *tlb = (TLB*) malloc(sizeof(TLB));
    tlb->head = NULL;
    tlb->tail = NULL;
    tlb->size = 0;
    tlb->TLB_Array = (int*) malloc(sizeof(int) * TLB_SIZE);
    for (int i = 0; i < TLB_SIZE; i++) {
        tlb->TLB_Array[i] = -1;
    }
    return tlb;
}

// adds a new TLB entry to the TLB
void add_entry(TLB *tlb, int pageNum, int frameNum) {
    if (tlb->size == 16) {
        // TLB is full, remove the least recently used entry
        TLB_Entry *remove = tlb->tail;
        tlb->tail = remove->prev;
        if (tlb->tail != NULL) {
            tlb->tail->next = NULL;
        }
        tlb->TLB_Array[remove->pageNum] = -1;
        free(remove);
        tlb->size--;
    }

    // add the new entry to the front of the list
    TLB_Entry *new_entry = (TLB_Entry*) malloc(sizeof(TLB_Entry));
    new_entry->pageNum = pageNum;
    new_entry->frameNum = frameNum;
    new_entry->next = tlb->head;
    new_entry->prev = NULL;
    if (tlb->head != NULL) {
        tlb->head->prev = new_entry;
    }
    tlb->head = new_entry;
    if (tlb->tail == NULL) {
        tlb->tail = new_entry;
    }
    tlb->TLB_Array[pageNum] = frameNum;
    tlb->size++;
}

int lookup_tlb(TLB *tlb, int pageNum) {
    if (tlb->TLB_Array[pageNum] != -1) {
        // TLB hit
        return tlb->TLB_Array[pageNum];
    }
    // TLB miss
    return -1;
}

void printTLB_Array(int *arr) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (arr[i] != -1) {
            printf("TLB_Array[%d]: %d\n", i, arr[i]);
        }
    }
}

void printTLB_LL(TLB *tlb) {
    TLB_Entry *curr = tlb->head;
    while (curr != NULL) {
        printf("TLB[%d]: %d\n", curr->pageNum, curr->frameNum);
        curr = curr->next;
    }
}

void freeTLB(TLB *tlb) {
    TLB_Entry *curr = tlb->head;
    TLB_Entry *next;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(tlb->TLB_Array);
    free(tlb);
}

#endif
