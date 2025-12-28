#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime>

class Task {
private:
    int id;
    std::string title;
    std::string description;
    bool completed;
    std::time_t createdAt;

public:
    Task();
    Task(int id, const std::string& title, const std::string& description);

    int getId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    bool isCompleted() const;
    std::time_t getCreatedAt() const;

    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void markCompleted();

    std::string serialize() const;
    static Task deserialize(const std::string& line);
};

#endif
