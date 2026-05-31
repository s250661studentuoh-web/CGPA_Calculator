/*
 * File:    report.h
 * Project: UOH CGPA Calculator
 * Author:  [Your Name]
 * Course:  Programming Fundamentals
 * Purpose: Declarations for all display/report functions
 */

#ifndef REPORT_H
#define REPORT_H

#include "structs.h"

/*
 * Displays the main program menu.
 */
void displayMainMenu();

/*
 * Displays the full UOH grading policy table.
 */
void displayGradingPolicy();

/*
 * Displays a formatted course report table for one semester.
 * sem: semester data with courses and computed SGPA
 */
void displaySemesterReport(const Semester& sem);

/*
 * Displays the final CGPA summary across all semesters.
 * semesters: all semester data
 * cgpa: computed cumulative GPA
 */
void displayFinalReport(const vector<Semester>& semesters, float cgpa);

/*
 * Displays a divider line of given width.
 */
void printLine(int width, char ch = '-');

#endif // REPORT_H
