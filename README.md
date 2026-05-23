# task-queue-cli

A lightweight command-line task queue manager written in C++, where tasks are processed based on priority rather than insertion order.

## Background

Built as a personal project to apply concepts from my professional experience working with queue-based scheduling systems in embedded software. The goal was simple: implement a clean, well-structured CLI tool in C++ that demonstrates priority queue logic from the ground up.

## Features

- Add tasks with optional priority levels (low, normal, high)
- Process tasks in priority order — high priority always goes first
- Update priority of existing tasks
- Remove tasks by ID
- View full task list with status and priority
- Queue status summary

## Demo

```
--- Task Queue CLI ---
Commands:
  add <name> [priority]   Add a task (priority: low, normal, high)
  remove <id>             Remove a task by id
  process                 Process the next pending task
  list                    List all tasks
  status                  Show queue status summary
  priority <id> <level>   Update a task's priority
  help                    Show this help message
  exit                    Exit the program
----------------------

> add "Fix login bug" high
Task added: [1] Fix login bug
> add "Write docs" low
Task added: [2] Write docs
> add "Code review" normal
Task added: [3] Code review
> list

--- Task Queue ---
[1] Fix login bug | HIGH | PENDING
[2] Write docs | LOW | PENDING
[3] Code review | NORMAL | PENDING
------------------

> process
Processing: [1] Fix login bug
Done: [1] Fix login bug
> process
Processing: [3] Code review
Done: [3] Code review
> process
Processing: [2] Write docs
Done: [2] Write docs
> process
No pending tasks.
> 
```

## Commands

| Command | Description |
|---|---|
| `add <name> [priority]` | Add a task (priority: low, normal, high) |
| `remove <id>` | Remove a task by ID |
| `process` | Process the highest priority pending task |
| `list` | List all tasks with status and priority |
| `status` | Show summary of pending, processing, done |
| `priority <id> <level>` | Update a task's priority |
| `help` | Show available commands |
| `exit` | Exit the program |

## Building

Requires `g++` with C++17 support.

```bash
make
```

Binary will be output to `build/task-queue-cli`.

## Tech

- C++17
- STL (`vector`, `algorithm`, `sstream`)
- Makefile build system 