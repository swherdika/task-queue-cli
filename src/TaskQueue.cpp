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
    auto highest = tasks.end();

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->status != TaskStatus::PENDING) continue;

        if (highest == tasks.end() ||
            static_cast<int>(it->priority) > static_cast<int>(highest->priority)) {
            highest = it;
        }
    }

    if (highest == tasks.end()) {
        std::cout << "No pending tasks.\n";
        return;
    }

    highest->status = TaskStatus::PROCESSING;
    std::cout << "Processing: [" << highest->id << "] " << highest->name << "\n";
    highest->status = TaskStatus::DONE;
    std::cout << "Done: [" << highest->id << "] " << highest->name << "\n";
}

void TaskQueue::listTasks() const {
    bool hasPending = false;
    bool hasDone = false;

    std::cout << "\n--- PENDING ---\n";
    for (const Task& t : tasks) {
        if (t.status == TaskStatus::PENDING) {
            std::cout << "[" << t.id << "] "
                      << t.name
                      << " | " << t.priorityToString() << "\n";
            hasPending = true;
        }
    }
    if (!hasPending) std::cout << "No pending tasks.\n";

    std::cout << "\n--- DONE ---\n";
    for (const Task& t : tasks) {
        if (t.status == TaskStatus::DONE) {
            std::cout << "[" << t.id << "] "
                      << t.name
                      << " | " << t.priorityToString() << "\n";
            hasDone = true;
        }
    }
    if (!hasDone) std::cout << "No completed tasks.\n";

    std::cout << "\n";
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