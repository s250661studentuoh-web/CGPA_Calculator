# Implement User Interface / Input-Output

---

## Required Headers

```cpp
#include <iostream>
#include <iomanip>   // setw(), setprecision(), fixed, left, right
#include <string>
#include <vector>
using namespace std;
```

---

## `report.cpp` — Complete Implementation

```cpp
/*
 * File:    report.cpp
 * Project: UOH CGPA Calculator
 * Author:  [Your Name]
 * Purpose: All display / UI functions — menus, tables, summaries
 */

#include "report.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// ─── Constants for column widths — change once here if layout needs tweaking ─
const int COL_COURSE = 25;
const int COL_CH     =  4;
const int COL_MARKS  =  8;
const int COL_GRADE  =  7;
const int COL_GP     =  7;
const int COL_QP     =  8;
const int TABLE_W    = COL_COURSE + COL_CH + COL_MARKS + COL_GRADE + COL_GP + COL_QP; // 59

/*
 * Function: displayMainMenu
 * -------------------------
 * Prints the main application menu with a bordered box style.
 */
void displayMainMenu() {
    cout << "\n";
    cout << "  ╔══════════════════════════════════════╗\n";
    cout << "  ║     UOH CGPA CALCULATOR SYSTEM       ║\n";
    cout << "  ║   University of Haripur — C++ PF     ║\n";
    cout << "  ╠══════════════════════════════════════╣\n";
    cout << "  ║  1.  Calculate SGPA / CGPA           ║\n";
    cout << "  ║  2.  View Grading Policy             ║\n";
    cout << "  ║  3.  Exit                            ║\n";
    cout << "  ╚══════════════════════════════════════╝\n";
    cout << "  Enter choice: ";
}

/*
 * Function: displaySemesterReport
 * --------------------------------
 * Displays a formatted table for one semester:
 *   - Header row: Course | CH | Marks | Grade | GP | QP
 *   - One row per course (I/W rows show the grade in the Marks column)
 *   - Footer: SGPA
 *
 * sem : the Semester struct (const ref — display only, no modification)
 */
void displaySemesterReport(const Semester& sem) {
    cout << "\n";
    cout << "  ┌─ Semester " << sem.semesterNumber << " Report ";
    cout << string(TABLE_W - 16, '─') << "┐\n";

    // Column headers
    cout << "  │ "
         << left  << setw(COL_COURSE) << "Course"
         << right << setw(COL_CH)     << "CH"
                  << setw(COL_MARKS)  << "Marks"
                  << setw(COL_GRADE)  << "Grade"
                  << setw(COL_GP)     << "GP"
                  << setw(COL_QP)     << "QP"
         << " │\n";

    cout << "  ├" << string(TABLE_W + 2, '─') << "┤\n";

    // One row per course
    for (const auto& c : sem.courses) {
        cout << "  │ "
             << left << setw(COL_COURSE) << c.courseName.substr(0, COL_COURSE - 1);

        if (c.marks < 0) {
            // I or W — show grade in the marks column, dashes for GP and QP
            cout << right
                 << setw(COL_CH)    << c.creditHours
                 << setw(COL_MARKS) << c.grade          // "I" or "W"
                 << setw(COL_GRADE) << c.grade
                 << setw(COL_GP)    << "—"
                 << setw(COL_QP)    << "—";
        } else {
            cout << right
                 << setw(COL_CH)    << c.creditHours
                 << fixed << setprecision(2)
                 << setw(COL_MARKS) << c.marks
                 << setw(COL_GRADE) << c.grade
                 << setw(COL_GP)    << c.gradePoint
                 << setw(COL_QP)    << c.qualityPoints;
        }
        cout << " │\n";
    }

    cout << "  ├" << string(TABLE_W + 2, '─') << "┤\n";
    cout << "  │ "
         << left  << setw(TABLE_W - 6) << "  SGPA"
         << right << fixed << setprecision(2) << setw(6) << sem.sgpa
         << " │\n";
    cout << "  └" << string(TABLE_W + 2, '─') << "┘\n";
}

/*
 * Function: displayFinalReport
 * ----------------------------
 * Displays the cumulative CGPA summary:
 *   - One line per semester showing its SGPA
 *   - Cumulative CGPA
 *   - Academic standing label
 *
 * semesters : all semester data (const — display only)
 * cgpa      : the pre-calculated cumulative CGPA
 */
void displayFinalReport(const vector<Semester>& semesters, float cgpa) {
    cout << "\n";
    cout << "  ╔══════════════════════════════════════╗\n";
    cout << "  ║         FINAL CGPA SUMMARY           ║\n";
    cout << "  ╠══════════════════════════════════════╣\n";

    for (const auto& sem : semesters) {
        cout << "  ║  Semester " << sem.semesterNumber
             << "  →  SGPA: "
             << fixed << setprecision(2) << sem.sgpa;

        // Pad the rest of the box line
        string line = "  Semester " + to_string(sem.semesterNumber)
                    + "  →  SGPA: " + to_string(static_cast<int>(sem.sgpa * 100) / 100);
        // Simple fixed-width approach — always 38 chars inside box
        cout << string(max(0, 38 - (int)("Semester X  →  SGPA: X.XX"s.length())), ' ') << " ║\n";
    }

    cout << "  ╠══════════════════════════════════════╣\n";
    cout << "  ║  Cumulative CGPA : "
         << fixed << setprecision(2) << setw(5) << cgpa
         << "                ║\n";
    cout << "  ╠══════════════════════════════════════╣\n";

    // Academic standing
    string standing, symbol;
    if      (cgpa >= 3.50f) { standing = "Dean's List";        symbol = "★"; }
    else if (cgpa >= 3.00f) { standing = "Good Standing";      symbol = "✓"; }
    else if (cgpa >= 2.00f) { standing = "Satisfactory";       symbol = "!"; }
    else                    { standing = "Academic Warning";    symbol = "✗"; }

    cout << "  ║  Status : " << symbol << " " << left << setw(26) << standing << " ║\n";
    cout << "  ╚══════════════════════════════════════╝\n";
}

/*
 * Function: displayGradingPolicy
 * -------------------------------
 * Prints the full UOH grading policy table.
 */
void displayGradingPolicy() {
    cout << "\n";
    cout << "  ╔══════════════════════════════════════╗\n";
    cout << "  ║        UOH GRADING POLICY            ║\n";
    cout << "  ╠══════════════════════════════════════╣\n";
    cout << "  ║ " << left
         << setw(15) << "Marks Range"
         << setw(10) << "Grade"
         << setw(13) << "Grade Points"
         << "║\n";
    cout << "  ╠══════════════════════════════════════╣\n";

    // Lambda to print one policy row neatly
    auto row = [](const string& range, const string& grade, const string& gp) {
        cout << "  ║ " << left
             << setw(15) << range
             << setw(10) << grade
             << setw(13) << gp
             << "║\n";
    };

    row("90 – 100",   "A+", "4.00");
    row("85 – 89",    "A",  "4.00");
    row("80 – 84",    "A-", "3.67");
    row("75 – 79",    "B+", "3.33");
    row("71 – 74",    "B",  "3.00");
    row("68 – 70",    "B-", "2.67");
    row("64 – 67",    "C+", "2.33");
    row("61 – 63",    "C",  "2.00");
    row("58 – 60",    "C-", "1.67");
    row("54 – 57",    "D+", "1.33");
    row("50 – 53",    "D",  "1.00");
    row("Below 50",   "F",  "0.00");
    row("Incomplete", "I",  "Excluded");
    row("Withdrawn",  "W",  "Excluded");

    cout << "  ╚══════════════════════════════════════╝\n";
}
```

