/*
 * ============================================================
 *  Project : UOH CGPA Calculator System
 *  Course  : Programming Fundamentals
 *  Author  : [Your Name]
 *  Roll No : [Your Roll No]
 *  Uni     : University of Haripur
 *  Date    : [Submission Date]
 * ============================================================
 *
 *  Description:
 *  A console-based CGPA calculator that automates SGPA and CGPA
 *  computation for University of Haripur students using the
 *  official UOH grading policy. Supports multiple semesters,
 *  multiple courses, input validation, and I/W grade handling.
 *
 *  Modules:
 *    main.cpp       — Entry point and menu controller
 *    functions.cpp  — Input and validation
 *    grading.cpp    — Grade conversion and GPA calculations
 *    report.cpp     — Formatted console output
 *    structs.h      — Shared Course and Semester data structures
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <limits>
#include "structs.h"
#include "functions.h"
#include "grading.h"
#include "report.h"
using namespace std;

// -------------------------------------------------------
// Calculator Workflow
// -------------------------------------------------------

/*
 * Runs the full SGPA/CGPA calculation flow:
 * 1. Get semester count
 * 2. Input each semester's courses
 * 3. Calculate and display SGPA per semester
 * 4. Calculate and display final CGPA
 */
void runCalculator() {
    vector<Semester> allSemesters;

    int semCount = getSemesterCount();

    for (int i = 1; i <= semCount; i++) {
        cout << "\n";
        cout << "  ---- Entering Data for Semester " << i << " ----\n";

        // Get course data from user
        Semester sem = inputSemesterData(i);

        // Calculate SGPA for this semester
        sem.sgpa = calculateSGPA(sem.courses);

        // Display semester report immediately
        displaySemesterReport(sem);

        allSemesters.push_back(sem);
    }

    // Calculate cumulative CGPA across all semesters
    float cgpa = calculateCGPA(allSemesters);

    // Display final summary
    displayFinalReport(allSemesters, cgpa);
}

// -------------------------------------------------------
// Main Entry Point
// -------------------------------------------------------

int main() {
    int choice;

    do {
        displayMainMenu();

        // Read and validate menu choice
        while (!(cin >> choice)) {
            cout << "  [!] Invalid input. Enter 1, 2, or 3.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Enter choice: ";
        }

        cout << "\n";

        switch (choice) {
            case 1:
                runCalculator();
                break;

            case 2:
                displayGradingPolicy();
                break;

            case 3:
                cout << "  Goodbye. Good luck with your studies!\n\n";
                break;

            default:
                cout << "  [!] Invalid choice. Please enter 1, 2, or 3.\n";
                break;
        }

    } while (choice != 3);

    return 0;
}
