#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include <string>
#include "Task.h"

class TaskManager {
private:
    std::vector<Task> tasks;
    std::string filename;
    int nextId;

    void load();
    void save() const;

public:
    explicit TaskManager(const std::string& filename);
    ~TaskManager();

    void addTask(const std::string& title, const std::string& description);
    void removeTask(int id);
    void completeTask(int id);

    const std::vector<Task>& getTasks() const;
};

#endif
