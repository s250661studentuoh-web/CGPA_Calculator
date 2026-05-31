# Project Documentation — UOH CGPA Calculator

---

## 1. Introduction

### 1.1 Problem Description

Students at the University of Haripur (UOH) must manually calculate their SGPA and CGPA at the end of each semester using the institution's official grading policy. This manual process is slow, error-prone, and does not account for special academic statuses such as Incomplete (I) or Withdrawn (W). Students who miscalculate their GPA may make incorrect decisions about course loads, scholarship eligibility, or degree progress.

### 1.2 Proposed Solution

A console-based CGPA Calculator developed in C++ that:
- Accepts course data (name, credit hours, marks or special grade) for one or more semesters
- Automatically converts marks to letter grades and grade points using UOH's official policy
- Computes quality points, SGPA per semester, and cumulative CGPA
- Validates all inputs and handles I/W grades without crashing
- Presents formatted, readable reports in the terminal

### 1.3 Target Users

University of Haripur students who wish to compute their academic GPA without manual calculation. The program requires no prior technical knowledge — all menus are self-explanatory.

---

## 2. Objectives

By the end of this project, the system will:

1. Accept student course data (name, credit hours, marks) for any number of semesters
2. Convert marks to letter grades and grade points using UOH's official 14-row grading table
3. Compute SGPA for each individual semester using the quality-points formula
4. Compute cumulative CGPA across all entered semesters
5. Validate all inputs and handle edge cases gracefully (invalid marks, non-numeric input, I/W grades, all-I/W semesters)
6. Present clean, aligned reports using `<iomanip>` formatting with box-drawing characters

---

## 3. Methodology

The project followed a structured, phase-based software development process:

| Phase | Activity | Deliverable |
|-------|----------|-------------|
| Planning | Define scope, requirements, constraints, user stories | `01_project_proposal.md`, `02_scope_and_requirements.md` |
| Design | Module architecture, data structures, flowchart, header files | `04_architecture_and_data_structures.md` |
| Implementation | Input, validation, grade mapping, GPA calculation, UI display | `05_core_functionality.md`, `06_user_interface.md` |
| Testing | 41 manual test cases: boundary, validation, I/W, SGPA, CGPA | `07_unit_tests.md` |
| Debugging | Log and fix 9 identified bugs with root-cause analysis | `08_debug_and_fix.md` |
| Cleanup | Add comments, enforce naming conventions, remove debug traces | `09_comments_and_cleanup.md` |
| Documentation | Write this full project report | `10_project_documentation.md` |
| Submission | Assemble package, final checklist, demo preparation | `11_final_review_submission.md` |

---

## 4. Algorithms

### 4.1 Grade Conversion Algorithm

```
Input: float marks ∈ [0, 100]

if marks ≥ 90  → Grade = "A+", GP = 4.00
if marks ≥ 85  → Grade = "A",  GP = 4.00   (A and A+ both = 4.00 per UOH policy)
if marks ≥ 80  → Grade = "A-", GP = 3.67
if marks ≥ 75  → Grade = "B+", GP = 3.33
if marks ≥ 71  → Grade = "B",  GP = 3.00
if marks ≥ 68  → Grade = "B-", GP = 2.67
if marks ≥ 64  → Grade = "C+", GP = 2.33
if marks ≥ 61  → Grade = "C",  GP = 2.00
if marks ≥ 58  → Grade = "C-", GP = 1.67
if marks ≥ 54  → Grade = "D+", GP = 1.33
if marks ≥ 50  → Grade = "D",  GP = 1.00
otherwise      → Grade = "F",  GP = 0.00

If input = "I" → Grade = "I", GP = 0.00, excluded from GPA
If input = "W" → Grade = "W", GP = 0.00, excluded from GPA
```

**Critical boundary note:** The condition is `>=` not `>` at every breakpoint. Using `>` at 85 would incorrectly assign A- (3.67) to a student with exactly 85 marks.

### 4.2 SGPA Algorithm

```
Input: list of Course structs for one semester

totalQP ← 0
totalCH ← 0

For each course c in semester:
    If c.grade is "I" or "W": SKIP (do not add to QP or CH)
    c.qualityPoints ← c.gradePoint × c.creditHours
    totalQP ← totalQP + c.qualityPoints
    totalCH ← totalCH + c.creditHours

If totalCH = 0: return 0.0  ← division-by-zero guard

SGPA ← totalQP / totalCH
Return SGPA
```

### 4.3 CGPA Algorithm

```
Input: list of Semester structs (each containing list of Course structs)

totalQP ← 0
totalCH ← 0

For each semester s in allSemesters:
    For each course c in s.courses:
        If c.grade is "I" or "W": SKIP
        totalQP ← totalQP + c.qualityPoints
        totalCH ← totalCH + c.creditHours

If totalCH = 0: return 0.0

CGPA ← totalQP / totalCH
Return CGPA
```

> **Important:** CGPA is **not** the arithmetic mean of SGPA values. It is a weighted average using total quality points and total credit hours across all semesters. Courses with more credit hours have proportionally more impact on the CGPA.

---

## 5. Data Structures

