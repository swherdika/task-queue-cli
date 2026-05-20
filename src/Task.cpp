#include "Task.h"

Task::Task(int id, const std::string& name, TaskPriority priority)
    : id(id), name(name), priority(priority), status(TaskStatus::PENDING) {
}

std::string Task::statusToString() const {
    switch (status) {
        case TaskStatus::PENDING:    return "PENDING";
        case TaskStatus::PROCESSING: return "PROCESSING";
        case TaskStatus::DONE:       return "DONE";
        default:                     return "UNKNOWN";
    }
}

std::string Task::priorityToString() const {
    switch (priority) {
        case TaskPriority::LOW:    return "LOW";
        case TaskPriority::NORMAL: return "NORMAL";
        case TaskPriority::HIGH:   return "HIGH";
        default:                   return "UNKNOWN";
    }
}