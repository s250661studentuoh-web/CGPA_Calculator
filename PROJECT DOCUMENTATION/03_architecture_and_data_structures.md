# Design Program Architecture & Data Structures

---

## System Architecture Overview

The program is divided into **five logical modules** plus one shared header, each with a single, clear responsibility.

```
┌─────────────────────────────────────────────────────────────────┐
│                          main.cpp                               │
│            (Entry point — orchestrates all modules)             │
└────────┬──────────────────────────────────────────┬────────────┘
         │                                          │
  ┌──────▼──────┐                           ┌──────▼──────┐
  │   Input     │                           │  Validation │
  │  Module     │                           │   Module    │
  │functions.cpp│                           │functions.cpp│
  └──────┬──────┘                           └──────┬──────┘
         │                                         │
         └────────────────┬────────────────────────┘
                          │
               ┌──────────▼──────────┐
               │    Grade & GPA      │
               │      Module         │
               │    grading.cpp      │
               └──────────┬──────────┘
                          │
               ┌──────────▼──────────┐
               │    Report Module    │
               │     report.cpp      │
               └─────────────────────┘

         ┌──────────────────────────┐
         │       structs.h          │  ← Shared by ALL modules
         │  Course + Semester types │
         └──────────────────────────┘
```

---

## Module Responsibilities

| Module | Files | Responsibility |
|--------|-------|----------------|
| **Input Module** | `functions.h` / `functions.cpp` | Reads semester count, course count, course name, credit hours, marks/grade |
| **Validation Module** | `functions.h` / `functions.cpp` | Enforces marks (0–100), credit hours (1–4), semester count (≥1), special grades |
| **Grade Module** | `grading.h` / `grading.cpp` | Converts marks → letter grade → grade points |
| **GPA Module** | `grading.h` / `grading.cpp` | Computes quality points, SGPA per semester, cumulative CGPA |
| **Report Module** | `report.h` / `report.cpp` | Displays main menu, semester table, final CGPA summary, grading policy |
| **Shared Types** | `structs.h` | Defines `Course` and `Semester` structs used by all modules |

---

## Data Structures

### `structs.h` — Shared definitions

```cpp
// structs.h
#pragma once
#include <string>
#include <vector>

/*
 * Course — holds all data for a single course in a single semester.
 */
struct Course {
    std::string courseName;    // e.g., "Programming Fundamentals"
    int         creditHours;   // 1 – 4
    float       marks;         // 0.0 – 100.0; -1.0 sentinel for I/W
    std::string grade;         // e.g., "A", "B+", "I", "W"
    float       gradePoint;    // e.g., 4.00, 3.33, 0.00
    float       qualityPoints; // gradePoint × creditHours; 0 for I/W
};

/*
 * Semester — groups all courses for one semester and stores its SGPA.
 */
struct Semester {
    int                  semesterNumber; // 1-indexed
    std::vector<Course>  courses;
    float                sgpa;           // calculated after all courses entered
};
```

> **Why `#pragma once`?** It prevents the header from being included twice in the same translation unit, which would cause a "struct redefinition" error. It is supported by all major C++ compilers (GCC, Clang, MSVC).

---

### Program-Level Data (in `main.cpp`)

```cpp
std::vector<Semester> allSemesters; // all semesters entered by the user
float                 cgpa = 0.0f; // final cumulative GPA, computed at the end
```

---

## Function Signatures (Declarations)

### `functions.h`

```cpp
#pragma once
#include "structs.h"

// Returns a validated number of semesters (1 – 20)
int  getSemesterCount();

// Returns a validated number of courses for semNum (1 – 15)
int  getCourseCount(int semNum);

// Reads and returns a fully populated Course struct
Course inputCourse(int courseNum);

// Returns true if marks are in [0, 100]
bool validateMarks(float marks);

// Returns true if credit hours are in [1, 4]
bool validateCreditHours(int ch);
```

### `grading.h`

```cpp
#pragma once
#include "structs.h"
#include <string>

// Converts numeric marks to UOH letter grade
std::string getGrade(float marks);

// Returns UOH grade point value for given numeric marks
float getGradePoint(float marks);

// Computes SGPA for one semester; modifies qualityPoints in-place
float calculateSGPA(std::vector<Course>& courses);

// Computes cumulative CGPA across all semesters
float calculateCGPA(std::vector<Semester>& semesters);
```

### `report.h`

```cpp
#pragma once
#include "structs.h"
#include <vector>

void displayMainMenu();
void displaySemesterReport(const Semester& sem);
void displayFinalReport(const std::vector<Semester>& semesters, float cgpa);
void displayGradingPolicy();
```

---

## Key Formulas

### Quality Points (per course)
```
Quality Points = Grade Points × Credit Hours

Example:
  Grade Points = 4.00  (for marks = 87 → Grade A)
  Credit Hours = 3
  Quality Points = 4.00 × 3 = 12.00
```

### SGPA (per semester)
```
SGPA = Σ(Quality Points) / Σ(Credit Hours)
       (I and W courses excluded from both numerator and denominator)

Example:
  Course A: GP=4.00, CH=3 → QP=12.00
  Course B: GP=3.33, CH=2 → QP= 6.67
  Course C: grade=W       → excluded
  SGPA = (12.00 + 6.67) / (3 + 2) = 18.67 / 5 = 3.73
```

### CGPA (cumulative)
```
CGPA = Σ(All Quality Points across all semesters) / Σ(All Credit Hours across all semesters)
       (I and W courses excluded from both numerator and denominator)

This is NOT an average of SGPAs — it uses the raw totals.
```

> **Common mistake:** Averaging the SGPAs (e.g., (3.73 + 3.50) / 2 = 3.615) gives a slightly different and **incorrect** result compared to the proper weighted formula above. Always use the raw QP and CH totals.

---

## Program Flowchart

```
START
  │
  ▼
Display Main Menu
  │
  ├──► [1] Calculate SGPA/CGPA
  │         │
  │         ▼
  │    getSemesterCount() — validated input
  │         │
  │         ▼
  │    ┌─── For each semester (1 to n) ─────────────────────────┐
  │    │   getCourseCount(semNum) — validated input             │
  │    │   ┌─── For each course (1 to m) ─────────────────────┐ │
  │    │   │   inputCourse() reads name, CH, marks or I/W     │ │
  │    │   │   validateMarks() / validateCreditHours()        │ │
  │    │   │   getGrade() + getGradePoint()                   │ │
  │    │   │   qualityPoints = gradePoint × creditHours       │ │
  │    │   └──────────────────────────────────────────────────┘ │
  │    │   calculateSGPA(semester.courses)                       │
  │    │   displaySemesterReport(semester)                       │
  │    └────────────────────────────────────────────────────────┘
  │         │
  │         ▼
  │    calculateCGPA(allSemesters)
  │    displayFinalReport(allSemesters, cgpa)
  │
  ├──► [2] View Grading Policy
  │         displayGradingPolicy()
  │
  └──► [3] Exit
  │
STOP
```
