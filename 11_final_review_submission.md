# Final Review & Submission Preparation

---

## Pre-Submission Checklist

Work through every item systematically. Do **not** submit until every box is checked.

### ✦ Source Code

- [ ] All `.cpp` and `.h` files compile without errors
- [ ] `g++ -std=c++17 -Wall -Wextra` produces **zero** warnings
- [ ] All debug `cout << "[DEBUG]..."` trace statements removed
- [ ] File headers (author, registration number, date, purpose) present in every `.cpp` and `.h` file
- [ ] Every function has a header comment (purpose, parameters, return value)
- [ ] All non-obvious logic lines have inline comments
- [ ] Consistent 4-space indentation throughout all files
- [ ] No hardcoded magic numbers — named constants used where applicable (`MAX_CREDIT_HOURS`, `COL_COURSE`, etc.)
- [ ] No unused variables, no unused `#include` statements
- [ ] `structs.h` uses `#pragma once` to prevent double-inclusion

### ✦ Functionality

- [ ] Main menu: all 3 options work correctly
- [ ] Semester count: accepts 1–20; rejects 0 and 21+
- [ ] Course count per semester: accepts 1–15; rejects 0 and 16+
- [ ] Course name: re-prompts on empty input
- [ ] Credit hours: accepts 1–4; rejects 0 and 5+; rejects non-integers
- [ ] Marks: accepts 0.0–100.0; rejects negative values, values > 100, and non-numeric text
- [ ] Special grades: `I` and `W` (and lowercase `i`/`w`) accepted and handled correctly
- [ ] I/W courses are **excluded** from quality points AND credit hours totals
- [ ] SGPA returns 0.00 (not a crash) when all courses in a semester are I/W
- [ ] CGPA uses raw cumulative QP/CH totals — not an average of SGPA values
- [ ] Academic standing message displays correctly at all four CGPA ranges
- [ ] `getline()` for course name does not skip due to leftover `\n` in buffer

### ✦ Documentation

- [ ] Project report complete (all 9 sections including screenshots)
- [ ] Test log (`testcases/test_log.md`) filled with all 41 test case results
- [ ] README.md includes compile and run instructions
- [ ] Screenshots folder contains at least 5 sample output screenshots
- [ ] `CMakeLists.txt` (and optionally `Makefile`) present and correct

---

## Submission Package

Organize your submission exactly as follows before zipping:

```text
[YourName]_CGPA_Calculator/
│
├── source_code/
│   ├── main.cpp
│   ├── structs.h             ← shared Course and Semester struct definitions
│   ├── functions.h
│   ├── functions.cpp
│   ├── grading.h
│   ├── grading.cpp
│   ├── report.h
│   └── report.cpp
│
├── build_config/
│   ├── CMakeLists.txt        ← CLion build configuration
│   └── Makefile              ← optional command-line build
│
├── documentation/
│   └── project_report.pdf    ← compiled from your markdown files
│
├── testcases/
│   └── test_log.md           ← all 41 test case results with pass/fail
│
├── screenshots/
│   ├── 01_main_menu.png
│   ├── 02_course_input.png
│   ├── 03_validation_error.png
│   ├── 04_iw_grade.png
│   ├── 05_semester_report.png
│   ├── 06_final_cgpa.png
│   └── 07_grading_policy.png
│
└── README.md
```

---

## Final Build & Run Verification

Run these exact commands before submission to confirm everything is clean:

```bash
# 1. Full clean build with strict warnings
g++ -std=c++17 -Wall -Wextra -Wpedantic \
    main.cpp functions.cpp grading.cpp report.cpp \
    -o cgpa_calculator

# 2. Confirm zero warnings in the output above ↑

# 3. Run the program and manually test all three menu options
./cgpa_calculator       # Linux / macOS
cgpa_calculator.exe     # Windows

# 4. Test scenario: 2 semesters, 3 courses each, including 1 I/W course
# Verify SGPA and CGPA match your manual calculation
```

---

## Demo Strategy (Presentation Day)

Follow this sequence for a clean, confident 10-minute demo:

| Step | What to Show | Time | Why It Impresses |
|------|-------------|------|-----------------|
| **1 · Problem** | Explain why manual CGPA calculation is error-prone; show the 14-row UOH grading table | 1 min | Sets context; shows you understand the real-world need |
| **2 · Architecture** | Open your module diagram; explain the 5-module design and `structs.h` separation | 2 min | Demonstrates software engineering thinking |
| **3 · Live Demo** | Run the program — enter 2 semesters, 3–4 courses each; include one I/W course | 3 min | Core feature showcase; shows it actually works |
| **4 · Validation Demo** | Deliberately enter marks=150, then "abc", then credit hours=0 | 1 min | Shows robustness; most students skip this |
| **5 · Test Cases** | Show 3–4 boundary test rows and match SGPA to your manual calculation | 2 min | Proves accuracy; evaluators love this |
| **6 · Future Scope** | Mention GPA prediction, file saving, scholarship checker | 1 min | Shows you thought beyond the assignment |

**Demo tips:**
- Run the program **before** your demo slot to ensure it compiles on the lab machine
- Have a sample run scripted in a `.txt` file so you can type quickly without hesitation
- Know the manual calculation for your demo data — have the result memorized or on paper

---

## Evaluation Criteria Self-Assessment

Rate yourself honestly. Identify gaps and fix them before submission.

| Criterion | Weight | Self-Score /10 | Notes |
|-----------|--------|---------------|-------|
| Correct SGPA calculation | High | | Verify against manual TC-33 and TC-34 |
| Correct CGPA calculation (cumulative, not averaged) | High | | Verify against TC-35 |
| Input validation — no crashes on bad input | Medium | | Test marks="abc", CH=0, all-I/W semester |
| I/W grade handling | Medium | | Excluded from QP AND from CH total |
| Code structure and modularity | Medium | | 5 modules, `structs.h` separation |
| Formatted UI output (iomanip, aligned columns) | Medium | | All columns aligned, I/W rows show "—" |
| Comments and code quality | Medium | | File headers, function headers, inline comments |
| Documentation completeness | High | | All 9 sections; screenshots included |
| Test case documentation | Medium | | 41 test cases with manual verification shown |
| Presentation quality | High | | Rehearsed; validation demo ready; numbers memorized |

---

## Final Words

> A project that is **correct, clean, well-tested, and well-documented** always scores higher than one that is feature-rich but crashes on bad input and has no comments.
>
> You now have the architecture, the complete code, 41 test cases, a 9-bug fix log, full documentation, and a presentation script.
>
> **Execute the checklist. Submit confidently.**
