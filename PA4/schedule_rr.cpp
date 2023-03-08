#include "schedulers.h"
#include "CPU.h"
#include "task.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <queue>

// use a max heap or pqueue

using namespace std;

queue<Task*> q; 
int tNum = 1;
int quantum = QUANTUM;

void add(char *name, int priority, int burst) {
    Task *task = new Task();
    task->name = name;
    task->priority = priority;
    task->burst = burst;
    task->tid = tNum;
    tNum++;
    q.push(task);
}

void schedule() {
    printf("Using RR Scheduler\n");
    while (!q.empty()) {
        Task *task = q.front();
        q.pop();
        printf("Task: %d, Name: %s, Burst: %d\n", task->tid, task->name, task->burst);
        if (quantum >= task->burst) {
            run(task, task->burst);
            printf("Task %s has finished!\n", task->name);
            delete task;
        }
        else {
            run(task, quantum);
            task->burst -= quantum;
            printf("Task %s has been kicked out\n", task->name);
            // CHECK IF THE TASK IS SUPPOSED TO BE SORTED WHEN ITS KICKED OUT BY RR 
            q.push(task);
        }
    }
}

