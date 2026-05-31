/*
 * File:    report.cpp
 * Project: UOH CGPA Calculator
 * Author:  [Your Name]
 * Course:  Programming Fundamentals
 * Purpose: All display and formatted console output implementations
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "report.h"
#include "grading.h"
using namespace std;

// -------------------------------------------------------
// Utility
// -------------------------------------------------------

void printLine(int width, char ch) {
    cout << "  " << string(width, ch) << "\n";
}

// -------------------------------------------------------
// Main Menu
// -------------------------------------------------------

void displayMainMenu() {
    cout << "\n";
    printLine(50, '=');
    cout << "  " << setw(40) << left << "   UNIVERSITY OF HARIPUR" << "\n";
    cout << "  " << setw(40) << left << "   CGPA CALCULATOR SYSTEM" << "\n";
    cout << "  " << setw(40) << left << "   Programming Fundamentals Project" << "\n";
    printLine(50, '=');
    cout << "\n";
    cout << "    [1]  Calculate SGPA / CGPA\n";
    cout << "    [2]  View Grading Policy\n";
    cout << "    [3]  Exit\n";
    cout << "\n";
    printLine(50, '-');
    cout << "  Enter choice: ";
}

// -------------------------------------------------------
// Grading Policy Table
// -------------------------------------------------------

void displayGradingPolicy() {
    cout << "\n";
    printLine(50, '=');
    cout << "       UNIVERSITY OF HARIPUR — GRADING POLICY\n";
    printLine(50, '=');
    cout << "\n";
    cout << "  " << left
         << setw(18) << "Marks Range"
         << setw(10) << "Grade"
         << setw(14) << "Grade Points"
         << "\n";
    printLine(42, '-');

    // Grade rows
    auto row = [](const string& range, const string& grade, const string& gp) {
        cout << "  " << left
             << setw(18) << range
             << setw(10) << grade
             << setw(14) << gp
             << "\n";
    };

    row("90 – 100",   "A+",  "4.00");
    row("85 – 89",    "A",   "4.00");
    row("80 – 84",    "A-",  "3.67");
    row("75 – 79",    "B+",  "3.33");
    row("71 – 74",    "B",   "3.00");
    row("68 – 70",    "B-",  "2.67");
    row("64 – 67",    "C+",  "2.33");
    row("61 – 63",    "C",   "2.00");
    row("58 – 60",    "C-",  "1.67");
    row("54 – 57",    "D+",  "1.33");
    row("50 – 53",    "D",   "1.00");
    row("Below 50",   "F",   "0.00");
    printLine(42, '-');
    row("Incomplete", "I",   "Excluded");
    row("Withdrawn",  "W",   "Excluded");
    printLine(42, '=');
    cout << "\n";
}

// -------------------------------------------------------
// Semester Report
// -------------------------------------------------------

void displaySemesterReport(const Semester& sem) {
    cout << "\n";
    printLine(65, '=');
    cout << "   SEMESTER " << sem.semesterNumber << " REPORT\n";
    printLine(65, '=');
    cout << "\n";

    // Table header
    cout << "  " << left
         << setw(22) << "Course"
         << setw(5)  << "CH"
         << setw(9)  << "Marks"
         << setw(7)  << "Grade"
         << setw(7)  << "GP"
         << setw(8)  << "QP"
         << "\n";
    printLine(58, '-');

    for (const auto& c : sem.courses) {
        cout << "  " << left << setw(22) << c.courseName.substr(0, 20);
        cout << setw(5) << c.creditHours;

        // Marks column — show grade label for I/W
        if (c.grade == "I" || c.grade == "W") {
            cout << setw(9) << "--";
        } else {
            cout << fixed << setprecision(2) << setw(9) << c.marks;
        }

        cout << setw(7) << c.grade;

        if (c.grade == "I" || c.grade == "W") {
            cout << setw(7) << "--" << setw(8) << "--";
        } else {
            cout << fixed << setprecision(2)
                 << setw(7) << c.gradePoint
                 << setw(8) << c.qualityPoints;
        }
        cout << "\n";
    }

    printLine(58, '-');
    cout << "  SGPA : " << fixed << setprecision(2) << sem.sgpa << "\n";
    printLine(58, '=');
    cout << "\n";
}

// -------------------------------------------------------
// Final CGPA Summary
// -------------------------------------------------------

void displayFinalReport(const vector<Semester>& semesters, float cgpa) {
    cout << "\n";
    printLine(50, '=');
    cout << "        FINAL CGPA SUMMARY\n";
    printLine(50, '=');
    cout << "\n";

    // Per-semester SGPA summary
    cout << "  " << left << setw(20) << "Semester"
         << setw(10) << "SGPA"
         << "\n";
    printLine(30, '-');

    for (const auto& sem : semesters) {
        string label = "Semester " + to_string(sem.semesterNumber);
        cout << "  " << left << setw(20) << label
             << fixed << setprecision(2) << setw(10) << sem.sgpa
             << "\n";
    }

    printLine(30, '-');
    cout << "\n";
    cout << "  Cumulative CGPA  :  " << fixed << setprecision(2) << cgpa << " / 4.00\n";
    cout << "  Academic Status  :  " << getAcademicStanding(cgpa) << "\n";
    cout << "\n";
    printLine(50, '=');
    cout << "\n";
}