---

## Expected Output — Sample Run

```
  ╔══════════════════════════════════════╗
  ║     UOH CGPA CALCULATOR SYSTEM       ║
  ║   University of Haripur — C++ PF     ║
  ╠══════════════════════════════════════╣
  ║  1.  Calculate SGPA / CGPA           ║
  ║  2.  View Grading Policy             ║
  ║  3.  Exit                            ║
  ╚══════════════════════════════════════╝
  Enter choice: 1

Enter number of semesters (1-20): 1

========================================
  Entering data for Semester 1
========================================
  Enter number of courses in Semester 1 (1-15): 3

  Course 1:
    Name: Programming Fundamentals
    Credit Hours (1-4): 3
    Marks (0-100) or special grade (I/W): 87

  Course 2:
    Name: ICT Fundamentals
    Credit Hours (1-4): 2
    Marks (0-100) or special grade (I/W): 75

  Course 3:
    Name: English
    Credit Hours (1-4): 2
    Marks (0-100) or special grade (I/W): W

  ┌─ Semester 1 Report ───────────────────────────────────────────┐
  │ Course                     CH   Marks   Grade      GP      QP │
  ├───────────────────────────────────────────────────────────────┤
  │ Programming Fundamentals    3   87.00       A    4.00   12.00 │
  │ ICT Fundamentals            2   75.00      B+    3.33    6.67 │
  │ English                     2       W       W       —       — │
  ├───────────────────────────────────────────────────────────────┤
  │                                                  SGPA   3.73  │
  └───────────────────────────────────────────────────────────────┘

  ╔══════════════════════════════════════╗
  ║         FINAL CGPA SUMMARY           ║
  ╠══════════════════════════════════════╣
  ║  Semester 1  →  SGPA: 3.73          ║
  ╠══════════════════════════════════════╣
  ║  Cumulative CGPA :  3.73            ║
  ╠══════════════════════════════════════╣
  ║  Status : ★ Dean's List             ║
  ╚══════════════════════════════════════╝
```

---

## UI Design Principles Applied

| Principle | Tool / Technique |
|-----------|-----------------|
| Column alignment | `setw()` from `<iomanip>` — all widths defined as constants |
| Decimal precision | `fixed` + `setprecision(2)` — ensures `3.73` not `3.7333...` |
| Visual separators | Box-drawing characters `╔ ╠ ╚ ║ ─ ┌ ┤ └` for professional look |
| Long name truncation | `c.courseName.substr(0, COL_COURSE - 1)` prevents column overflow |
| I/W display | Marks column shows `"I"` or `"W"` text; GP/QP columns show `"—"` |
| Academic standing | Conditional message + symbol changes based on CGPA range |
| Constants for widths | All `setw()` values defined at the top — easy to adjust layout once |
