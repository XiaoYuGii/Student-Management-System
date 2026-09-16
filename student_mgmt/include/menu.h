#ifndef MENU_H
#define MENU_H

#include "linked_list.h"
#include "file_io.h"
#include <iostream>
#include <limits>
#include <string>
#include <utility>


void printBanner();
void printMenu();
void printSearchMenu();

void addStudent   (LinkedList& list, const std::string& file);
void viewAll      (const LinkedList& list);
void searchMenu   (const LinkedList& list);
void updateStudent(LinkedList& list, const std::string& file);
void deleteStudent(LinkedList& list, const std::string& file);
void sortStudents (LinkedList& list, const std::string& file);


inline void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

inline int getInt(const std::string& prompt, int lo, int hi) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val && val >= lo && val <= hi) {
            clearInput();
            return val;
        }
        clearInput();
        std::cout << "  Invalid input. Enter a number between "
                  << lo << " and " << hi << ".\n";
    }
}

inline std::string getString(const std::string& prompt) {
    std::string val;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, val);
        if (!val.empty()) return val;
        std::cout << "  Input cannot be empty. Try again.\n";
    }
}

inline float getGPA(const std::string& prompt) {
    float val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val && val >= 0.0f && val <= 4.0f) {
            clearInput();
            return val;
        }
        clearInput();
        std::cout << "  GPA must be between 0.00 and 4.00. Try again.\n";
    }
}

inline Student promptStudent(int id) {
    clearInput();
    std::cout << "\n";
    std::string name   = getString("  Full Name    : ");
    std::string gender = getString("  Gender (Male/Female/Other): ");
    int   age          = getInt   ("  Age          : ", 1, 120);
    float gpa          = getGPA   ("  GPA (0.0-4.0): ");
    std::string major  = getString("  Major        : ");
    return Student(id, name, gender, age, gpa, major);
}


inline void printBanner() {
    std::cout << "\n";
    std::cout << "  ╔═══════════════════════════════════════════╗\n";
    std::cout << "  ║   Student Information Management System   ║\n";
    std::cout << "  ║          Data Structure – C++             ║\n";
    std::cout << "  ╚═══════════════════════════════════════════╝\n";
    std::cout << "\n";
}

inline void printMenu() {
    std::cout << "  ┌─────────────────────────────────┐\n";
    std::cout << "  │           MAIN  MENU            │\n";
    std::cout << "  ├─────────────────────────────────┤\n";
    std::cout << "  │  1. Add Student                 │\n";
    std::cout << "  │  2. View All Students           │\n";
    std::cout << "  │  3. Search Student              │\n";
    std::cout << "  │  4. Update Student              │\n";
    std::cout << "  │  5. Delete Student              │\n";
    std::cout << "  │  6. Sort Students (by GPA)      │\n";
    std::cout << "  │  0. Exit                        │\n";
    std::cout << "  └─────────────────────────────────┘\n";
    std::cout << "  Choice: ";
}

inline void printSearchMenu() {
    std::cout << "\n  Search by:\n";
    std::cout << "    1. Student ID\n";
    std::cout << "    2. Student Name\n";
    std::cout << "    0. Back\n";
    std::cout << "  Choice: ";
}

inline void addStudent(LinkedList& list, const std::string& file) {
    std::cout << "\n── Add New Student ──────────────────────────────\n";
    int id = list.nextAutoId();
    std::cout << "  Auto-assigned ID: " << id << "\n";

    Student s = promptStudent(id);
    list.insertBack(s);

    if (saveToCSV(list, file))
        std::cout << "\n  ✓ Student added and saved successfully.\n";
    else
        std::cout << "\n  ✗ Student added but file save failed.\n";
}

inline void viewAll(const LinkedList& list) {
    std::cout << "\n── All Students ─────────────────────────────────\n";
    list.display();
}

inline void searchMenu(const LinkedList& list) {
    std::cout << "\n── Search ───────────────────────────────────────";
    printSearchMenu();
    int choice;
    std::cin >> choice;
    clearInput();

    if (choice == 1) {
        int id = getInt("  Enter Student ID: ", 1, 999999);
        Node* node = list.search(id);
        if (!node) {
            std::cout << "  ✗ No student found with ID " << id << ".\n";
        } else {
            // Display just that record
            LinkedList tmp;
            tmp.insertBack(node->data);
            tmp.display();
        }
    } else if (choice == 2) {
        clearInput();
        std::string name = getString("  Enter Name: ");
        Node* node = list.searchByName(name);
        if (!node) {
            std::cout << "  ✗ No student found with name \"" << name << "\".\n";
        } else {
            LinkedList tmp;
            tmp.insertBack(node->data);
            tmp.display();
        }
    }
}

inline void updateStudent(LinkedList& list, const std::string& file) {
    std::cout << "\n── Update Student ───────────────────────────────\n";
    if (list.isEmpty()) { std::cout << "  No records to update.\n"; return; }

    int id = getInt("  Enter ID of student to update: ", 1, 999999);
    if (!list.idExists(id)) {
        std::cout << "  ✗ Student ID " << id << " not found.\n";
        return;
    }

    std::cout << "  Current record:\n";
    Node* cur = list.search(id);
    {
        LinkedList tmp;
        tmp.insertBack(cur->data);
        tmp.display();
    }

    std::cout << "  Enter new values:\n";
    Student updated = promptStudent(id);

    if (list.update(id, updated) && saveToCSV(list, file))
        std::cout << "\n  ✓ Student updated and saved.\n";
    else
        std::cout << "\n  ✗ Update failed.\n";
}

inline void deleteStudent(LinkedList& list, const std::string& file) {
    std::cout << "\n── Delete Student ───────────────────────────────\n";
    if (list.isEmpty()) { std::cout << "  No records to delete.\n"; return; }

    int id = getInt("  Enter ID of student to delete: ", 1, 999999);
    if (!list.idExists(id)) {
        std::cout << "  ✗ Student ID " << id << " not found.\n";
        return;
    }

    // Confirm
    std::cout << "  Are you sure? (y/n): ";
    char confirm;
    std::cin >> confirm;
    clearInput();
    if (confirm != 'y' && confirm != 'Y') {
        std::cout << "  Cancelled.\n";
        return;
    }

    if (list.remove(id) && saveToCSV(list, file))
        std::cout << "  ✓ Student deleted and file updated.\n";
    else
        std::cout << "  ✗ Delete failed.\n";
}

inline void sortStudents(LinkedList& list, const std::string& file) {
    std::cout << "\n── Sort by GPA (descending) ─────────────────────\n";
    if (list.size() < 2) {
        std::cout << "  Nothing to sort.\n";
        list.display();
        return;
    }

    bool swapped;
    do {
        swapped = false;
        Node* cur = list.head();
        while (cur && cur->next) {
            if (cur->data.gpa < cur->next->data.gpa) {
                std::swap(cur->data, cur->next->data);
                swapped = true;
            }
            cur = cur->next;
        }
    } while (swapped);

    saveToCSV(list, file);
    std::cout << "  ✓ Sorted by GPA (highest first):\n";
    list.display();
}

#endif
