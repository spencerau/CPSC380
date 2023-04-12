#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#include "buffer_item.h"

//using namespace std;

/*
The producer thread(s) will create the data item(s) which includes the checksum and random data (produced using the rand() function, 
which produces random integers between 0 and RAND MAX). 
The consumer thread(s) read the shared memory buffer of item(s), calculate the checksum and compare that with the value stored in the 
shared memory buffer to ensure that the data did not get corrupted.
The producer/consumer program (prodcon.c) that takes three arguments from the command line (no prompting the user from within the program).
*/

enum {
    false = 0,
    true = 1
} typedef bool;

void *producer(void *param); /* the producer thread */
void *consumer(void *param); /* the consumer thread */
int insert_item(buffer_item *item);
int remove_item(buffer_item *item);
uint16_t checksum(uint8_t *addr, uint32_t count);

// mutex protects against if the prod and cons is reading from same buffer
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
buffer_item buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

/*
./prodcon <delay> <#producer threads> <#consumer threads>
<delay> indicates how long to sleep (in seconds) before terminating
<#producer threads> indicates number of threads
<#consumer threads> indicates the number of consumer threads.
*/

/*
The Buffer
Internally, the buffer will consist of a fixed-size array of type buffer item (which will be defined using a typedef). 
The array of buffer item objects will be manipulated as a circular queue. The definition of buffer item, along with the 
size of the buffer, can be stored in a header file such as the following:
#define BUFFER_SIZE 30 typedef struct {
uint16_t cksum;
uint8_t buffer[BUFFER_SIZE]; } buffer_item;
struct buffer_item item[NUM_ITEMS];
The buffer will be manipulated with two functions, insert_item() and remove_item(), which are called by the producer 
and consumer threads, respectively. The insert_item() and remove_item() functions will synchronize the producer and 
consumer using the algorithms outlined in Fig 3. The buffer will also require an initialization function that initializes 
the mutual- exclusion object mutex along with the empty and full semaphores.
The main() function will initialize the buffer and create the separate producer and consumer threads. Once it has created 
the producer and consumer threads, the main() function will sleep for a period of time and, upon awakening, will terminate 
the application. The main() function will be passed three parameters on the command line:
1. How long to sleep before terminating (in seconds)
2. The number of producer threads
3. The number of consumer threads
*/
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Incorrect number of arguments\n");
        printf("Usage: ./pc <delay> <#producer threads> <#consumer threads>\n");
        return -1;
    }
    // Get command line args
    int delay = atoi(argv[1]);
    int num_prod_t = atoi(argv[2]);
    int num_cons_t = atoi(argv[3]);

    sem_unlink("empty");
    sem_unlink("full");
    // use sem_open because of Steve Jobs
    sem_open("empty", O_CREAT | O_EXCL | O_RDWR, 0644, NUM_ITEMS);
    sem_open("full", O_CREAT | O_EXCL | O_RDWR, 0644, 0);
    pthread_mutex_init(&mutex, NULL);

    // create producer threads
    for (int i = 0; i < num_prod_t; i++) {
        pthread_t prod_t;
        int prod_tid = -1;
        prod_tid = pthread_create(&prod_t, NULL, producer, NULL);
        if (prod_tid == -1) {
            perror("Error creating producer thread\n");
            exit(EXIT_FAILURE);
        }
        /*
        prod_tid = pthread_join(prod_t, NULL);
        if (prod_tid == -1) {
            perror("Error joining producer thread\n");
            exit(EXIT_FAILURE);
        }
        */
    }

    // create consumer threads
    for (int i = 0; i < num_cons_t; i++) {
        pthread_t cons_t;
        int cons_tid = -1;
        cons_tid = pthread_create(&cons_t, NULL, consumer, NULL);
        if (cons_tid == -1) {
            perror("Error creating consumer thread\n");
            exit(EXIT_FAILURE);
        }
        /*
        cons_tid = pthread_join(cons_t, NULL);
        if (cons_tid == -1) {
            perror("Error joining consumer thread\n");
            exit(EXIT_FAILURE);
        }
        */
    }

    // sleep
    sleep(delay);

    // destroy semaphores this way because of Steve Jobs
    sem_unlink("empty");
    sem_unlink("full");
    pthread_mutex_destroy(&mutex);

    return 0;
}

int insert_item(buffer_item *item) {
    memcpy(&buffer[in], item, sizeof(buffer_item));
    in = (in + 1) % NUM_ITEMS;
    return 0;
}

int remove_item(buffer_item *item) {
    memcpy(item, &buffer[out], sizeof(buffer_item));
    out = (out + 1) % NUM_ITEMS;
    return 0;
}

void *producer(void *param) {
    while (true) {        
        // checks if there are any open buffers
        buffer_item newItem;
        for (int i = 0; i < BUFFER_SIZE; i++) {
            newItem.buffer[i] = rand() % 256;
            newItem.cksum = checksum(newItem.buffer, BUFFER_SIZE);
        }

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        // insert item into buffer
        if (insert_item(&newItem) == -1) {
            printf("Error inserting item into buffer\n");
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    pthread_exit(0);

}

void *consumer(void *param) {
    while (true) {
        // is there at least one item to read

        buffer_item next_consumed;

        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // remove an item from buffer to next_consumed
        if (remove_item(&next_consumed) == -1) {
            printf("Error removing item from buffer\n");
        }
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        // checksum
        int cs = checksum(next_consumed.buffer, BUFFER_SIZE);
        if (next_consumed.cksum != cs) {
            printf("Checksums do not match when consuming\n");
            printf("Expected Checksum: %X\n", next_consumed.cksum);
            printf("Actual Checksum: %X\n", cs);
            //printf("Buffer Index: %d", out);
        }
    }
    pthread_exit(0);
}

/*
 * Checksum routine for Internet Protocol family headers (C Version)
 * checksum(addr, strlen(addr)))
 */

uint16_t checksum(uint8_t *addr, uint32_t count)
{
    // fix this

    uint32_t sum = 0;

    uint16_t *buf = (uint16_t *) addr;

    // Main summing loop
    while(count > 1)
    {
        sum = sum + *(buf)++;
        count = count - 2;
    }

    // Add left-over byte, if any
    if (count > 0)
        sum = sum + *addr;

    // Fold 32-bit sum to 16 bits
    while (sum>>16)
        sum = (sum & 0xFFFF) + (sum >> 16);
    return(~sum);
}
