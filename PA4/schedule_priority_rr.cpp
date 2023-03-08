#include "schedulers.h"
#include "CPU.h"
#include "task.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <queue>

// use a max heap or pqueue

using namespace std;

struct Compare {
    bool operator()(const Task *t1, const Task* t2) {
        return t1->priority < t2->priority;
    }
};

priority_queue<Task*, vector<Task*>, Compare> pq;
int tNum = 1;
int quantum = QUANTUM;

void add(char *name, int priority, int burst) {
    Task *task = new Task();
    task->name = name;
    task->priority = priority;
    task->burst = burst;
    task->tid = tNum;
    tNum++;
    pq.push(task);
}

void schedule() {
    printf("Using Priority RR Scheduler\n");
    while (!pq.empty()) {
        Task *task = pq.top();
        pq.pop();
        printf("Task: %d, Name: %s, Burst: %d, Priority: %d\n", task->tid, task->name, task->burst, task->priority);
        if (quantum >= task->burst) {
            run(task, task->burst);
            printf("Task %s has finished!\n", task->name);
            delete task;
        }
        else {
            run(task, quantum);
            task->burst -= quantum;
            // CHECK IF THE TASK IS SUPPOSED TO BE SORTED WHEN ITS KICKED OUT BY RR 
            printf("Task %s has been kicked out\n", task->name);
            pq.push(task);
        }
    }
}

