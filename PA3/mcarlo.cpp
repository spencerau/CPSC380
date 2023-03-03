/**
 * @author Spencer Au
 * ID: 2385256
 * spau@chapman.edu
 * CPSC 380 - Section 1
 * PA3
 * 
 * Estimates Pi using the Monte Carlo method
 * Uses a circle inscribed into a square
 * Generates a random number of points, and checks which
 * are inside the circle
 * Uses one thread to generate points and another to check which
 * are inside the circle
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <ctype.h>
#include <iostream>

using namespace std;

int npoints;
int hit_count = 0;
double pi = 0;
void *genPoints(void *arg);
void *findPi(void *arg);
double random_double();

//pthread_t tid; /* the thread identifier */
//pthread_attr_t attr; /* set of attributes for the thread */

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        fprintf(stderr, "Incorrect Number of Args");
        return -1;
    }

    string argv1 = argv[1];
    for (char c: argv1) {
        if (!isdigit(c)) {
            fprintf(stderr, "That value is not an int");
            return -1;
        }
    }

    npoints = atoi(argv[1]);
    //double arg[2] = {npoints, hit_count};
    pthread_t pointTh;
    int point_tid = pthread_create(&pointTh, NULL, genPoints, NULL);//(void*)&arg);
    if (point_tid != 0) {
        fprintf(stderr, "Failed to create Thread to create points");
        return -1;
    }
    // On success, pthread_join() returns 0; on error, it returns an error number.
    if (pthread_join(pointTh, NULL) != 0) {
        fprintf(stderr, "Thread Point failed to join");
        return -1;
    }

    // NOTE: ONLY NEED TO USE ONE THREAD - CREATE POINTS AND CHECK IF IN CIRCLE
    // PARENT THREAD CALCULATES PI

    pthread_t piTh;
    //double pi;
    int pi_tid = pthread_create(&piTh, NULL, findPi, NULL);//(void*)&pi);
    if (pi_tid != 0) {
        fprintf(stderr, "Failed to create Thread to find Pi");
        return -1;
    }
    if (pthread_join(piTh, NULL) != 0) {
        fprintf(stderr, "Thread Point failed to join");
        return -1;
    }
    printf("Pi is estimated to be: %.5f with %d points\n", pi, npoints);
    printf("Pi is supposed  to be: %.5f\n", M_PI);
}

void *genPoints(void *arg) {
    //cout << "Thread genPoints is executing" << endl;
    double x;
    double y;
    int num = 0;
    // change the seed to system time
    srandom(time(0));
    /* Check for points inside circle */
    for (int i = 0; i < npoints; i++) {	
    /* generate random numbers between -1.0 and +1.0 (exclusive) */
        x = random_double() * 2.0 - 1.0;
        y = random_double() * 2.0 - 1.0;
        if (sqrt(x*x + y*y) < 1.0 ) ++hit_count;	
    }
    //cout << "Thread genPoints is going to exit" << endl;
    pthread_exit(0);
}

void *findPi(void *arg) {
    //cout << "Thread findPi is executing" << endl;
    //double *pi = (double *) arg;
    pi = (double)4.0*hit_count/npoints;
    //cout << "Thread findPi is going to exit" << endl;
    pthread_exit(0);
}

/* Generates a double precision random number */
double random_double() 
{
    // rand() is not POSIX compliant
	return random() / ((double)RAND_MAX + 1);
}
