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

int main() {

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