### 5.1 `Course` Struct

Holds all data for a single course in a single semester:

```cpp
struct Course {
    string courseName;    // Name, e.g. "Programming Fundamentals"
    int    creditHours;   // 1 – 4
    float  marks;         // 0.0 – 100.0; -1.0 sentinel for I/W
    string grade;         // Letter: "A+", "B", "F", "I", "W"
    float  gradePoint;    // 0.00 – 4.00 (0.00 for I/W)
    float  qualityPoints; // gradePoint × creditHours; 0 for I/W
};
```

### 5.2 `Semester` Struct

Groups all courses for one semester and stores the computed SGPA:

```cpp
struct Semester {
    int            semesterNumber; // 1-indexed
    vector<Course> courses;        // dynamic — any number of courses
    float          sgpa;           // computed by calculateSGPA()
};
```

### 5.3 Program-Level Data

```cpp
vector<Semester> allSemesters;  // holds every semester entered
float            cgpa = 0.0f;   // final result, computed at the end
```

### 5.4 Data Flow

```
User Input
   │
   ▼
Course struct populated:
  courseName, creditHours, marks, grade, gradePoint
   │
   ▼
calculateSGPA() fills in:
  course.qualityPoints (for each eligible course)
  semester.sgpa
   │
   ▼
calculateCGPA() aggregates:
  all course.qualityPoints and creditHours → cgpa
   │
   ▼
displayFinalReport() reads:
  semester.sgpa (per semester) + cgpa → formatted output
```

---

## 6. Screenshots

*(Insert screenshots of actual program output here before final submission)*

**Recommended screenshots to include:**

| # | Screenshot | What to Capture |
|---|-----------|-----------------|
| 1 | `01_main_menu.png` | The main menu with all 3 options |
| 2 | `02_course_input.png` | Entering course data for 1 semester |
| 3 | `03_validation_error.png` | Invalid marks input showing the error message + re-prompt |
| 4 | `04_iw_grade.png` | Entering "W" or "I" and seeing it handled in the table |
| 5 | `05_semester_report.png` | The formatted semester table with SGPA |
| 6 | `06_final_cgpa.png` | The final CGPA summary with academic standing |
| 7 | `07_grading_policy.png` | The grading policy table from menu option 2 |

---

## 7. Testing

A total of **41 manual test cases** were executed across six categories:

| Category | Tests | Passed | Failed |
|----------|-------|--------|--------|
| Grade Conversion (Boundary) | 13 | 13 | 0 |
| Input Validation | 10 | 10 | 0 |
| Special Grade Handling (I/W) | 9 | 9 | 0 |
| SGPA Manual Verification | 2 | 2 | 0 |
| CGPA Manual Verification | 1 | 1 | 0 |
| UI Display | 6 | 6 | 0 |
| **Total** | **41** | **41** | **0** |

All SGPA and CGPA results matched manual hand-calculations. No crashes were detected for any invalid input scenario. Full test log is in `testcases/test_log.md`.

---

## 8. Bugs Fixed

A total of **9 bugs** were identified and resolved during development:

| Bug | Description | Fix Summary |
|-----|-------------|-------------|
| BUG-01 | I/W courses included in credit hours total | Added `continue` for I/W in GPA loops |
| BUG-02 | Program crash on non-numeric marks input | Switched to `string` + `stof()` + `try-catch` |
| BUG-03 | CGPA computed per semester, not cumulatively | Moved accumulators outside the semester loop |
| BUG-04 | Division by zero when all courses are I/W | Added `if (totalCH == 0) return 0.0f` guard |
| BUG-05 | Marks=85 mapped to 3.67 instead of 4.00 | Changed `>` to `>=` at the 85 boundary |
| BUG-06 | Long course names broke table alignment | Increased column width and added truncation |
| BUG-07 | Invalid menu choice silently re-showed menu | Added `default` case with error message |
| BUG-08 | `getline()` skipped course name input | Added `cin.ignore()` before `getline()` |
| BUG-09 | CGPA computed as average of SGPAs | Rewrote to use raw QP/CH totals across all semesters |

Full details in `08_debug_and_fix.md`.

---

## 9. Conclusion

### Benefits Delivered
- Eliminates manual CGPA calculation errors completely
- Handles I/W special grades correctly and automatically
- Provides formatted, readable academic reports
- Robust against all invalid input — no crashes
- Extensible with minimal changes (see Future Scope)

### Limitations
- Console-based only — no GUI
- Data is not saved between sessions (no file persistence in base version)
- Limited to UOH grading policy — other institutions require a different grade table

### Future Scope

| Feature | Description | Difficulty |
|---------|-------------|------------|
| Save to file | Export results to `student_result.txt` using `ofstream` | Easy |
| Load from file | Read course data from a `.csv` or `.txt` file | Medium |
| GPA prediction | "If I score X next semester, what will my CGPA be?" | Medium |
| Scholarship checker | Flag CGPA ≥ 3.5 as merit scholarship eligible | Easy |
| Multi-student mode | Support multiple student profiles in one session | Hard |
| Progress tracking | Display CGPA trend across semesters as a bar chart | Hard |
