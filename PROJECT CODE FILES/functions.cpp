/*
 * File:    functions.cpp
 * Project: UOH CGPA Calculator
 * Author:  [Your Name]
 * Course:  Programming Fundamentals
 * Purpose: Input and validation function implementations
 */

#include <iostream>
#include <string>
#include <limits>
#include "functions.h"
#include "grading.h"
using namespace std;

// -------------------------------------------------------
// Validation
// -------------------------------------------------------

bool validateMarks(float marks) {
    return (marks >= 0.0f && marks <= 100.0f);
}

bool validateCreditHours(int ch) {
    return (ch >= 1 && ch <= 4);
}

// -------------------------------------------------------
// Input Helpers
// -------------------------------------------------------

int getSemesterCount() {
    int n;
    while (true) {
        cout << "\n  Enter total number of semesters (1-10): ";
        if (cin >> n && n >= 1 && n <= 10) break;
        cout << "  [!] Invalid. Enter a number between 1 and 10.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return n;
}

int getCourseCount(int semNum) {
    int n;
    while (true) {
        cout << "  Courses in Semester " << semNum << " (1-10): ";
        if (cin >> n && n >= 1 && n <= 10) break;
        cout << "  [!] Invalid. Enter a number between 1 and 10.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return n;
}

// -------------------------------------------------------
// Semester Input
// -------------------------------------------------------

/*
 * Reads all course data for one semester.
 * Supports numeric marks OR special I/W grade input.
 */
Semester inputSemesterData(int semNum) {
    Semester sem;
    sem.semesterNumber = semNum;
    sem.sgpa           = 0.0f;

    int courseCount = getCourseCount(semNum);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush buffer

    cout << "\n";

    for (int i = 1; i <= courseCount; i++) {
        Course c;
        c.marks        = -1;
        c.gradePoint   = 0.0f;
        c.qualityPoints = 0.0f;

        // --- Course Name ---
        cout << "  Course " << i << " Name     : ";
        getline(cin, c.courseName);

        // --- Credit Hours ---
        while (true) {
            cout << "  Credit Hours (1-4): ";
            if (cin >> c.creditHours && validateCreditHours(c.creditHours)) break;
            cout << "  [!] Invalid. Credit hours must be 1 to 4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // --- Marks or Special Grade ---
        string input;
        while (true) {
            cout << "  Marks (0-100) or I/W : ";
            cin >> input;

            // Check for special grades I or W
            if (input == "I" || input == "i") {
                c.grade      = "I";
                c.gradePoint = 0.0f;
                break;
            } else if (input == "W" || input == "w") {
                c.grade      = "W";
                c.gradePoint = 0.0f;
                break;
            }

            // Try parsing as float
            try {
                float m = stof(input);
                if (validateMarks(m)) {
                    c.marks      = m;
                    c.grade      = getGrade(m);
                    c.gradePoint = getGradePoint(m);
                    break;
                } else {
                    cout << "  [!] Marks must be between 0 and 100.\n";
                }
            } catch (...) {
                cout << "  [!] Invalid input. Enter a number or I/W.\n";
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n";

        sem.courses.push_back(c);
    }

    return sem;
}
