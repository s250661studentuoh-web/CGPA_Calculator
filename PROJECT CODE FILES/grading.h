/*
 * File:    grading.h
 * Project: UOH CGPA Calculator
 * Author:  [Your Name]
 * Course:  Programming Fundamentals
 * Purpose: Declarations for grade conversion and GPA calculation
 */

#ifndef GRADING_H
#define GRADING_H

#include "structs.h"

// --- Grade Conversion ---

/*
 * Converts numeric marks to UOH letter grade.
 * marks: value between 0.0 and 100.0
 * returns: letter grade string e.g., "A+", "B+", "F"
 */
string getGrade(float marks);

/*
 * Returns the grade point value for given marks per UOH policy.
 * marks: value between 0.0 and 100.0
 * returns: grade point e.g., 4.00, 3.33, 0.00
 */
float getGradePoint(float marks);

// --- GPA Calculations ---

/*
 * Calculates SGPA for a semester.
 * Computes quality points for each course (GP x CH).
 * Excludes courses with I or W grades.
 * courses: reference to vector of Course structs (modified in-place)
 * returns: SGPA as float, or 0.0 if no eligible courses
 */
float calculateSGPA(vector<Course>& courses);

/*
 * Calculates cumulative CGPA across all semesters.
 * Excludes all I/W graded courses from computation.
 * semesters: all semester data
 * returns: CGPA as float
 */
float calculateCGPA(vector<Semester>& semesters);

/*
 * Returns academic standing label based on CGPA.
 * e.g., "Dean's List", "Good Standing", "Academic Warning"
 */
string getAcademicStanding(float cgpa);

#endif // GRADING_H
