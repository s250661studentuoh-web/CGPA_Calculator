# Implement Core Functionality

---

## Overview

Core functionality is split across three file pairs: `functions`, `grading`, and `report`. Every function has a single, clearly defined job. Together they implement the complete pipeline:

```
User Input → Validation → Grade Mapping → GPA Calculation → Report Display
```

---

## `functions.cpp` — Input & Validation

```cpp
/*
 * File:    functions.cpp
 * Project: UOH CGPA Calculator
 * Author:  [Your Name]
 * Purpose: User input and input validation functions
 */

#include "functions.h"
#include <iostream>
#include <string>
#include <stdexcept>   // std::invalid_argument, std::out_of_range
using namespace std;

/*
 * Function: getSemesterCount
 * --------------------------
 * Prompts the user for the number of semesters they want to enter.
 * Re-prompts until a valid integer in [1, 20] is given.
 *
 * returns: validated semester count
 */
int getSemesterCount() {
    int n;
    do {
        cout << "\nEnter number of semesters (1-20): ";
        cin  >> n;

        if (cin.fail() || n < 1 || n > 20) {
            cin.clear();                        // clear error flags
            cin.ignore(1000, '\n');             // discard bad input
            cout << "  [!] Invalid input. Please enter a number between 1 and 20.\n";
            n = -1;                             // force loop to continue
        }
    } while (n < 1 || n > 20);

    return n;
}

/*
 * Function: getCourseCount
 * ------------------------
 * Prompts for the number of courses in a given semester.
 * Re-prompts until a valid integer in [1, 15] is given.
 *
 * semNum  : the semester number (used only in the prompt message)
 * returns : validated course count
 */
int getCourseCount(int semNum) {
    int n;
    do {
        cout << "  Enter number of courses in Semester " << semNum << " (1-15): ";
        cin  >> n;

        if (cin.fail() || n < 1 || n > 15) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Invalid input. Please enter a number between 1 and 15.\n";
            n = -1;
        }
    } while (n < 1 || n > 15);

    return n;
}

/*
 * Function: inputCourse
 * ---------------------
 * Reads a complete Course from the user: name, credit hours, and either
 * numeric marks (0–100) or a special grade ("I" or "W").
 *
 * courseNum : display index for the prompt (1-based)
 * returns   : fully populated Course struct
 */
Course inputCourse(int courseNum) {
    Course c;

    // --- Course name ---
    cout << "\n  Course " << courseNum << ":\n";
    cin.ignore(1000, '\n');                 // clear leftover newline from previous cin >>
    cout << "    Name: ";
    getline(cin, c.courseName);
    while (c.courseName.empty()) {
        cout << "    [!] Name cannot be empty. Enter course name: ";
        getline(cin, c.courseName);
    }

    // --- Credit hours ---
    do {
        cout << "    Credit Hours (1-4): ";
        cin  >> c.creditHours;

        if (cin.fail() || !validateCreditHours(c.creditHours)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "    [!] Invalid. Credit hours must be 1, 2, 3, or 4.\n";
            c.creditHours = -1;
        }
    } while (!validateCreditHours(c.creditHours));

    // --- Marks or special grade ---
    string input;
    bool   validInput = false;

    do {
        cout << "    Marks (0-100) or special grade (I/W): ";
        cin  >> input;

        if (input == "I" || input == "W" || input == "i" || input == "w") {
            // Normalize to uppercase
            c.grade         = (input == "i") ? "I" : (input == "w") ? "W" : input;
            c.marks         = -1.0f;    // sentinel — indicates no numeric marks
            c.gradePoint    = 0.0f;
            c.qualityPoints = 0.0f;
            validInput      = true;

        } else {
            // Attempt numeric conversion
            try {
                float marks = stof(input);
                if (!validateMarks(marks)) {
                    cout << "    [!] Marks must be between 0 and 100.\n";
                } else {
                    c.marks         = marks;
                    c.grade         = getGrade(marks);         // from grading.cpp
                    c.gradePoint    = getGradePoint(marks);    // from grading.cpp
                    c.qualityPoints = 0.0f;                    // computed in calculateSGPA
                    validInput      = true;
                }
            } catch (const invalid_argument&) {
                cout << "    [!] Invalid input. Enter a number (e.g. 75.5) or I/W.\n";
            } catch (const out_of_range&) {
                cout << "    [!] Number out of range. Enter a value between 0 and 100.\n";
            }
        }
    } while (!validInput);

    return c;
}

/*
 * Function: validateMarks
 * -----------------------
 * Returns true if marks are in the valid range [0, 100].
 */
bool validateMarks(float marks) {
    return (marks >= 0.0f && marks <= 100.0f);
}

/*
 * Function: validateCreditHours
 * ------------------------------
 * Returns true if credit hours are in the valid range [1, 4].
 */
bool validateCreditHours(int ch) {
    return (ch >= 1 && ch <= 4);
}
```

