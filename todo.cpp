#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Task {
    string description;
    bool completed;

    Task(string desc, bool comp = false) : description(desc), completed(comp) {}
};

void displayMenu() {
    cout << "\n======= To-Do List =======\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Complete Task\n";
    cout << "4. Save and Exit\n";
    cout << "===========================\n";
}

void addTask(vector<Task> &tasks) {
    string description;
    cout << "Enter task description: ";
    getline(cin, description);
    tasks.push_back(Task(description));
    cout << "Task added!\n";
}

void viewTasks(const vector<Task> &tasks) {
    cout << "\n======= Tasks =======\n";
    if (tasks.empty()) {
        cout << "No tasks!\n";
    } else {
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << (tasks[i].completed ? "[X] " : "[ ] ") << tasks[i].description << "\n";
        }
    }
    cout << "=====================\n";
}

void completeTask(vector<Task> &tasks) {
    int taskNumber;
    cout << "Enter task number to complete: ";
    cin >> taskNumber;
    cin.ignore();  // to ignore the newline character left by cin
    if (taskNumber > 0 && taskNumber <= static_cast<int>(tasks.size())) {
        tasks[taskNumber - 1].completed = true;
        cout << "Task marked as completed!\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

void saveTasks(const vector<Task> &tasks, const string &filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto &task : tasks) {
            file << task.description << "\n" << task.completed << "\n";
        }
        file.close();
        cout << "Tasks saved to '" << filename << "'.\n";
    } else {
        cout << "Error: Unable to save tasks to '" << filename << "'.\n";
    }
}
//ofstream- This class describes an output stream. It is used to create files and to write data to files. 
//ifstream- This class describes an input stream. It's a program that reads data from files and displays it
void loadTasks(vector<Task> &tasks, const string &filename) {
    ifstream file(filename);
    if (file.is_open()) {
        tasks.clear();  // Clear existing tasks
        string description;
        bool completed;
        while (getline(file, description) && file >> completed) {
            file.ignore();  // to ignore the newline character after the boolean
            tasks.push_back(Task(description, completed));
        }
        file.close();
        cout << "Tasks loaded from '" << filename << "'.\n";
    } else {
        cout << "No existing tasks found. Starting with an empty list.\n";
    }
}

int main() {
    vector<Task> tasks;
    string filename = "tasks.txt";
    loadTasks(tasks, filename);

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // to ignore the newline character left by cin

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                completeTask(tasks);
                break;
            case 4:
                saveTasks(tasks, filename);
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
