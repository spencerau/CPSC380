#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

int main()
{
pid_t pid;
pid = fork();

if (pid == 0) {
    fork();
    //pthread_create();
}
fork();
}
