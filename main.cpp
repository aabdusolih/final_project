#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include <iomanip>

// comments may be irrelevant and should be changed

using namespace std;

// function to change color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void delay(int seconds) {
    Sleep(seconds * 1000); // Not used in the code yet
}

struct employee {
    int id;
    string name;
    int salary;
    string position;
};

int showMenu();
void viewEmployees();
void addEmployee();
void searchEmployee(string search_id);
void deleteById(string delete_id);
void updateById(string update_id);

int main() {
    int search_choice = 0;
    cout << "Welcome to the Employee System!" << endl << endl;

    // showing menu until user enters 5 for exit
    do {
        int user_choice = showMenu();
        switch (user_choice) {
        case 1: {
            setColor(11); // Green for response
            cout << "\nYou selected to search employees." << endl;
            cout << "Enter 1 to view all employees: " << endl;
            cout << "Enter 2 to search employees by id: " << endl;
            do {
                cout << "Enter your choice: ";
                cin >> search_choice;

                if (search_choice == 1) {
                    viewEmployees();
                    break;
                }
                if (search_choice == 2) {
                    string search_id = "";
                    cout << "Enter the id of the employee to search: ";
                    cin >> search_id;
                    searchEmployee(search_id);
                    break;
                }
            } while (search_choice != 2 && search_choice != 1);
            break;
        }
        case 2: {
            setColor(11); // Green for response
            cout << "\nYou selected to update employee information." << endl;
            string update_id = "";
            cout << "Enter the id of the employee to update: ";
            cin >> update_id;
            updateById(update_id);
            break;
        }
        case 3: {
            setColor(11);
            cout << "\nYou selected to add a new employee." << endl;
            addEmployee();
            break;
        }
        case 4: {
            setColor(11);
            cout << "\nYou selected to remove an employee." << endl;
            string delete_id = "";
            cout << "Enter the id of the employee to delete: ";
            cin >> delete_id;
            deleteById(delete_id);
            break;
        }
        case 5: {
            setColor(11); // Light cyan for exit color
            cout << "\nExiting program..." << endl;
            setColor(7); // Reset color
            return 0;
        }

        default:
            setColor(12); // Red for invalid choice
            cout << "\nInvalid choice. Please try again." << endl;
        }

        setColor(7); // Reset color after response
        cout << endl << "--------------------------------------" << endl; // Add some space for better readability
    } while (true);
}

// function to show menu
int showMenu() {
    int choice;

    setColor(11);
    cout << "=====================================" << endl;
    cout << "       EMPLOYEE MANAGEMENT SYSTEM    " << endl;
    cout << "            Made by C--             "<< endl;
    cout << "=====================================" << endl;

    setColor(14);
    cout << "  1. Search employees" << endl;
    cout << "  2. Update employee information" << endl;
    cout << "  3. Add a new employee" << endl;
    cout << "  4. Remove an employee" << endl;
    cout << "  5. Exit" << endl;

    setColor(11);
    cout << "=====================================" << endl;

    do {
        setColor(10); // Green for menu input
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 5) {
            setColor(12); // Red for invalid choice
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice < 1 || choice > 5);

    setColor(7); // Reset color
    return choice;
}

void viewEmployees() {
    setColor(11); // Green for response
    cout << "\nTrying to open the file..." << endl;
    ifstream file("employee.csv");

    if (!file) {
        setColor(12); // Red for error
        cout << "Error! Could not open file." << endl;
        return;
    }
    cout << "File opening successful." << endl;

    string line;
    bool isHeader = true;
    setColor(15);
    cout << "ID      Name                Salary        Position " << endl;

    while (getline(file, line)) {
        if (isHeader) {
            isHeader = false;
            continue; // skip CSV header line
        }

        stringstream ss(line);
        string id, name, salary, position;

        // parsing
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, salary, ',');
        getline(ss, position, ',');

        int id_length = id.length();
        int name_length = name.length();
        int salary_length = salary.length();
        int position_length = position.length();

        cout << id << setw(8-id_length) << "  "
             << name << setw(20-name_length) << "  "
             << salary << setw(14-salary_length) << "  "
             << position << endl;
    }

    file.close();
}

