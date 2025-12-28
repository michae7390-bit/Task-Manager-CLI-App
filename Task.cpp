#include "Task.h"
#include <sstream>

Task::Task() : id(0), completed(false), createdAt(std::time(nullptr)) {}

Task::Task(int id, const std::string& title, const std::string& description)
    : id(id), title(title), description(description),
      completed(false), createdAt(std::time(nullptr)) {}

int Task::getId() const { return id; }
std::string Task::getTitle() const { return title; }
std::string Task::getDescription() const { return description; }
bool Task::isCompleted() const { return completed; }
std::time_t Task::getCreatedAt() const { return createdAt; }

void Task::setTitle(const std::string& t) { title = t; }
void Task::setDescription(const std::string& d) { description = d; }
void Task::markCompleted() { completed = true; }

std::string Task::serialize() const {
    std::ostringstream oss;
    oss << id << "|" << completed << "|" << createdAt << "|" << title << "|" << description;
    return oss.str();
}

Task Task::deserialize(const std::string& line) {
    std::stringstream ss(line);
    Task task;
    std::string segment;

    std::getline(ss, segment, '|');
    task.id = std::stoi(segment);

    std::getline(ss, segment, '|');
    task.completed = (segment == "1");

    std::getline(ss, segment, '|');
    task.createdAt = std::stoll(segment);

    std::getline(ss, task.title, '|');
    std::getline(ss, task.description);

    return task;
}
