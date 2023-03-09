#include "schedulers.h"
#include "CPU.h"
#include "task.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <queue>

#include <iostream>

using namespace std;

queue<Task*> q; 
int tNum = 1;

void add(char *name, int priority, int burst) {
    Task *task = new Task;
    task->name = name;
    task->priority = priority;
    task->burst = burst;
    // tid is the task number
    task->tid = tNum;
    tNum++;
    q.push(task);
}

void schedule() {
    printf("Using FCFS Scheduler\n");
    while (!q.empty()) {
        Task *task = q.front();
        q.pop();
        printf("Task: %d, Name: %s, Burst: %d\n", task->tid, task->name, task->burst);
        run(task, task->burst);
        printf("Task %s has finished!\n", task->name);
        delete task;
    }
}