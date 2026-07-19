/**
 * @file Menu.h
 * @brief Command-line menu interface for the Task Manager application.
 * 
 * This class provides an interactive menu system for users to manage tasks,
 * including viewing, adding, removing, and marking tasks as complete.
 */

#ifndef MENU_H
#define MENU_H

#include "TaskManager.h"

/**
 * @class Menu
 * @brief Manages the user interface and interaction flow for task management operations.
 * 
 * The Menu class handles all user interactions through a command-line interface,
 * delegating task operations to the TaskManager instance.
 */
class Menu {
private:
    // ========== Data Members ==========
    TaskManager& manager;  ///< Reference to the TaskManager instance

    // ========== Private Helper Methods ==========
    
    /**
     * @brief Displays all current tasks in a formatted manner.
     */
    void showTasks() const;

    /**
     * @brief Prompts user for task details and adds a new task.
     */
    void addTask();

    /**
     * @brief Prompts user to select and remove an existing task.
     */
    void removeTask();

    /**
     * @brief Prompts user to select and mark a task as complete.
     */
    void completeTask();

    /**
     * @brief Displays the main menu options to the user.
     */
    void displayMenuOptions() const;

    /**
     * @brief Handles invalid user input with an error message.
     */
    void handleInvalidInput() const;

public:
    // ========== Constructors ==========
    
    /**
     * @brief Constructs a Menu instance with a reference to TaskManager.
     * 
     * @param manager Reference to the TaskManager instance for delegating operations.
     * 
     * @note The Menu holds a reference; ensure the TaskManager outlives the Menu instance.
     */
    explicit Menu(TaskManager& manager);

    // ========== Deleted Constructors ==========
    Menu(const Menu&) = delete;             ///< Copy constructor (deleted)
    Menu& operator=(const Menu&) = delete;  ///< Copy assignment (deleted)

    // ========== Public Methods ==========
    
    /**
     * @brief Starts the main menu loop for user interaction.
     * 
     * This method displays the menu, accepts user input, and delegates to the
     * appropriate handler methods until the user chooses to exit.
     * 
     * @note This is a blocking call that runs until the user selects exit.
     */
    void run();
};

#endif  // MENU_H
