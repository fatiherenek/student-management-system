#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Student {
    int id;
    string name;
    float grade1;
    float grade2;
    float grade3;
};

vector<Student> students;

void loadFromFile() {
    ifstream file("data/students.txt");
    if (!file.is_open()) return;

    Student s;
    while (file >> s.id) {
        file.ignore();
        getline(file, s.name);
        file >> s.grade1 >> s.grade2 >> s.grade3;
        students.push_back(s);
    }
    file.close();
}

void saveToFile() {
    ofstream file("data/students.txt");
    for (const auto& s : students) {
        file << s.id << endl;
        file << s.name << endl;
        file << s.grade1 << " " << s.grade2 << " " << s.grade3 << endl;
    }
    file.close();
}

void addStudent() {
    Student s;
    cout << "Student ID: ";
    cin >> s.id;

    cout << "Student Name: ";
    cin.ignore();
    getline(cin, s.name);

    cout << "Grade 1: ";
    cin >> s.grade1;
    cout << "Grade 2: ";
    cin >> s.grade2;
    cout << "Grade 3: ";
    cin >> s.grade3;

    students.push_back(s);
    saveToFile();

    cout << "Student added and saved successfully!\n";
}

void listStudents() {
    cout << "\n--- Student List ---\n";
    for (const auto& s : students) {
        float avg = (s.grade1 + s.grade2 + s.grade3) / 3;
        cout << "ID: " << s.id
             << " | Name: " << s.name
             << " | Average: " << avg << endl;
    }
}

int main() {
    loadFromFile();

    int choice;
    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. List Students\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                listStudents();
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}
