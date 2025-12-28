#include "TaskManager.h"
#include <fstream>
#include <algorithm>

TaskManager::TaskManager(const std::string& file)
    : filename(file), nextId(1) {
    load();
}

TaskManager::~TaskManager() {
    save();
}

void TaskManager::load() {
    std::ifstream in(filename);
    if (!in) return;

    std::string line;
    while (std::getline(in, line)) {
        Task task = Task::deserialize(line);
        tasks.push_back(task);
        nextId = std::max(nextId, task.getId() + 1);
    }
}

void TaskManager::save() const {
    std::ofstream out(filename);
    for (const auto& task : tasks) {
        out << task.serialize() << "\n";
    }
}

void TaskManager::addTask(const std::string& title, const std::string& description) {
    tasks.emplace_back(nextId++, title, description);
}

void TaskManager::removeTask(int id) {
    tasks.erase(
        std::remove_if(tasks.begin(), tasks.end(),
            [id](const Task& t) { return t.getId() == id; }),
        tasks.end()
    );
}

void TaskManager::completeTask(int id) {
    for (auto& task : tasks) {
        if (task.getId() == id) {
            task.markCompleted();
            return;
        }
    }
}

const std::vector<Task>& TaskManager::getTasks() const {
    return tasks;
}
