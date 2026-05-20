#pragma once

#include <string>

enum class TaskStatus {
    PENDING,
    PROCESSING,
    DONE
};

enum class TaskPriority {
    LOW,
    NORMAL,
    HIGH
};

struct Task {
    int id;
    std::string name;
    TaskPriority priority;
    TaskStatus status;

    Task(int id, const std::string& name, TaskPriority priority = TaskPriority::NORMAL);

    std::string statusToString() const;
    std::string priorityToString() const;
};