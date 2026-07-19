#include "Task.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

// ============== CONSTRUCTORS ==============

Task::Task() 
    : id(0), completed(false), createdAt(std::time(nullptr)), 
      dueDate(0), completedAt(0), priority(TaskPriority::MEDIUM),
      estimatedHours(0), actualHours(0) {}

Task::Task(int id, const std::string& title, const std::string& description)
    : id(id), title(title), description(description),
      completed(false), createdAt(std::time(nullptr)), 
      dueDate(0), completedAt(0), priority(TaskPriority::MEDIUM),
      estimatedHours(0), actualHours(0) {}

// ============== BASIC GETTERS ==============

int Task::getId() const { return id; }

std::string Task::getTitle() const { return title; }

std::string Task::getDescription() const { return description; }

bool Task::isCompleted() const { return completed; }

std::time_t Task::getCreatedAt() const { return createdAt; }

// ============== EXTENDED GETTERS ==============

std::time_t Task::getDueDate() const { return dueDate; }

std::time_t Task::getCompletedAt() const { return completedAt; }

TaskPriority Task::getPriority() const { return priority; }

std::string Task::getPriorityString() const {
    switch (priority) {
        case TaskPriority::LOW:
            return "LOW";
        case TaskPriority::MEDIUM:
            return "MEDIUM";
        case TaskPriority::HIGH:
            return "HIGH";
        case TaskPriority::CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
    }
}

std::string Task::getCategory() const { return category; }

std::vector<std::string> Task::getTags() const { return tags; }

int Task::getEstimatedHours() const { return estimatedHours; }

int Task::getActualHours() const { return actualHours; }

// ============== BASIC SETTERS ==============

void Task::setTitle(const std::string& t) {
    if (!t.empty()) {
        title = t;
    }
}

void Task::setDescription(const std::string& d) {
    description = d;
}

void Task::markCompleted() {
    if (!completed) {
        completed = true;
        completedAt = std::time(nullptr);
    }
}

// ============== EXTENDED SETTERS ==============

void Task::setDueDate(std::time_t date) {
    dueDate = date;
}

void Task::setPriority(TaskPriority p) {
    priority = p;
}

void Task::setPriorityFromString(const std::string& p) {
    std::string upper_p = p;
    std::transform(upper_p.begin(), upper_p.end(), upper_p.begin(), ::toupper);
    
    if (upper_p == "LOW") {
        priority = TaskPriority::LOW;
    } else if (upper_p == "MEDIUM") {
        priority = TaskPriority::MEDIUM;
    } else if (upper_p == "HIGH") {
        priority = TaskPriority::HIGH;
    } else if (upper_p == "CRITICAL") {
        priority = TaskPriority::CRITICAL;
    }
}

void Task::setCategory(const std::string& cat) {
    if (!cat.empty()) {
        category = cat;
    }
}

void Task::addTag(const std::string& tag) {
    if (!tag.empty() && !hasTag(tag)) {
        tags.push_back(tag);
    }
}

void Task::removeTag(const std::string& tag) {
    auto it = std::find(tags.begin(), tags.end(), tag);
    if (it != tags.end()) {
        tags.erase(it);
    }
}

void Task::setEstimatedHours(int hours) {
    if (hours >= 0) {
        estimatedHours = hours;
    }
}

void Task::setActualHours(int hours) {
    if (hours >= 0) {
        actualHours = hours;
    }
}

void Task::incrementActualHours(int hours) {
    if (hours > 0) {
        actualHours += hours;
    }
}

// ============== UTILITY METHODS ==============

bool Task::isOverdue() const {
    if (completed || dueDate == 0) {
        return false;
    }
    return std::time(nullptr) > dueDate;
}

bool Task::isDueToday() const {
    if (dueDate == 0) {
        return false;
    }
    
    std::time_t now = std::time(nullptr);
    struct tm* now_tm = std::localtime(&now);
    struct tm* due_tm = std::localtime(&dueDate);
    
    return (now_tm->tm_year == due_tm->tm_year &&
            now_tm->tm_mon == due_tm->tm_mon &&
            now_tm->tm_mday == due_tm->tm_mday);
}

bool Task::isDueSoon(int daysAhead) const {
    if (dueDate == 0 || completed) {
        return false;
    }
    
    std::time_t now = std::time(nullptr);
    std::time_t soon = now + (daysAhead * 24 * 60 * 60);
    
    return (dueDate > now && dueDate <= soon);
}

std::string Task::getFormattedDueDate() const {
    if (dueDate == 0) {
        return "No due date";
    }
    
    struct tm* tm_info = std::localtime(&dueDate);
    char buffer[26];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    return std::string(buffer);
}

std::string Task::getFormattedCreatedAt() const {
    struct tm* tm_info = std::localtime(&createdAt);
    char buffer[26];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    return std::string(buffer);
}

std::string Task::getFormattedCompletedAt() const {
    if (completedAt == 0) {
        return "Not completed";
    }
    
    struct tm* tm_info = std::localtime(&completedAt);
    char buffer[26];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    return std::string(buffer);
}

