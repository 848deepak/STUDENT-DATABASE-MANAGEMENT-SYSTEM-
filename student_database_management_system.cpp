#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <regex>
using namespace std;
//name TRANNUM UID:CO23367
// Stct to store subject scheme details
struct Scheme {
    char subjectCode[20];
    char subjectTitle[50];
    int maxMarksSessional;
    int maxMarksTheory;
    Scheme* next;
    Scheme* prev;
};

// Strct to store student details
struct Student {
    int enrollmentNumber;
    char name[50];
    char fatherName[50];
    char dob[11]; // Format: DD-MM-YYYY
    int semester;
    int admissionYear;
    Scheme* subjectScheme; // Pointer to subject scheme
    int marksSessional;
    int marksTheory;
    Student* next;
    Student* prev;
};

// Global head pointers for doubly linked lists
Student* studentHead = nullptr;
Scheme* schemeHead = nullptr;

// Fun declarations
void addScheme();
void deleteScheme(const string& subjectCode);
void updateScheme(const string& subjectCode);
void addStudent();
void printReportCard(int enrollmentNumber);
void measurePerformance();
void sortStudentsByField(const string& field);
void logAction(const string& action);
bool isValidDOB(const string& dob);

// Fun to log actions
void logAction(const string& action) {
    ofstream logFile("actions_log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << action << endl;
        logFile.close();
    }
}


// Function to validate Date of Birth format
bool isValidDOB(const string& dob) {
    regex dobPattern("^\\d{2}-\\d{2}-\\d{4}$"); // DD-MM-YYYY
    if (!regex_match(dob, dobPattern)) {
        return false;
    }
    int day = stoi(dob.substr(0, 2));
    int month = stoi(dob.substr(3, 2));
    int year = stoi(dob.substr(6, 4));

    // Check for valid day, month, and year ranges
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false; // Months with 30 days
    if (month == 2) { // February checks
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap && day > 29) return false;
        if (!isLeap && day > 28) return false;
    }

    // Validate the year range
    int currentYear = 2024; // Set to the current year or get dynamically
    if (year < 1900 || year > currentYear) return false;

    return true;
}

// Function to add a scheme to the database
void addScheme() {
    Scheme* newScheme = new Scheme;
    cout << "Enter Subject Code: ";
    cin >> newScheme->subjectCode;
    cout << "Enter Subject Title: ";
    cin.ignore();
    cin.getline(newScheme->subjectTitle, 50);
    cout << "Enter Maximum Marks for Sessional: ";
    cin >> newScheme->maxMarksSessional;
    cout << "Enter Maximum Marks for Theory: ";
    cin >> newScheme->maxMarksTheory;

    newScheme->next = nullptr;
    newScheme->prev = nullptr;

    if (schemeHead == nullptr) {
        schemeHead = newScheme;
    } else {
        Scheme* temp = schemeHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newScheme;
        newScheme->prev = temp;
    }
    cout << "Scheme added successfully.\n";
    logAction("Scheme added: " + string(newScheme->subjectCode));
}

// Function to delete a scheme from the database
void deleteScheme(const string& subjectCode) {
    Scheme* temp = schemeHead;
    while (temp != nullptr && temp->subjectCode != subjectCode) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Scheme not found.\n";
        return;
    }
    if (temp->prev != nullptr) temp->prev->next = temp->next;
    if (temp->next != nullptr) temp->next->prev = temp->prev;
    if (temp == schemeHead) schemeHead = temp->next;
    delete temp;
    cout << "Scheme deleted successfully.\n";
    logAction("Scheme deleted: " + subjectCode);
}

// Function to update a scheme in the database
void updateScheme(const string& subjectCode) {
    Scheme* temp = schemeHead;
    while (temp != nullptr && temp->subjectCode != subjectCode) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Scheme not found.\n";
        return;
    }
    cout << "Enter new Subject Title: ";
    cin.ignore();
    cin.getline(temp->subjectTitle, 50);
    cout << "Enter new Maximum Marks for Sessional: ";
    cin >> temp->maxMarksSessional;
    cout << "Enter new Maximum Marks for Theory: ";
    cin >> temp->maxMarksTheory;
    cout << "Scheme updated successfully.\n";
    logAction("Scheme updated: " + subjectCode);
}

