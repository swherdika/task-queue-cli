#pragma once

#include <queue>
#include <vector>
#include <string>
#include "Task.h"

class TaskQueue {
private:
    std::vector<Task> tasks;
    int nextId;

    std::vector<Task>::iterator findById(int id);

public:
    TaskQueue();

    void addTask(const std::string& name, TaskPriority priority = TaskPriority::NORMAL);
    void removeTask(int id);
    void processNext();
    void listTasks() const;
    void showStatus() const;
    void setPriority(int id, TaskPriority priority);
    void clearDone();
};