/*
 * File:    structs.h
 * Project: UOH CGPA Calculator
 * Author:  [Your Name]
 * Course:  Programming Fundamentals
 * Purpose: Shared data structures used across all modules
 */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>
using namespace std;

// Holds all data for a single course in a semester
struct Course {
    string courseName;      // e.g., "Programming Fundamentals"
    int    creditHours;     // Valid range: 1 to 4
    float  marks;           // Numeric marks 0-100, or -1 for I/W
    string grade;           // Letter grade e.g., "A+", "B", "I", "W"
    float  gradePoint;      // Grade point value e.g., 4.00, 3.33
    float  qualityPoints;   // gradePoint * creditHours
};

// Groups all courses in one semester with computed SGPA
struct Semester {
    int            semesterNumber;
    vector<Course> courses;
    float          sgpa;
};

#endif // STRUCTS_H