// Function to add a student to the records
void addStudent() {
    Student* newStudent = new Student;
    cout << "Enter Enrollment Number: ";
    cin >> newStudent->enrollmentNumber;
    cout << "Enter Student Name: ";
    cin.ignore();
    cin.getline(newStudent->name, 50);
    cout << "Enter Father's Name: ";
    cin.getline(newStudent->fatherName, 50);

    // DOB Validation
    while (true) {
        cout << "Enter Date of Birth (DD-MM-YYYY): ";
        string dob;
        cin >> dob;
        if (isValidDOB(dob)) {
            strcpy(newStudent->dob, dob.c_str());
            break;
        } else {
            cout << "Invalid DOB format. Please enter in DD-MM-YYYY format.\n";
        }
    }

    cout << "Enter Semester: ";
    cin >> newStudent->semester;
    cout << "Enter Year of Admission: ";
    cin >> newStudent->admissionYear;

    cout << "Enter Marks Awarded in Sessional: ";
    cin >> newStudent->marksSessional;
    cout << "Enter Marks Awarded in Theory: ";
    cin >> newStudent->marksTheory;

    newStudent->next = nullptr;
    newStudent->prev = nullptr;

    if (studentHead == nullptr) {
        studentHead = newStudent;
    } else {
        Student* temp = studentHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newStudent;
        newStudent->prev = temp;
    }
    cout << "Student added successfully.\n";
    logAction("Student added: Enrollment Number " + to_string(newStudent->enrollmentNumber));
}



// Function to measure the performance of certain operations
void measurePerformance() {
    auto start = chrono::high_resolution_clock::now();
    addStudent();  // Example: measuring time for addition
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Time taken for addition: " << elapsed.count() << " seconds\n";
}
// Function to print the report card of a student
void printReportCard(int enrollmentNumber) {
    Student* temp = studentHead;
    while (temp != nullptr && temp->enrollmentNumber != enrollmentNumber) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Student not found.\n";
        return;
    }
    cout << "Report Card for " << temp->name << " (" << temp->enrollmentNumber << ")\n";
    cout << "Semester: " << temp->semester << ", Year of Admission: " << temp->admissionYear << "\n";
    cout << "Marks Awarded - Sessional: " << temp->marksSessional << ", Theory: " << temp->marksTheory << "\n";
}

// Function to display all student records
void displayAllRecords() {
    if (studentHead == nullptr) {
        cout << "No student records available.\n";
        return;
    }
    Student* temp = studentHead;
    while (temp != nullptr) {
        cout << "Enrollment Number: " << temp->enrollmentNumber << "\n";
        cout << "Name: " << temp->name << "\n";
        cout << "Father's Name: " << temp->fatherName << "\n";
        cout << "Date of Birth: " << temp->dob << "\n";
        cout << "Semester: " << temp->semester << "\n";
        cout << "Admission Year: " << temp->admissionYear << "\n";
        cout << "Marks - Sessional: " << temp->marksSessional << ", Theory: " << temp->marksTheory << "\n";
        cout << "------------------------------\n";
        temp = temp->next;
    }
}
// Function to sort students by a specified field
void sortStudentsByField(const string& field) {
    if (studentHead == nullptr) return;
    bool swapped;
    do {
        swapped = false;
        Student* current = studentHead;
        while (current->next != nullptr) {
            bool condition = false;
            if (field == "name") {
                condition = strcmp(current->name, current->next->name) > 0;
            } else if (field == "enrollmentNumber") {
                condition = current->enrollmentNumber > current->next->enrollmentNumber;
            }
            if (condition) {
                swap(current->name, current->next->name);
                swap(current->enrollmentNumber, current->next->enrollmentNumber);
                swap(current->fatherName, current->next->fatherName);
                swap(current->dob, current->next->dob);
                swap(current->semester, current->next->semester);
                swap(current->admissionYear, current->next->admissionYear);
                swap(current->marksSessional, current->next->marksSessional);
                swap(current->marksTheory, current->next->marksTheory);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    cout << "Students sorted by " << field << ".\n";
}

// Main function to display menu and handle user choices
int main() {
    int choice;
    do {
        cout << "\n1. Add Scheme\n2. Delete Scheme\n3. Update Scheme\n4. Add Student\n5. Print Report Card\n6. Measure Performance\n7. Sort Students\n8. Display All Records\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addScheme(); break;
            case 2: {
                string subjectCode;
                cout << "Enter Subject Code to delete: ";
                cin >> subjectCode;
                deleteScheme(subjectCode);
                break;
            }
            case 3: {
                string subjectCode;
                cout << "Enter Subject Code to update: ";
                cin >> subjectCode;
                updateScheme(subjectCode);
                break;
            }
            case 4: addStudent(); break;
            case 5: {
                int enrollmentNumber;
                cout << "Enter Enrollment Number to print report: ";
                cin >> enrollmentNumber;
                printReportCard(enrollmentNumber);
                break;
            }
            case 6: measurePerformance(); break;
            case 7: {
                string field;
                cout << "Enter field to sort by (name/enrollmentNumber): ";
                cin >> field;
                sortStudentsByField(field);
                break;
            }
            case 8: displayAllRecords(); break;
            case 0: 
                cout << "Exiting program.\n"; 
                logAction("Program exited.");
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);
    return 0;
}