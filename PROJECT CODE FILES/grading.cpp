/*
 * File:    grading.cpp
 * Project: UOH CGPA Calculator
 * Author:  [Your Name]
 * Course:  Programming Fundamentals
 * Purpose: Grade conversion and GPA calculation implementations
 */

#include "grading.h"
using namespace std;

// -------------------------------------------------------
// Grade Conversion — UOH Grading Policy
// -------------------------------------------------------

/*
 * Maps numeric marks to UOH letter grade.
 * Boundary values are inclusive (>=).
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
 * Maps numeric marks to grade point value per UOH policy.
 * Note: A+ and A both map to 4.00.
 */
float getGradePoint(float marks) {
    if      (marks >= 85) return 4.00f;
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

// -------------------------------------------------------
// GPA Calculations
// -------------------------------------------------------

/*
 * SGPA = Sum(GradePoint * CreditHours) / Sum(CreditHours)
 * Courses with I or W grade are excluded from both totals.
 */
float calculateSGPA(vector<Course>& courses) {
    float totalQP = 0.0f;
    int   totalCH = 0;

    for (auto& c : courses) {
        // Skip incomplete and withdrawn courses
        if (c.grade == "I" || c.grade == "W") continue;

        // Compute and store quality points
        c.qualityPoints = c.gradePoint * static_cast<float>(c.creditHours);

        totalQP += c.qualityPoints;
        totalCH += c.creditHours;
    }

    // Guard against division by zero (all courses I/W)
    if (totalCH == 0) return 0.0f;

    return totalQP / static_cast<float>(totalCH);
}

/*
 * CGPA = Sum of all QP across semesters / Sum of all CH across semesters
 * I/W courses excluded from both totals.
 */
float calculateCGPA(vector<Semester>& semesters) {
    float totalQP = 0.0f;
    int   totalCH = 0;

    for (auto& sem : semesters) {
        for (auto& c : sem.courses) {
            if (c.grade == "I" || c.grade == "W") continue;
            totalQP += c.qualityPoints;
            totalCH += c.creditHours;
        }
    }

    if (totalCH == 0) return 0.0f;

    return totalQP / static_cast<float>(totalCH);
}

/*
 * Returns academic standing string based on CGPA value.
 */
string getAcademicStanding(float cgpa) {
    if      (cgpa >= 3.5f) return "Dean's List          [*]";
    else if (cgpa >= 3.0f) return "Good Standing        [+]";
    else if (cgpa >= 2.0f) return "Satisfactory         [~]";
    else if (cgpa >= 1.0f) return "Academic Warning     [!]";
    else                   return "Academic Probation   [X]";
}
