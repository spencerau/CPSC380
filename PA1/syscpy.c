/*
ID: 002385256
spau@chapman.edu
CPSC 380 - Section 1
PA1

The objective of this assignment is to familiarize yourself how Linux system 
calls. We will be using system calls to manipulate a file using the standard 
I/O library to make file handling more efficient.

Write a C/C++ program that only uses only standard system calls to copy the contents 
of one file to another file. You should only have to use the open() (SYS_open), 
close()(SYS_close), read()(SYS_read) and write()(SYS_write) system calls. 
You can use printf() or fprintf() for error or informational messaging.  
Your program should not explicitly prompt the user for input/output filenames 
but rather those should be provided on the command line.

*/

#include <sys/types.h>
#include <sys/syscall.h>
#include <fcntl.h>  
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

    int readfd = syscall(SYS_open, argv[1], O_RDONLY);
    if (readfd == -1) {
        printf("File to be read from failed to open");
        return -1;
    }

    int writefd = syscall(SYS_open, argv[2], O_WRONLY | O_CREAT);
    if (writefd == -1) {
        printf("File to be written to failed to open");
        return -1;
    }

    char *buffer = (char *) calloc(100, sizeof(char));
    int bytesRead = 0;
    int bytesWrote = 0;

    bytesRead = syscall(SYS_read, readfd, buffer, sizeof(char));

    while (bytesRead != 0) {
        if (bytesRead == -1) {
            printf("File failed to read");
            return -1;
        }

        bytesWrote = syscall(SYS_write, writefd, buffer, sizeof(char));
        if (bytesWrote == -1) {
            printf("File failed to write");
            return -1;
        }
        bytesRead = syscall(SYS_read, readfd, buffer, sizeof(char));
    }

    free(buffer);
    if (syscall(SYS_close, readfd) == -1) {
        printf("File 'read' failed to close");
        return -1;
    }
    return 1;
}