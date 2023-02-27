# sshell

+ Program Description
+ This program simluates a shell, with the promp "osh>"
+ It will keep reprompting the user until "exit" is entered
+ It uses execvp() to pull the command entered along with any flags
+ It creates a new process with fork() and has the child process call execvp()
+ If the user enters an "&" character at the end then the parent process will call
waitpid() and wait until the child process finishes

## Identifying Information

* Name: Spencer Au
* Student ID: 2385256
* Email: spau@chapman.edu
* Course: CPSC 380
* Assignment: PA2 - Fork Process

## Source Files

* sshell.cpp

## References

* https://man7.org/linux/man-pages/man2/fork.2.html
* https://man7.org/linux/man-pages/man3/exec.3p.html
* https://www.unix.com/man-page/posix/3/execvp/
* https://stackoverflow.com/questions/289347/using-strtok-with-a-stdstring
* https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
* https://linuxcommand.org/lc3_man_pages/ls1.html
* https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-waitpid-wait-specific-child-process-end
* https://man7.org/linux/man-pages/man2/wait.2.html

## Known Errors

*

## Build Insructions

* g++ *.cpp -o shell

## Execution Instructions

* ./shell
* osh> "command" "-flag1" "-flag2" (&)
