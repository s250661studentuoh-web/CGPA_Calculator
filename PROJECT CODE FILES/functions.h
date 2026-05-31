/*
 * File:    functions.h
 * Project: UOH CGPA Calculator
 * Author:  [Your Name]
 * Course:  Programming Fundamentals
 * Purpose: Declarations for input and validation functions
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

// --- Input Functions ---

/*
 * Prompts user and returns a validated semester count (1-10)
 */
int getSemesterCount();

/*
 * Prompts user and returns a validated course count (1-10)
 * semNum: semester number shown in the prompt
 */
int getCourseCount(int semNum);

/*
 * Reads all course data for a given semester from the user.
 * Handles I/W special grade input and validates marks/credit hours.
 * semNum: semester number shown in prompts
 * returns: fully populated Semester struct
 */
Semester inputSemesterData(int semNum);

// --- Validation Functions ---

/*
 * Returns true if marks are within valid range (0.0 to 100.0)
 */
bool validateMarks(float marks);

/*
 * Returns true if credit hours are within valid range (1 to 4)
 */
bool validateCreditHours(int ch);

#endif // FUNCTIONS_H
