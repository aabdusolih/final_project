#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct employee {
    int id;
    string name;
    int salary;
    string position;
};

int showMenu();
void viewEmployees();

int main() {
    cout << "Welcome to the Employee System!" << endl << endl;
    viewEmployees();
    return 0;
}

int showMenu() {
    int choice;
    cout << "Choose an option from the menu. " << endl;
    cout << "1. Search employees " << endl;
    cout << "2. Update employee information " << endl;
    cout << "3. Add a new employee " << endl;
    cout << "4. Remove an employee " << endl;
    cout << "5. Exit" << endl;
    do {
        if (choice < 1 || choice > 5) {
            cout << "Invalid choice." << endl;
        }
        cout << "Enter your choice: ";
        cin >> choice;
    } while (choice < 1 || choice > 5);
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

    string line;
    // Read each line from the file and print it
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}