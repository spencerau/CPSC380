/*
ID: 002385256
spau@chapman.edu
CPSC 380 - Section 1
PA2

*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

#define MAX_LINE 80 /* The maximum length command*/

int main(void) {
    // command line arguments
    char *args[MAX_LINE/2 +1]; 
    // flag to determine when to exit program
    int should_run = 1;
    string command;
    pid_t pid;

    while (should_run) {
        printf("osh>");
        fflush(stdout);
        /**
         * After reading user input, the steps are:
         * (1) Fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) if command included &, parent will invoke wait()
        */
        cin >> command; 
        //command = "ls -l -v";
        if (command == "exit") {
            should_run = 0;
            break;
        }
        char *temp = strdup(command.c_str());
        //strcpy(temp, command.c_str());
        char *token = strtok(temp, " ");
        int i = 0;
        while (token != NULL) {
            args[i] = strdup(token);
            token = strtok(NULL, " ");
            i++;
        }
        delete temp;
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
            execvp(args[0], args);
            // need to implement error checking for execvp
        }
        // parent process
        else {
            wait(NULL);
            printf("Child Process is complete\n");
        }
        // implement & where the parent process calls wait() and waits for child process to finish

    }

    //delete args;
    return 0;

}
