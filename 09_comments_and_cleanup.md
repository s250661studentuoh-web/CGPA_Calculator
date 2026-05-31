# Add Comments & Clean Up Code

---

## Why This Step Matters

Clean, well-commented code:
- Makes your intent clear to the evaluator — they don't need to run it to understand it
- Demonstrates professional coding habits beyond PF level
- Earns presentation marks even when the examiner just reads the code
- Makes future edits and debugging significantly faster

> "Code is read far more often than it is written."

---

## Comment Style Guide

### File Header (top of every `.cpp` and `.h` file)

```cpp
/*
 * File:    grading.cpp
 * Project: UOH CGPA Calculator
 * Author:  [Your Name]         ← replace with your actual name
 * RegNo:   [Registration No.]
 * Date:    [Submission Date]
 * Purpose: Grade conversion (marks → letter grade → grade points)
 *          and GPA calculation (SGPA per semester, cumulative CGPA)
 */
```

### Function Header (above every function)

```cpp
/*
 * Function: calculateSGPA
 * -----------------------
 * Calculates the Semester Grade Point Average (SGPA) for a list of courses.
 * Courses with grade "I" or "W" are excluded from both numerator and denominator.
 * Also sets each eligible course's qualityPoints field in-place.
 *
 * courses : vector<Course>& — modified in-place (qualityPoints populated)
 * returns : float SGPA value, or 0.0f if no eligible courses exist
 */
float calculateSGPA(vector<Course>& courses) { ... }
```

### Inline Comments (inside function body)

Use inline comments **only** for non-obvious logic. Don't comment what the code already says clearly.

```cpp
// ✅ Good — explains WHY, not just WHAT
// Skip I/W courses — they do not contribute to quality points or credit hours
if (c.grade == "I" || c.grade == "W") continue;

// ✅ Good — explains a non-obvious guard
// Guard against division by zero (occurs when all courses are I or W)
if (totalCH == 0) return 0.0f;

// ✅ Good — explains the formula in plain English
// SGPA = total quality points / total eligible credit hours
return totalQP / static_cast<float>(totalCH);

// ❌ Bad — restates what the code obviously does
int totalCH = 0;  // set totalCH to zero
```

---

## Naming Conventions

| Element | Convention | Example |
|---------|------------|---------| 
| Local variables | `camelCase` | `totalQP`, `creditHours`, `numSemesters` |
| Function names | `camelCase` | `calculateSGPA()`, `getGrade()`, `inputCourse()` |
| Struct names | `PascalCase` | `Course`, `Semester` |
| Constants | `UPPER_SNAKE_CASE` | `MAX_CREDIT_HOURS`, `COL_COURSE` |
| Parameters | `camelCase` | `semNum`, `courses`, `cgpa` |
| Loop counters | Short + descriptive | `s` (semester), `c` (course index), `i` (generic) |

---

## Named Constants — Avoid Magic Numbers

```cpp
// ❌ Bad — magic numbers scattered across the code
if (ch >= 1 && ch <= 4) ...
if (marks >= 0 && marks <= 100) ...
cout << string(59, '-') << "\n";

// ✅ Good — define once, use everywhere
const int MIN_CREDIT_HOURS = 1;
const int MAX_CREDIT_HOURS = 4;
const float MIN_MARKS      = 0.0f;
const float MAX_MARKS      = 100.0f;
const int TABLE_WIDTH      = 59;

if (ch >= MIN_CREDIT_HOURS && ch <= MAX_CREDIT_HOURS) ...
if (marks >= MIN_MARKS && marks <= MAX_MARKS) ...
cout << string(TABLE_WIDTH, '-') << "\n";
```

---

## Indentation & Formatting Rules

```cpp
// ✅ Good — 4-space indent, braces on same line, blank lines between sections
float calculateSGPA(vector<Course>& courses) {
    float totalQP = 0.0f;
    int   totalCH = 0;

    for (auto& c : courses) {
        if (c.grade == "I" || c.grade == "W") continue;

        c.qualityPoints = c.gradePoint * static_cast<float>(c.creditHours);
        totalQP += c.qualityPoints;
        totalCH += c.creditHours;
    }

    if (totalCH == 0) return 0.0f;
    return totalQP / static_cast<float>(totalCH);
}

// ❌ Bad — no spacing, cryptic names, no comments
float f(vector<Course>&v){float x=0;int y=0;
for(auto&c:v){if(c.grade=="I"||c.grade=="W")continue;
c.qualityPoints=c.gradePoint*c.creditHours;x+=c.qualityPoints;y+=c.creditHours;}
if(y==0)return 0;return x/y;}
```

