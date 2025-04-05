#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

using namespace std;

struct employee {
    int id;
    string name;
    int salary;
    string position;
};

int showMenu();
void viewEmployees();
void addEmployee();

int main() {
    int search_choice = 0;
    cout << "Welcome to the Employee System!" << endl << endl;
    int user_choice = showMenu();
    switch (user_choice) {
        case 1: {
            cout << "Enter 1 to view all employees: " << endl;
            cout << "Enter 2 to search employees by id: " << endl;
            do {
                cout << "Enter your choice: ";
                cin >> search_choice;

                if (search_choice == 1) {
                    viewEmployees();
                    return 0;
                }
                if (search_choice == 2) {
                    return 0; // Unfinished part
                }
            } while (search_choice != 2 || search_choice != 1);
            break;
        }
        case 2: {
            // Unfinished
            break;
        }
        case 3: {
            addEmployee();
            break;
        }
        case 5: {
                setColor(11); // Light cyan for exit color
                cout << "\nExiting program..." << std::endl;
                setColor(7); // Reset color
                break;
        }

        default:
            cout << "Invalid choice." << endl;
    }

    return 0;
}

int showMenu() {
    int choice;

    // Header
    setColor(11); // Light cyan
    cout << "=====================================" << std::endl;
    cout << "       EMPLOYEE MANAGEMENT SYSTEM    " << std::endl;
    cout << "=====================================" << std::endl;

    // Menu options
    setColor(14); // Yellow
    cout << "  1. Search employees" << std::endl;
    cout << "  2. Update employee information" << std::endl;
    cout << "  3. Add a new employee" << std::endl;
    cout << "  4. Remove an employee" << std::endl;
    cout << "  5. Exit" << std::endl;

    // Footer
    setColor(11);
    cout << "=====================================" << std::endl;

    // User input loop
    do {
        setColor(10); // Green for input prompt
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 5) {
            setColor(12); // Red for error
            cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice < 1 || choice > 5);

    setColor(7); // Reset color
    return choice;
}


void viewEmployees() {
    cout << "Trying to open the file..." << endl;
    // Open the file
    ifstream file("employee.txt");

    // Check if the file was opened successfully
    if (!file) {
        cout << "Error! Could not open file." << endl;
        return;
    }
    cout << "File opening successful." << endl;
    string line;
    // Read each line from the file and print it
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}
void addEmployee() {
    int id;
    string name;
    int salary;
    string position;
    cout << "Enter employee id: ";
    cin >> id;
    cin.ignore();
    cout << "Enter employee name: ";
    getline(cin, name);
    cout << "Enter employee position: ";
    getline(cin, position);
    cout << "Enter employee salary: ";
    cin >> salary;

    ofstream file("employee.txt", ios::app);
    if (!file) {
        cout << "Error! Could not open file." << endl;
        return;
    }
    file << "id: " << id << ", name: \"" << name << "\", salary: " << salary << ", position: \"" << position << "\"" << endl;
    file.close();
    cout << "Employee successfully added." << endl;
}