#include <iostream>
#include <sstream>
#include "TaskQueue.h"

TaskPriority parsePriority(const std::string& s) {
    if (s == "high") return TaskPriority::HIGH;
    if (s == "low")  return TaskPriority::LOW;
    return TaskPriority::NORMAL;
}

void printHelp() {
    std::cout << "\n--- Task Queue CLI ---\n";
    std::cout << "Commands:\n";
    std::cout << "  add <name> [priority]   Add a task (priority: low, normal, high)\n";
    std::cout << "  remove <id>             Remove a task by id\n";
    std::cout << "  process                 Process the next pending task\n";
    std::cout << "  list                    List all tasks\n";
    std::cout << "  status                  Show queue status summary\n";
    std::cout << "  priority <id> <level>   Update a task's priority\n";
    std::cout << "  help                    Show this help message\n";
    std::cout << "  exit                    Exit the program\n";
    std::cout << "  clear                   Clear all completed tasks\n";
    std::cout << "----------------------\n\n";
}

int main() {
    TaskQueue queue;
    const std::string savePath = "data/tasks.csv";
    queue.load(savePath);

    std::string line;
    printHelp();

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "exit") {
            queue.save(savePath);
            break;
        } else if (command == "help") {
            printHelp();
        } else if (command == "list") {
            queue.listTasks();
        } else if (command == "status") {
            queue.showStatus();
        } else if (command == "process") {
            queue.processNext();
            queue.save(savePath);
        } else if (command == "add") {
            std::string name, priority, extra;

            if (iss.peek() == ' ') iss.get(); // skip leading space

            if (iss.peek() == '"') {
                iss.get();                         // consume opening quote
                std::getline(iss, name, '"');      // read until closing quote
                iss >> priority;
            } else {
                iss >> name >> priority;
            }

            // check for unexpected extra arguments
            if (iss >> extra) {
                std::cout << "Error: task name with spaces must be wrapped in quotes.\n";
                std::cout << "  Usage: add <name> [priority]\n";
                std::cout << "  Usage: add \"Fix login bug\" high\n";
                continue;
            }

            queue.addTask(name, parsePriority(priority));
            queue.save(savePath);
        } else if (command == "remove") {
            int id;
            iss >> id;
            queue.removeTask(id);
            queue.save(savePath);
        } else if (command == "priority") {
            int id;
            std::string level;
            iss >> id >> level;
            queue.setPriority(id, parsePriority(level));
            queue.save(savePath);
        } else if (command == "clear") {
            queue.clearDone();
            queue.save(savePath);
        } else if (!command.empty()) {
            std::cout << "Unknown command: " << command << ". Type 'help' to see commands.\n";
        }
    }

    return 0;
}