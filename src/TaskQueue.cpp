#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
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

void TaskQueue::clearDone() {
    auto it = tasks.begin();
    while (it != tasks.end()) {
        if (it->status == TaskStatus::DONE) {
            it = tasks.erase(it);
        } else {
            ++it;
        }
    }
    std::cout << "Cleared all completed tasks.\n";
}

void TaskQueue::save(const std::string& filepath) const {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cout << "Warning: could not save tasks to " << filepath << "\n";
        return;
    }
    for (const Task& t : tasks) {
        file << t.id << ","
             << t.name << ","
             << t.priorityToString() << ","
             << t.statusToString() << "\n";
    }
}

void TaskQueue::load(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return; // no save file yet, silent

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string idStr, name, priorityStr, statusStr;

        std::getline(iss, idStr, ',');
        std::getline(iss, name, ',');
        std::getline(iss, priorityStr, ',');
        std::getline(iss, statusStr, ',');

        int id = std::stoi(idStr);
        TaskPriority priority = TaskPriority::NORMAL;
        if (priorityStr == "HIGH") priority = TaskPriority::HIGH;
        if (priorityStr == "LOW")  priority = TaskPriority::LOW;

        TaskStatus status = TaskStatus::PENDING;
        if (statusStr == "DONE") status = TaskStatus::DONE;

        Task t(id, name, priority);
        t.status = status;
        tasks.push_back(t);

        if (id >= nextId) nextId = id + 1;
    }
    std::cout << "Tasks loaded.\n";
}