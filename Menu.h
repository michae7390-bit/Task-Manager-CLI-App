#ifndef MENU_H
#define MENU_H

#include "TaskManager.h"

class Menu {
private:
    TaskManager& manager;

    void showTasks() const;
    void addTask();
    void removeTask();
    void completeTask();

public:
    explicit Menu(TaskManager& manager);
    void run();
};

#endif
