
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int npoints;
int hit_count = 0;

int main(int argc, char *argv) {
    if (argc != 2) printf("Incorrect Number of Args");
    npoints = stoi(argv[1]);
}

/* Generates a double precision random number */
double random_double() 
{
	return random() / ((double)RAND_MAX + 1);
}

/* Check for points inside circle */
for (i = 0; i < npoints; i++) {	
/* generate random numbers between -1.0 and +1.0 (exclusive) */
    x = random_double() * 2.0 - 1.0;
	y = random_double() * 2.0 - 1.0;
		
	if (sqrt(x*x + y*y) < 1.0 )++hit_count;	
}	
