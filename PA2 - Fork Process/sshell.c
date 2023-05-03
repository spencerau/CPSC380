/**
 * @author Spencer Au
 * ID: 2385256
 * spau@chapman.edu
 * CPSC 380 - Section 1
 * PA2
 * 
 * This program simluates a shell, with the promp "osh>"
 * It will keep reprompting the user until "exit" is entered
 * It uses execvp() to pull the command entered along with any flags
 * It creates a new process with fork() and has the child process call execvp()
 * If the user enters an "&" character at the end then the parent process will call
 * waitpid() and wait until the child process finishes
 **/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* The maximum length command*/
#define MAX_LINE 80

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
        char *command = (char*)malloc(MAX_LINE);
        fgets(command, MAX_LINE, stdin);
        // check if user wants to exit
        if (strcmp(command, "exit\n") == 0) {
            should_run = 0;
            continue;
            break;
        }
        // strip command of newline and check for & flag
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
            args[i] = strdup(token);
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;
        free(command);
        free(token);

        // fork a child process
        pid = fork();
        // error checking if the fork failed
        if (pid < 0) {
            fprintf(stderr, "Fork Failed\n");
            return -1;
        }
        // child process
        else if (pid == 0) {
            // it returns -1 if an error has occured
            if (execvp(args[0], args) == -1) {
                fprintf(stderr, "execvp() failed\n");
                continue;
            }
            //printf("The child process is executing\n");
        }
        // parent process
        else {
            //cout << "Child Process created with pid " << pid << endl;
            int status = -99;
            // wait on the child process to complete
            if (ampersand) waitpid(pid, &status, 0);
            //cout << "Child Process is complete with status " << status << endl;
        }
    }
    return 0;

}
