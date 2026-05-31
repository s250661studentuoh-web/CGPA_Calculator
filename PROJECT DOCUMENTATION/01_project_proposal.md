# Project Proposal — UOH CGPA Calculator

---

## Problem Statement

Students at the University of Haripur (UOH) often struggle to manually calculate their SGPA and CGPA accurately across multiple semesters. Manual calculation is time-consuming, error-prone, and does not account for special grade types such as Incomplete (I) or Withdrawn (W). There is no accessible, lightweight tool tailored to UOH's exact grading policy.

---

## Objectives

- Develop a console-based CGPA Calculator in C++ targeting UOH's official grading scale
- Automate SGPA and CGPA computation with zero rounding errors
- Support any number of semesters and any number of courses per semester
- Handle special grade inputs (`I` / `W`) gracefully by excluding them from calculations
- Display clean, aligned academic reports using `<iomanip>` formatting
- Validate all inputs and prevent crashes from invalid or unexpected data

---

## Scope

**In Scope:**
- Input of course names, credit hours, and marks (or I/W)
- Grade conversion using UOH grading scale
- Quality-points computation per course
- SGPA calculation per semester
- Cumulative CGPA calculation across all semesters
- Input validation and error-handling loops
- Formatted console output (tables, separators, academic standing)

**Out of Scope (Base Version):**
- Graphical User Interface (GUI)
- Database or persistent file storage
- Network, web, or API integration
- Multi-user or login system

---

## Methodology

| Phase | Steps |
|-------|-------|
| **1 · Planning** | Define scope, requirements, user stories, constraints |
| **2 · Design** | Design module architecture, data structures (`Course`, `Semester`), flowcharts |
| **3 · Implementation** | Code input, validation, grade mapping, GPA computation, UI display |
| **4 · Testing** | Run 19+ manual test cases — boundary values, edge cases, I/W handling |
| **5 · Debugging** | Log bugs, identify root causes, apply fixes |
| **6 · Cleanup** | Add comments, enforce naming conventions, remove debug traces |
| **7 · Documentation** | Write project report, fill test log, prepare README |
| **8 · Submission** | Organize package, run final checklist, prepare demo |

---

## Project Timeline

| Week | Milestone |
|------|-----------|
| Week 1 | Proposal approved; scope and requirements documented |
| Week 2 | Architecture designed; data structures finalized; header files created |
| Week 3 | Core functions implemented (`grading.cpp`, `functions.cpp`) |
| Week 4 | UI and report module implemented (`report.cpp`, `main.cpp`) |
| Week 5 | All 19 test cases run; 7 bugs logged and fixed |
| Week 6 | Code cleaned, commented, and documented; final report written |
| Week 7 | Submission package assembled; demo rehearsed |

---

## Risk Analysis

| Risk | Likelihood | Impact | Mitigation |
|------|------------|--------|------------|
| Division by zero (all I/W courses) | Medium | High (crash) | Guard `if (totalCH == 0) return 0.0;` |
| Invalid text input crashes `cin` | High | High | Use `string` input + `stof()` with `try-catch` |
| Off-by-one in grade boundary | Medium | Medium | Manual desk-check at 85, 90, 50, 49 |
| Column misalignment in reports | Low | Low | Set `setw()` generously; test with long names |
| Forgetting to exclude I/W from CH total | Medium | High | Unit test TC-15, TC-16, TC-17 cover this explicitly |

---

## UOH Grading Policy

| Marks Range | Grade | Grade Points |
|-------------|-------|-------------|
| 90 – 100    | A+    | 4.00        |
| 85 – 89     | A     | 4.00        |
| 80 – 84     | A-    | 3.67        |
| 75 – 79     | B+    | 3.33        |
| 71 – 74     | B     | 3.00        |
| 68 – 70     | B-    | 2.67        |
| 64 – 67     | C+    | 2.33        |
| 61 – 63     | C     | 2.00        |
| 58 – 60     | C-    | 1.67        |
| 54 – 57     | D+    | 1.33        |
| 50 – 53     | D     | 1.00        |
| Below 50    | F     | 0.00        |
| Incomplete  | I     | **Excluded** |
| Withdrawn   | W     | **Excluded** |

> **Note:** Both A+ (90–100) and A (85–89) map to 4.00 grade points per UOH policy.

---

## Testing Strategy

| Technique | Purpose |
|-----------|---------|
| Boundary value testing | Marks at 90, 89, 50, 49 — verify grade boundaries are exact |
| Invalid input testing | Marks > 100, negative marks, credit hours = 0 or 5 |
| Special grade handling | `I` and `W` — verify exclusion from SGPA and CGPA |
| Manual verification | Compare hand-calculated SGPA/CGPA to software output |
| All-I/W semester | Verify SGPA = 0 and no division-by-zero crash |
| Long course names | Verify UI table columns do not break |