std::string Task::getStatus() const {
    if (completed) {
        return "Completed";
    } else if (isOverdue()) {
        return "Overdue";
    } else if (isDueToday()) {
        return "Due Today";
    } else if (isDueSoon()) {
        return "Due Soon";
    } else {
        return "Pending";
    }
}

std::string Task::getFullDetails() const {
    std::ostringstream oss;
    oss << "=== Task Details ===" << std::endl;
    oss << "ID: " << id << std::endl;
    oss << "Title: " << title << std::endl;
    oss << "Description: " << description << std::endl;
    oss << "Status: " << getStatus() << std::endl;
    oss << "Priority: " << getPriorityString() << std::endl;
    
    if (!category.empty()) {
        oss << "Category: " << category << std::endl;
    }
    
    oss << "Created: " << getFormattedCreatedAt() << std::endl;
    
    if (dueDate != 0) {
        oss << "Due: " << getFormattedDueDate() << std::endl;
    }
    
    if (completed) {
        oss << "Completed: " << getFormattedCompletedAt() << std::endl;
    }
    
    if (estimatedHours > 0) {
        oss << "Estimated Hours: " << estimatedHours << std::endl;
        oss << "Actual Hours: " << actualHours << std::endl;
    }
    
    if (!tags.empty()) {
        oss << "Tags: ";
        for (size_t i = 0; i < tags.size(); ++i) {
            oss << tags[i];
            if (i < tags.size() - 1) oss << ", ";
        }
        oss << std::endl;
    }
    
    return oss.str();
}

bool Task::isValid() const {
    return !title.empty() && id >= 0;
}

bool Task::hasTag(const std::string& tag) const {
    return std::find(tags.begin(), tags.end(), tag) != tags.end();
}

// ============== COMPARISON OPERATORS ==============

bool Task::operator==(const Task& other) const {
    return id == other.id && title == other.title && completed == other.completed;
}

bool Task::operator!=(const Task& other) const {
    return !(*this == other);
}

bool Task::operator<(const Task& other) const {
    if (priority != other.priority) {
        return static_cast<int>(priority) > static_cast<int>(other.priority);  // Higher priority first
    }
    
    if (dueDate != 0 && other.dueDate != 0) {
        return dueDate < other.dueDate;  // Earlier due date first
    }
    
    return id < other.id;
}

bool Task::operator>(const Task& other) const {
    return other < *this;
}

// ============== SERIALIZATION ==============

std::string Task::serialize() const {
    std::ostringstream oss;
    oss << id << "|" << completed << "|" << createdAt << "|" 
        << completedAt << "|" << static_cast<int>(priority) << "|"
        << dueDate << "|" << category << "|" << title << "|" 
        << description << "|" << estimatedHours << "|" << actualHours;
    
    // Append tags
    oss << "|";
    for (size_t i = 0; i < tags.size(); ++i) {
        oss << tags[i];
        if (i < tags.size() - 1) oss << ",";
    }
    
    return oss.str();
}

std::string Task::serializeJSON() const {
    std::ostringstream oss;
    oss << "{\"id\":" << id << ",\"title\":\"" << title 
        << "\",\"description\":\"" << description 
        << "\",\"completed\":" << (completed ? "true" : "false")
        << ",\"priority\":\"" << getPriorityString()
        << "\",\"category\":\"" << category
        << "\",\"createdAt\":" << createdAt
        << ",\"dueDate\":" << dueDate
        << ",\"completedAt\":" << completedAt
        << ",\"estimatedHours\":" << estimatedHours
        << ",\"actualHours\":" << actualHours
        << ",\"tags\":[";
    
    for (size_t i = 0; i < tags.size(); ++i) {
        oss << "\"" << tags[i] << "\"";
        if (i < tags.size() - 1) oss << ",";
    }
    
    oss << "]}";
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

    std::getline(ss, segment, '|');
    task.completedAt = std::stoll(segment);

    std::getline(ss, segment, '|');
    task.priority = static_cast<TaskPriority>(std::stoi(segment));

    std::getline(ss, segment, '|');
    task.dueDate = std::stoll(segment);

    std::getline(ss, segment, '|');
    task.category = segment;

    std::getline(ss, task.title, '|');
    std::getline(ss, task.description, '|');

    std::getline(ss, segment, '|');
    task.estimatedHours = std::stoi(segment);

    std::getline(ss, segment, '|');
    task.actualHours = std::stoi(segment);

    // Parse tags
    std::getline(ss, segment);
    if (!segment.empty()) {
        std::stringstream tag_stream(segment);
        std::string tag;
        while (std::getline(tag_stream, tag, ',')) {
            if (!tag.empty()) {
                task.tags.push_back(tag);
            }
        }
    }

    return task;
}

Task Task::deserializeJSON(const std::string& json) {
    Task task;
    // Basic JSON parsing (simplified - a real implementation would use a JSON library)
    // This is a placeholder that would need a proper JSON parser
    return task;
}

// ============== UTILITY ==============

void Task::reset() {
    id = 0;
    title.clear();
    description.clear();
    completed = false;
    createdAt = std::time(nullptr);
    dueDate = 0;
    completedAt = 0;
    priority = TaskPriority::MEDIUM;
    category.clear();
    tags.clear();
    estimatedHours = 0;
    actualHours = 0;
}

void Task::clearTags() {
    tags.clear();
}
