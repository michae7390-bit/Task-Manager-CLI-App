#include "Menu.h"
#include <iostream>

Menu::Menu(TaskManager& mgr) : manager(mgr) {}

void Menu::run() {
    while (true) {
        std::cout << "\n1. Show Tasks\n2. Add Task\n3. Remove Task\n4. Complete Task\n5. Exit\nChoice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: showTasks(); break;
            case 2: addTask(); break;
            case 3: removeTask(); break;
            case 4: completeTask(); break;
            case 5: return;
            default: std::cout << "Invalid choice\n";
        }
    }
}

void Menu::showTasks() const {
    for (const auto& task : manager.getTasks()) {
        std::cout << task.getId() << ". "
                  << task.getTitle()
                  << (task.isCompleted() ? " [DONE]\n" : "\n");
    }
}

void Menu::addTask() {
    std::cin.ignore();
    std::string title, description;

    std::cout << "Title: ";
    std::getline(std::cin, title);
    std::cout << "Description: ";
    std::getline(std::cin, description);

    manager.addTask(title, description);
}

void Menu::removeTask() {
    int id;
    std::cout << "Task ID: ";
    std::cin >> id;
    manager.removeTask(id);
}

void Menu::completeTask() {
    int id;
    std::cout << "Task ID: ";
    std::cin >> id;
    manager.completeTask(id);
}
