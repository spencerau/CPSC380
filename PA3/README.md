# mcarlo

+ Estimates Pi using the Monte Carlo method
+ Uses a circle inscribed into a square
+ Generates a random number of points, and checks which
are inside the circle
+ Uses one thread to generate points and another to check which
are inside the circle

## Identifying Information

* Name: Spencer Au
* Student ID: 2385256
* Email: spau@chapman.edu
* Course: CPSC 380
* Assignment: PA3 - Monte Carlo

## Source Files

* mcarlo.cpp

## References

* https://man7.org/linux/man-pages/man7/pthreads.7.html
* https://man7.org/linux/man-pages/man3/pthread_create.3.html
* https://man7.org/linux/man-pages/man3/pthread_join.3.html
* https://www.geeksforgeeks.org/thread-functions-in-c-c/
* https://en.wikipedia.org/wiki/C_POSIX_library

## Known Errors

*

## Build Insructions

* g++ *.cpp -o mcarlo

## Execution Instructions

* ./mcarlo "number of points"