---

## Code Cleanup Checklist

Before final submission, verify every item below is complete:

### Source Code Quality
- [ ] All debug `cout << "[DEBUG]..."` trace statements removed
- [ ] No unused variables (`-Wall` flag generates a warning for these)
- [ ] No unused `#include` statements
- [ ] All `#include` and `#pragma once` at the top of every file
- [ ] Consistent 4-space indentation throughout all files
- [ ] Braces on the same line as the statement (`{` at end of line, not on its own line)

### Comments
- [ ] File header (name, project, date, purpose) in **every** `.cpp` and `.h` file
- [ ] Function header comment above **every** function
- [ ] Inline comments on non-obvious logic lines
- [ ] No commented-out dead code left in the final submission

### Naming
- [ ] All variable names are descriptive (`totalQP` not `x`, `numSemesters` not `n`)
- [ ] All function names clearly state what they do (`inputCourse`, not `getData`)
- [ ] Struct names are PascalCase (`Course`, `Semester`)
- [ ] No magic numbers — all `setw()`, loop bounds, and range limits are named constants

### Functionality
- [ ] All three menu options work correctly
- [ ] Program does not crash on any invalid input
- [ ] SGPA and CGPA values match hand-calculated results from test cases
- [ ] I/W grades correctly excluded from GPA calculations
- [ ] No division-by-zero crash when all courses are I/W

---

## Fully Commented Example — `grading.cpp`

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
 * Converts numeric marks to a UOH letter grade.
 * All boundaries are inclusive (>=), matching UOH policy exactly.
 *
 * marks   : float in [0, 100]
 * returns : letter grade string (e.g. "A+", "B-", "F")
 */
string getGrade(float marks) {
    if      (marks >= 90) return "A+";
    else if (marks >= 85) return "A";   // Note: A+ and A both give 4.00 GP
    else if (marks >= 80) return "A-";
    else if (marks >= 75) return "B+";
    else if (marks >= 71) return "B";
    else if (marks >= 68) return "B-";
    else if (marks >= 64) return "C+";
    else if (marks >= 61) return "C";
    else if (marks >= 58) return "C-";
    else if (marks >= 54) return "D+";
    else if (marks >= 50) return "D";
    else                  return "F";   // marks < 50 → fail
}

/*
 * Function: getGradePoint
 * -----------------------
 * Returns the grade point value for given marks.
 * Boundary: marks >= 85 (not > 85) ensures marks=85 correctly returns 4.00.
 *
 * marks   : float in [0, 100]
 * returns : grade point (0.00 – 4.00)
 */
float getGradePoint(float marks) {
    if      (marks >= 85) return 4.00f;  // both A+ (90-100) and A (85-89) → 4.00
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
 * Computes SGPA for one semester. Excludes I/W courses from both
 * numerator (quality points) and denominator (credit hours).
 * Populates each eligible course's qualityPoints field as a side effect.
 *
 * courses : vector<Course>& — modified in-place (qualityPoints set)
 * returns : SGPA float, or 0.0 if all courses are I or W
 */
float calculateSGPA(vector<Course>& courses) {
    float totalQP = 0.0f;
    int   totalCH = 0;

    for (auto& c : courses) {
        // Skip I and W — they do not contribute to GPA
        if (c.grade == "I" || c.grade == "W") continue;

        // Compute and store quality points for this course
        c.qualityPoints = c.gradePoint * static_cast<float>(c.creditHours);

        // Accumulate totals for the SGPA formula
        totalQP += c.qualityPoints;
        totalCH += c.creditHours;
    }

    // Guard: if all courses were I/W, totalCH = 0 → avoid division by zero
    if (totalCH == 0) return 0.0f;

    // SGPA = Σ(Quality Points) / Σ(Credit Hours)
    return totalQP / static_cast<float>(totalCH);
}
```
