#include <iostream>
using namespace std;

struct Student {
    int         id;
    string      name;
    string      gender;
    int         age;
    float       gpa;
    string      major;

    Student()
        : id(0), name(""), gender(""), age(0), gpa(0.0f), major("") {}

    Student(int id, const string& name, const string& gender,
            int age, float gpa, const string& major)
        : id(id), name(name), gender(gender),
          age(age), gpa(gpa), major(major) {}
};

void printBanner() {
    cout << "\n";
    cout << "  ╔═══════════════════════════════════════════╗\n";
    cout << "  ║   Student Information Management System   ║\n";
    cout << "  ║          Data Structure – C++             ║\n";
    cout << "  ╚═══════════════════════════════════════════╝\n";
    cout << "\n";
}

void printMenu() {
    cout << "  ┌─────────────────────────────────┐\n";
    cout << "  │           MAIN  MENU            │\n";
    cout << "  ├─────────────────────────────────┤\n";
    cout << "  │  1. Add Student                 │\n";
    cout << "  │  2. View All Students           │\n";
    cout << "  │  3. Search Student              │\n";
    cout << "  │  4. Update Student              │\n";
    cout << "  │  5. Delete Student              │\n";
    cout << "  │  6. Sort Students (by GPA)      │\n";
    cout << "  │  0. Exit                        │\n";
    cout << "  └─────────────────────────────────┘\n";
    cout << "  Choice: ";
}

void printSearchMenu() {
    cout << "\n  Search by:\n";
    cout << "    1. Student ID\n";
    cout << "    2. Student Name\n";
    cout << "    0. Back\n";
    cout << "  Choice: ";
}

int main() {
    printBanner();
    return 0;
}
