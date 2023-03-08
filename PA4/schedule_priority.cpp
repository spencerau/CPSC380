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
    printf("Using Priority Scheduler\n");
    while (!pq.empty()) {
        Task *task = pq.top();
        pq.pop();
        printf("Task: %d, Name: %s, Burst: %d, Priority: %d\n", task->tid, task->name, task->burst, task->priority);
        run(task, task->burst);
        printf("Task %s has finished!\n", task->name);
        delete task;
    }
}

