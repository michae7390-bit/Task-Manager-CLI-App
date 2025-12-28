C++ Task Manager (CLI Application)

A simple yet well-structured command-line task manager written in modern C++ (C++17).
This project demonstrates object-oriented design, file persistence, and clean separation of concerns.

 Features

Add new tasks with title and description

View all tasks in a clean CLI menu

Mark tasks as completed

Delete tasks by ID

Persistent storage using a local file (tasks.db)

Modular, extensible architecture

 Project Structure
.
├── main.cpp
├── Task.h
├── Task.cpp
├── TaskManager.h
├── TaskManager.cpp
├── Menu.h
├── Menu.cpp
├── tasks.db        # auto-generated on first run
└── README.md

 Technologies Used

Language: C++17

Standard Library only (no external dependencies)

File I/O for persistence

Object-Oriented Programming (OOP)
Build & Run Instructions
1. Compile

Using g++:

g++ -std=c++17 main.cpp Task.cpp TaskManager.cpp Menu.cpp -o task_manager

2. Run
./task_manager

 Usage

When the program starts, you’ll see a menu:

1. Show Tasks
2. Add Task
3. Remove Task
4. Complete Task
5. Exit


Enter the number corresponding to the action you want.

Tasks are automatically saved when the program exits.

Data persists between runs using tasks.db.

 Data Storage

Tasks are stored in a plain text file (tasks.db) using a custom serialization format:

id|completed|timestamp|title|description


This keeps the project lightweight and dependency-free.

 Design Overview

Task
Represents a single task with metadata and serialization logic.

TaskManager
Handles task storage, loading/saving, and business logic.

Menu
Manages user interaction and CLI flow.

main.cpp
Entry point that wires everything together.

Possible Extensions

Search and filter tasks

Task deadlines and priorities

JSON storage instead of plain text

Unit tests

GUI (Qt / SFML)

Multi-user support

License

This project is provided for educational purposes.
You are free to modify and use it as needed.