---

## `grading.cpp` — Grade Mapping & GPA Calculation

```cpp
/*
 * File:    grading.cpp
 * Project: UOH CGPA Calculator
 * Author:  [Your Name]
 * Purpose: Grade conversion and GPA calculation functions
 */

#include "grading.h"
using namespace std;

/*
 * Function: getGrade
 * ------------------
 * Converts numeric marks to a UOH letter grade string.
 * I/W grades are NOT handled here — they are set directly in inputCourse().
 *
 * marks   : float in [0, 100]
 * returns : letter grade string, e.g. "A+", "B-", "F"
 */
string getGrade(float marks) {
    if      (marks >= 90) return "A+";
    else if (marks >= 85) return "A";
    else if (marks >= 80) return "A-";
    else if (marks >= 75) return "B+";
    else if (marks >= 71) return "B";
    else if (marks >= 68) return "B-";
    else if (marks >= 64) return "C+";
    else if (marks >= 61) return "C";
    else if (marks >= 58) return "C-";
    else if (marks >= 54) return "D+";
    else if (marks >= 50) return "D";
    else                  return "F";
}

/*
 * Function: getGradePoint
 * -----------------------
 * Returns the UOH grade point value for given numeric marks.
 * Note: both A+ (90–100) and A (85–89) return 4.00 per UOH policy.
 *
 * marks   : float in [0, 100]
 * returns : grade point value (0.00 – 4.00)
 */
float getGradePoint(float marks) {
    if      (marks >= 85) return 4.00f;   // A+ and A both → 4.00
    else if (marks >= 80) return 3.67f;
    else if (marks >= 75) return 3.33f;
    else if (marks >= 71) return 3.00f;
    else if (marks >= 68) return 2.67f;
    else if (marks >= 64) return 2.33f;
    else if (marks >= 61) return 2.00f;
    else if (marks >= 58) return 1.67f;
    else if (marks >= 54) return 1.33f;
    else if (marks >= 50) return 1.00f;
    else                  return 0.00f;
}

/*
 * Function: calculateSGPA
 * -----------------------
 * Calculates the Semester Grade Point Average (SGPA) for a list of courses.
 * Courses with grade "I" or "W" are excluded from both numerator and denominator.
 * Also sets each eligible course's qualityPoints field in-place.
 *
 * courses : vector<Course>& — semester's course list (modified: qualityPoints set)
 * returns : SGPA as float, or 0.0 if no eligible courses
 */
float calculateSGPA(vector<Course>& courses) {
    float totalQP = 0.0f;
    int   totalCH = 0;

    for (auto& c : courses) {
        // Skip I and W grades — they do not contribute to GPA
        if (c.grade == "I" || c.grade == "W") continue;

        // Compute and store quality points for this course
        c.qualityPoints = c.gradePoint * static_cast<float>(c.creditHours);

        // Accumulate totals
        totalQP += c.qualityPoints;
        totalCH += c.creditHours;
    }

    // Guard against division by zero (all courses are I or W)
    if (totalCH == 0) return 0.0f;

    return totalQP / static_cast<float>(totalCH);
}

/*
 * Function: calculateCGPA
 * -----------------------
 * Calculates the cumulative CGPA across all semesters by summing ALL quality
 * points and ALL credit hours (excluding I/W courses).
 *
 * This is the correct approach — NOT an average of SGPA values.
 *
 * semesters : vector<Semester>& — all semester data
 * returns   : cumulative CGPA as float
 */
float calculateCGPA(vector<Semester>& semesters) {
    float totalQP = 0.0f;
    int   totalCH = 0;

    for (const auto& sem : semesters) {
        for (const auto& c : sem.courses) {
            if (c.grade == "I" || c.grade == "W") continue;
            totalQP += c.qualityPoints;
            totalCH += c.creditHours;
        }
    }

    if (totalCH == 0) return 0.0f;

    return totalQP / static_cast<float>(totalCH);
}
```

