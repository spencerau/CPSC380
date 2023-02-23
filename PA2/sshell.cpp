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
        fgets(command, MAX_LINE, stdin);
        // check if user wants to exit
        if (strcmp(command, "exit\n") == 0) {
            should_run = 0;
            continue;
            break;
        }
        // strip command of '\n'
        int len = strlen(command);
        command[len-1] = '\0';
        if (command[len-2] == '&') {
            ampersand = 1;
            command[len-2] = '\0';
        }
        // tokenize command
        char *token = strtok(command, " ");
        int i = 0;
        while (token != NULL) {
            // maybe use strcmp(str1, str2) to get rid of warnings
            args[i++] = strdup(token);
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = nullptr;
        delete command;
        delete token;

        // fork a child process
        pid = fork();
        // error checking if the fork failed
        if (pid < 0) {
            fprintf(stderr, "Fork Failed\n");
            return -1;
        }

        // child process
        else if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                fprintf(stderr, "execvp() failed\n");
                continue;
            }
            printf("The child process is executing\n");
            // the child process will execute in the background while it reprompts the user
            // this is not correct
            //if (ampersand) continue;

            // need to implement error checking for execvp
            // it returns -1 if an error has occured
        }

        // parent process
        else {
            //wait(NULL);
            cout << "Child Process created with pid " << pid << endl;
            int status;
            // wait on the child process to complete
            if (ampersand) waitpid(pid, &status, 0);
            cout << "Child Process is complete with status " << status << endl;
        }
        // implement '&' where the parent process calls wait() and waits for child process to finish
        // supposed to use fork() twice so that it creates another child process, making the original parent a grandparent?
        // the grandchild process will run execvp() "in the background"
        // need to call setsid() on the original child process in order to set it as the parent in a new process that will reprompt the user
        // grandparent needs to wait() on inital child
        // set original pid to a new pid, so grandPID = setsid()?
        // then we do 
        /*
        pid_t pid;
        pid_t grandPID;
        pid = fork();
        grandPID = setsid();
        pid = fork();
        */
        // check with Prof Springer if this is the correct way to go about part 3
        // or use setpgid() instead of calling fork twice?
        // also using daemon() is another solution?
        // other stuff about handling zombie processes with double forking - read up more about this

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