void addEmployee() {
    int id;
    string name;
    int salary;
    string position;

    setColor(11);

    // getting new employee information
    cout << "Enter employee id: ";
    cin >> id;
    cin.ignore();

    cout << "Enter employee name: ";
    getline(cin, name);

    cout << "Enter employee position: ";
    getline(cin, position);

    cout << "Enter employee salary: ";
    cin >> salary;

    ofstream file("employee.csv", ios::app);
    if (!file) {
        setColor(12); // Red for error
        cout << "Error! Could not open file." << endl;
        return;
    }

    // writing new employee information
    file << id << "," << name << "," << salary << "," << position << endl;
    file.close();

    setColor(10); // Green for success
    cout << "Employee successfully added." << endl;
}

void searchEmployee(string search_id)
{
    bool found = false;
    ifstream file("employee.csv");

    if (!file) {
        setColor(12); // Red for error
        cout << "Error! Could not open file." << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, salary, position;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, salary, ',');
        getline(ss, position, ',');

        if (id == search_id)  // print info if id matches
        {
            found = true;
            setColor(10); // Green for found result
            cout << "ID: " << id
            << ", Name: " << name
            << ", Salary: " << salary
            << ", Position: " << position << endl;
            break;
        }
    }
    if (!found)
    {
        setColor(12); // Red for not found
        cout << "Employee with given id not found in the database." << endl;
    }
}

void deleteById(string delete_id)
{
    ifstream file("employee.csv");
    ofstream tempFile("temp.csv"); // creating temporary file to delete a record
    if (!file || !tempFile)
    {
        setColor(12); // Red for error
        cout << "Error! Could not open file." << endl;
        return;
    }

    string line;
    bool found = false;

    if (getline(file, line)) {
        tempFile << line << endl;  // header line
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, salary, position;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, salary, ',');
        getline(ss, position, ',');

        if (id == delete_id) {
            found = true;
            continue; // skip writing when id found to delete a record
        }

        tempFile << id << "," << name << "," << salary << "," << position << endl;
    }
    file.close();
    tempFile.close();

    if (found) { // rename temp to employee.csv to delete the employee
        remove("employee.csv");
        rename("temp.csv", "employee.csv");
        setColor(10); // Green for success
        cout << "Employee successfully deleted from database." << endl;
    }
    else {
        remove("temp.csv");
        setColor(12); // Red for not found
        cout << "Employee with ID " << delete_id << " was not found." << endl;
    }
}

void updateById(string update_id) {
    ifstream file("employee.csv");
    ofstream tempFile("temp.csv");
    if (!file || !tempFile)
    {
        setColor(12); // Red for error
        cout << "Error! Could not open file." << endl;
        return;
    }

    string line;
    bool found = false;

    // Write the header first
    if (getline(file, line)) {
        tempFile << line << endl;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, salary, position;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, salary, ',');
        getline(ss, position, ',');

        if (id == update_id) {
            found = true;
            int new_salary;
            string new_name, new_position;

            setColor(11);

            // getting information to update

            cout << "Enter new employee name: ";
            cin.ignore();  // Ignore leftover newline character in the input
            getline(cin, new_name);
            cout << "Enter new employee salary: ";
            cin >> new_salary;
            cout << "Enter new employee position: ";
            cin.ignore();  // Ignore leftover newline character
            getline(cin, new_position);

            // Write updated data to the temporary file
            tempFile << id << "," << new_name << "," << new_salary << "," << new_position << endl;
        }
        else {
            // Copy the existing data to the temporary file
            tempFile << id << "," << name << "," << salary << "," << position << endl;
        }
    }

    file.close();
    tempFile.close();

    if (found) { // change temp to employee.csv to update information
        remove("employee.csv");
        rename("temp.csv", "employee.csv");
        setColor(10); // Green for success
        cout << "Employee information updated." << endl;
    }
    else {
        remove("temp.csv");
        setColor(12); // Red for not found
        cout << "Employee with ID " << update_id << " was not found." << endl;
    }
}