---

## `main.cpp` — Entry Point & Calculator Orchestration

```cpp
/*
 * File:    main.cpp
 * Project: UOH CGPA Calculator
 * Author:  [Your Name]
 * Purpose: Entry point — orchestrates the full SGPA/CGPA calculation flow
 */

#include <iostream>
#include <vector>
#include "structs.h"
#include "functions.h"
#include "grading.h"
#include "report.h"
using namespace std;

/*
 * Function: runCalculator
 * -----------------------
 * Drives the full multi-semester input, SGPA calculation, and CGPA flow.
 * Called when the user selects option 1 from the main menu.
 */
void runCalculator() {
    vector<Semester> allSemesters;

    int numSemesters = getSemesterCount();

    for (int s = 1; s <= numSemesters; s++) {
        Semester sem;
        sem.semesterNumber = s;

        cout << "\n========================================\n";
        cout << "  Entering data for Semester " << s << "\n";
        cout << "========================================\n";

        int numCourses = getCourseCount(s);

        for (int c = 1; c <= numCourses; c++) {
            Course course = inputCourse(c);
            sem.courses.push_back(course);
        }

        // Calculate SGPA for this semester (also sets qualityPoints in each course)
        sem.sgpa = calculateSGPA(sem.courses);

        // Display the semester report immediately
        displaySemesterReport(sem);

        allSemesters.push_back(sem);
    }

    // Calculate and display the final CGPA summary
    float cgpa = calculateCGPA(allSemesters);
    displayFinalReport(allSemesters, cgpa);
}

int main() {
    int choice = 0;

    do {
        displayMainMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Invalid input. Please enter 1, 2, or 3.\n";
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                runCalculator();
                break;
            case 2:
                displayGradingPolicy();
                break;
            case 3:
                cout << "\n  Goodbye! Good luck with your studies.\n\n";
                break;
            default:
                cout << "  [!] Invalid choice. Please enter 1, 2, or 3.\n";
        }
    } while (choice != 3);

    return 0;
}
```

---

## Special Grade Handling — Summary

| Scenario | What Happens |
|----------|-------------|
| User enters `I` or `W` | `marks = -1` (sentinel), `gradePoint = 0`, `qualityPoints = 0`, grade set to "I" or "W" |
| SGPA loop encounters I/W | `continue` skips the course — not added to QP or CH totals |
| ALL courses in a semester are I/W | `totalCH == 0`, returns `0.0` — no crash |
| CGPA loop encounters I/W | Same `continue` skip — correctly excluded from cumulative totals |
| Display of I/W course | Marks column shows "I" or "W" (not a number) |

---

## Input Handling — Why `string` + `stof()` Instead of `float`?

Using `cin >> float` directly fails silently when the user types text:
```cpp
// ❌ Problem: if user types "abc", cin enters fail state and marks = 0 silently
float marks;
cin >> marks;
```

The correct approach reads a string first, then tries to convert:
```cpp
// ✅ Correct: handles text, I/W, and numbers uniformly
string input;
cin >> input;
try {
    float marks = stof(input);
    // process marks...
} catch (const invalid_argument&) {
    // input was not a number at all
} catch (const out_of_range&) {
    // number too large or too small
}
```
