[README.md](https://github.com/user-attachments/files/32286326/README.md)
# Student Information Management System
### Data Structures Assignment – C++17

---

## Project Structure

```
student_mgmt/
├── include/
│   ├── student.h       # Student data struct (POD)
│   ├── linked_list.h   # Singly-Linked List (data structure)
│   ├── file_io.h       # CSV read / write (persistence)
│   └── menu.h          # Console UI + all CRUD logic
├── src/
│   └── main.cpp        # Entry point (event loop)
├── Makefile
└── students.csv        # Auto-created on first run
```

---

## Build & Run

```bash
# Compile
make

# Run
./student_mgmt

# Or in one step
make run

# Clean binary + CSV
make clean
```

Manual build (no make):
```bash
g++ -std=c++17 -Iinclude -Wall -o student_mgmt src/main.cpp
```

---

## Features

| Feature | Details |
|---------|---------|
| Data structure | **Singly-Linked List** (custom implementation) |
| Persistence | **CSV file** (`students.csv`) with header row |
| CRUD | Create · Read (all / by ID / by name) · Update · Delete |
| Sorting | Bubble sort by GPA (descending) |
| ID management | Auto-increment (max existing ID + 1) |
| Input validation | Range checks for age, GPA; non-empty strings |

---

## Menu Options

```
1. Add Student      – prompts for all fields; ID is auto-assigned
2. View All         – formatted table of every record
3. Search           – by ID or by full name
4. Update           – select by ID, edit all fields
5. Delete           – select by ID, confirm before deleting
6. Sort by GPA      – in-place descending sort, saved to CSV
0. Exit
```

---

## Data Model

| Field  | Type   | Constraints       |
|--------|--------|-------------------|
| id     | int    | auto-increment, PK |
| name   | string | non-empty         |
| gender | string | non-empty         |
| age    | int    | 1 – 120           |
| gpa    | float  | 0.00 – 4.00       |
| major  | string | non-empty         |

---

## CSV Format

```
id,name,gender,age,gpa,major
1,Alice Johnson,Female,20,3.85,Computer Science
2,Bob Smith,Male,22,3.10,Mathematics
```
Fields containing commas are automatically quoted.  
The header row is skipped on load.
