#include <stdint.h>

/* buffer.h */
#define NUM_ITEMS 25
#define BUFFER_SIZE 30

struct buffer_itme {
uint16_t cksum;
// buffer of random bytes - random bytes are generated using the rand() function
uint8_t buffer[BUFFER_SIZE];
} typedef buffer_item;


