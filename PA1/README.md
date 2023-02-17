# syscpy

syscpy imitates the "cp" command using the OPEN, CLOSE, READ, and WRITE system calls via syscall().


## Identifying Information

* Spencer Au
* ID: 002385256
* spau@chapman.edu
* CPSC 380 - Section 1
* PA1


## Source Files
* syscpy.c


## References
* https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
* https://man7.org/linux/man-pages/man2/open.2.html
* https://man7.org/linux/man-pages/man2/read.2.html
* https://man7.org/linux/man-pages/man2/write.2.html
* https://man7.org/linux/man-pages/man2/close.2.html


## Known Errors
*


## Build Instructions:
* To Compile: gcc syscpy.c -o syscpy


## Execution Instructions:
* To Run: ./syscpy "inputFile" outputFile"
* To Test: diff "inputFile" outputFile"
