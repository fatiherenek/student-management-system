#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    int id;
    string name;
    float grade1;
    float grade2;
    float grade3;
};

vector<Student> students;

// File 
void loadFromFile() {
    ifstream file("data/students.txt");
    if (!file.is_open()) return;

    Student s;
    string line;

    while (getline(file, line)) {
        s.id = stoi(line);
        getline(file, s.name);

        getline(file, line);
        s.grade1 = stof(line);
        getline(file, line);
        s.grade2 = stof(line);
        getline(file, line);
        s.grade3 = stof(line);

        students.push_back(s);
    }
    file.close();
}

void saveToFile() {
    ofstream file("data/students.txt");
    for (const auto& s : students) {
        file << s.id << endl;
        file << s.name << endl;
        file << s.grade1 << endl;
        file << s.grade2 << endl;
        file << s.grade3 << endl;
    }
    file.close();
}

// Helpers
float average(const Student& s) {
    return (s.grade1 + s.grade2 + s.grade3) / 3;
}

// CRUD 
void addStudent() {
    Student s;
    string input;

    cout << "Student ID: ";
    getline(cin, input);
    s.id = stoi(input);

    cout << "Student Name: ";
    getline(cin, s.name);

    cout << "Grade 1: ";
    getline(cin, input);
    s.grade1 = stof(input);

    cout << "Grade 2: ";
    getline(cin, input);
    s.grade2 = stof(input);

    cout << "Grade 3: ";
    getline(cin, input);
    s.grade3 = stof(input);

    students.push_back(s);
    saveToFile();

    cout << "Student added successfully!\n";
}

void listStudents() {
    if (students.empty()) {
        cout << "No students found.\n";
        return;
    }

    cout << "\n--- Student List ---\n";
    for (const auto& s : students) {
        cout << "ID: " << s.id
             << " | Name: " << s.name
             << " | Average: " << average(s) << endl;
    }
}

void searchStudent() {
    string input;
    cout << "Enter ID to search: ";
    getline(cin, input);
    int id = stoi(input);

    for (const auto& s : students) {
        if (s.id == id) {
            cout << "Found -> " << s.name
                 << " | Average: " << average(s) << endl;
            return;
        }
    }
    cout << "Student not found!\n";
}

void deleteStudent() {
    string input;
    cout << "Enter ID to delete: ";
    getline(cin, input);
    int id = stoi(input);

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            students.erase(it);
            saveToFile();
            cout << "Student deleted successfully!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

// Main 
int main() {
    loadFromFile();

    string input;
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. List Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        getline(cin, input);
        choice = stoi(input);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: listStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}

