/**
 * @author Spencer Au
 * ID: 2385256
 * spau@chapman.edu
 * CPSC 380 - Section 1
 * PA4
 * 
 * Uses Shortest Job First to schedule tasks
 **/

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
        return t1->burst > t2->burst;
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
    printf("Using SJF Scheduler\n");
    while (!pq.empty()) {
        Task *task = pq.top();
        pq.pop();
        printf("Task: %d, Name: %s, Burst: %d\n", task->tid, task->name, task->burst);
        run(task, task->burst);
        printf("Task %s has finished!\n", task->name);
        delete task;
    }
}

