/*
ID: 002385256
spau@chapman.edu
CPSC 380 - Section 1
PA1

*/

#include <sys/types.h>
//#include <sys/stat.h>
#include <sys/syscall.h>
#include <fcntl.h>  
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int readfd = syscall(SYS_open, argv[1], O_RDONLY);
    //int readfd = open(argv[1], O_RDONLY);
    if (readfd == -1) {
        printf("File to be read from failed to open");
        return -1;
    }
    int writefd = syscall(SYS_open, argv[2], O_WRONLY | O_CREAT);
    if (writefd == -1) {
        printf("File to be written to failed to open");
        return -1;
    }

    char *c = (char *) calloc(100, sizeof(char));

    while (syscall(SYS_read, readfd, c, sizeof(char)) != 0) {
        // implement error handling for read
        syscall(SYS_write, writefd, c, sizeof(char));
        // implement error handling for write

    }

    free(c);
    //close(readfd);
    if (syscall(SYS_close, readfd) == -1) {
        printf("File 'read' failed to close");
    }
}