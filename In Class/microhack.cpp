#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <ctype.h>
#include <iostream>

using namespace std;

int arr[10000];
int c = 0;

void *average(void *arg);
void *min(void *arg);
void *max(void *arg);


int main(int argc, char *argv[]) {

    for (int i = 0; i < argc-1; i++) {
        arr[i] = atoi(argv[i+1]);
        c++;
        //printf("ARGV[i+1]: %d\n", argv[i+1]);
        //printf("arr[%d]: %d\n", i, arr[i]);
        //printf("Count: %d\n", c);
    }

    pthread_t t1;
    int tid1 = pthread_create(&t1, NULL, average, NULL);
    pthread_join(t1, NULL);

    pthread_t t2;
    int tid2 = pthread_create(&t2, NULL, min, NULL);
    pthread_join(t2, NULL);

    pthread_t t3;
    int tid3 = pthread_create(&t3, NULL, max, NULL);
    pthread_join(t3, NULL);


    //arr = new int[1000];

    for (int i = 0; i < argc-1; i++) {
        arr[i] = atoi(argv[i+1]);
        c++;
        //printf("ARGV[i+1]: %d\n", argv[i+1]);
        //printf("arr[%d]: %d\n", i, arr[i]);
        //printf("Count: %d\n", c);
    }

}

void *average(void *arg) {
    double ave = 0;
    for (int i = 0; i < c; i++) {
        ave += arr[i];
        //cout << "ave" << endl;
    }
    ave /= c;
    printf("The average value is %f\n", ave);
    pthread_exit(0);
}

void *min(void *arg) {
    int low = 99999;
    //cout << "test" << endl;
    for (int i = 0; i < c; i++) {
        if (arr[i] < low) {
            low = arr[i];
            //cout << low << endl;
        }
    }

    printf("The minimum value is %d\n", low);
    pthread_exit(0);
}

void *max(void *arg) {
    int high = -99999;
    for (int i = 0; i < c; i++) {
        if (arr[i] > high) high = arr[i];
    }

    printf("The maximum value is %d\n", high);
    pthread_exit(0);
}