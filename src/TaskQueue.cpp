#include <iostream>
#include <algorithm>
#include "TaskQueue.h"

TaskQueue::TaskQueue() : nextId(1) {
}

std::vector<Task>::iterator TaskQueue::findById(int id) {
    return std::find_if(tasks.begin(), tasks.end(),
        [id](const Task& t) { return t.id == id; });
}

void TaskQueue::addTask(const std::string& name, TaskPriority priority) {
    tasks.push_back(Task(nextId++, name, priority));
    std::cout << "Task added: [" << nextId - 1 << "] " << name << "\n";
}

void TaskQueue::removeTask(int id) {
    auto it = findById(id);
    if (it == tasks.end()) {
        std::cout << "Task not found: " << id << "\n";
        return;
    }
    std::cout << "Task removed: [" << it->id << "] " << it->name << "\n";
    tasks.erase(it);
}

void TaskQueue::setPriority(int id, TaskPriority priority) {
    auto it = findById(id);
    if (it == tasks.end()) {
        std::cout << "Task not found: " << id << "\n";
        return;
    }
    it->priority = priority;
    std::cout << "Priority updated: [" << it->id << "] " << it->name << " to " << it->priorityToString() << "\n";
}

void TaskQueue::processNext() {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [](const Task& t) { return t.status == TaskStatus::PENDING; });

    if (it == tasks.end()) {
        std::cout << "No pending tasks.\n";
        return;
    }

    it->status = TaskStatus::PROCESSING;
    std::cout << "Processing: [" << it->id << "] " << it->name << "\n";
    it->status = TaskStatus::DONE;
    std::cout << "Done: [" << it->id << "] " << it->name << "\n";
}

void TaskQueue::listTasks() const {
    if (tasks.empty()) {
        std::cout << "Queue is empty.\n";
        return;
    }
    std::cout << "\n--- Task Queue ---\n";
    for (const Task& t : tasks) {
        std::cout << "[" << t.id << "] "
                  << t.name
                  << " | " << t.priorityToString()
                  << " | " << t.statusToString() << "\n";
    }
    std::cout << "------------------\n\n";
}

void TaskQueue::showStatus() const {
    int pending = 0, processing = 0, done = 0;
    for (const Task& t : tasks) {
        if (t.status == TaskStatus::PENDING) pending++;
        else if (t.status == TaskStatus::PROCESSING) processing++;
        else done++;
    }
    std::cout << "\n--- Status ---\n";
    std::cout << "Pending:    " << pending << "\n";
    std::cout << "Processing: " << processing << "\n";
    std::cout << "Done:       " << done << "\n";
    std::cout << "--------------\n\n";
}