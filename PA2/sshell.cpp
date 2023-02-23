/**
 * @author Spencer Au
 * ID: 2385256
 * spau@chapman.edu
 * CPSC 380 - Section 1
 * PA2
 * 
 * 
 * */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 /* The maximum length command*/

int main(void) {
    // command line arguments
    char *args[MAX_LINE/2 +1]; 
    // flag to determine when to exit program
    int should_run = 1;
    pid_t pid;
    int ampersand= 0;

    /**
        * After reading user input, the steps are:
        * (1) Fork a child process using fork()
        * (2) the child process will invoke execvp()
        * (3) if command included &, parent will invoke wait()
    */

    while (should_run) {
        printf("osh> ");
        fflush(stdout);
        ampersand = 0;
        
        char *command = new char();
        fgets(command, MAX_LINE/2+1, stdin);
        // need to strip command of '\n'
        int len = strlen(command);
        command[len-1] = '\0';
        // check if user wants to exit
        if (command == "exit") {
            should_run = 0;
            break;
        }
        // tokenize command
        char *token = strtok(command, " ");
        int i = 0;
        while (token != NULL) {
            if (token == "&") ampersand = 1;
            args[i] = strdup(token);
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = nullptr;
        delete command;
        delete token;
        // fork a child process
        pid = fork();
        // error checking if the fork failed
        if (pid < 0) {
            fprintf(stderr, "Fork Failed");
            return -1;
        }
        // child process
        else if (pid == 0) {
            cout << "args[0]: " << args[0] << endl;
            execvp(args[0], args);
            printf("The child process is executing\n");
            //exit(1);
            // need to implement error checking for execvp
            // it returns -1 if an error has occured
        }
        // parent process
        else {
            //wait(NULL);
            cout << "Child Process created with pid " << pid << endl;
            int status;
            waitpid(pid, &status, 0);
            cout << "Child Process is complete with status " << status << endl;
        }
        // implement & where the parent process calls wait() and waits for child process to finish

        /*
        In fact, under normal termination, exit() will be called either directly (as shown above) or indirectly, as the C run-time library 
        (which is added to UNIX executable files) will include a call to exit() by default.

        A parent process may wait for the termination of a child process by using the wait() system call. The wait() system call is passed 
        a parameter that allows the parent to obtain the exit status of the child. This system call also returns the process identifier of 
        the terminated child so that the parent can tell which of its children has terminated:

        pid_t pid;
        int status;
 
        pid = wait(&status);
        */
    }
    //delete args;
    return 0;

}
