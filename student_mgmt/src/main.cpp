#include "menu.h"

#include <iostream>

static const std::string DATA_FILE = "students.csv";

int main() {
    LinkedList students;

    if (!loadFromCSV(students, DATA_FILE)) {
        std::cerr << "  [WARN] Could not load data file – starting fresh.\n";
    }

    printBanner();
    std::cout << "  Loaded " << students.size()
              << " record(s) from " << DATA_FILE << "\n\n";

    int choice = -1;
    while (choice != 0) {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: addStudent   (students, DATA_FILE); break;
            case 2: viewAll      (students);            break;
            case 3: searchMenu   (students);            break;
            case 4: updateStudent(students, DATA_FILE); break;
            case 5: deleteStudent(students, DATA_FILE); break;
            case 6: sortStudents (students, DATA_FILE); break;
            case 0:
                std::cout << "\n  Goodbye! Data saved to "
                          << DATA_FILE << "\n\n";
                break;
            default:
                clearInput();
                std::cout << "  Invalid option. Please choose 0-6.\n";
        }
    }

    return 0;
}
