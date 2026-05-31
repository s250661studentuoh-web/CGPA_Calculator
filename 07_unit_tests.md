# Write Unit Tests

---

## Why Testing Matters

Most PF students skip this section. Including documented test cases demonstrates:
- Professional software development habits
- Confidence in your program's correctness
- Ability to think about edge cases — not just the happy path

> "Testing shows the presence of bugs, not their absence — but documented passing tests show the evaluator you know your code works."

---

## Test Category 1: Grade Conversion — Boundary Tests

Boundary testing verifies that the grade-mapping `if-else` chain uses `>=` (not `>`) at every breakpoint.

| Test ID | Input (Marks) | Expected Grade | Expected GP | Actual Output | Result |
|---------|--------------|----------------|-------------|---------------|--------|
| TC-01 | 100.0 | A+ | 4.00 | A+, 4.00 | ✅ Pass |
| TC-02 | 90.0  | A+ | 4.00 | A+, 4.00 | ✅ Pass |
| TC-03 | 89.9  | A  | 4.00 | A,  4.00 | ✅ Pass |
| TC-04 | 85.0  | A  | 4.00 | A,  4.00 | ✅ Pass |
| TC-05 | 84.9  | A- | 3.67 | A-, 3.67 | ✅ Pass |
| TC-06 | 80.0  | A- | 3.67 | A-, 3.67 | ✅ Pass |
| TC-07 | 75.0  | B+ | 3.33 | B+, 3.33 | ✅ Pass |
| TC-08 | 71.0  | B  | 3.00 | B,  3.00 | ✅ Pass |
| TC-09 | 70.9  | B- | 2.67 | B-, 2.67 | ✅ Pass |
| TC-10 | 68.0  | B- | 2.67 | B-, 2.67 | ✅ Pass |
| TC-11 | 50.0  | D  | 1.00 | D,  1.00 | ✅ Pass |
| TC-12 | 49.9  | F  | 0.00 | F,  0.00 | ✅ Pass |
| TC-13 | 0.0   | F  | 0.00 | F,  0.00 | ✅ Pass |

> **Key insight:** TC-04 and TC-05 are critical — they verify that marks=85 gives A (4.00) not A- (3.67). This is the most common off-by-one error.

---

## Test Category 2: Input Validation Tests

| Test ID | Input | Where | Expected Behavior | Result |
|---------|-------|-------|-------------------|--------|
| TC-14 | Marks = 101 | `inputCourse()` | Error message, re-prompt | ✅ Pass |
| TC-15 | Marks = -1  | `inputCourse()` | Error message, re-prompt | ✅ Pass |
| TC-16 | Marks = "abc" | `inputCourse()` | `invalid_argument` caught, re-prompt | ✅ Pass |
| TC-17 | Credit Hours = 0 | `inputCourse()` | Error message, re-prompt | ✅ Pass |
| TC-18 | Credit Hours = 5 | `inputCourse()` | Error message, re-prompt | ✅ Pass |
| TC-19 | Semesters = 0 | `getSemesterCount()` | Error message, re-prompt | ✅ Pass |
| TC-20 | Semesters = 21 | `getSemesterCount()` | Error message, re-prompt | ✅ Pass |
| TC-21 | Menu choice = 9 | `main()` | "Invalid choice" message | ✅ Pass |
| TC-22 | Menu choice = "x" | `main()` | `cin` fail caught, re-prompt | ✅ Pass |
| TC-23 | Empty course name | `inputCourse()` | Re-prompt until non-empty | ✅ Pass |

---

## Test Category 3: Special Grade Handling

| Test ID | Setup | Expected Behavior | Result |
|---------|-------|-------------------|--------|
| TC-24 | 1 course, grade = I | SGPA = 0.00 (no eligible courses) | ✅ Pass |
| TC-25 | 1 course, grade = W | SGPA = 0.00 (no eligible courses) | ✅ Pass |
| TC-26 | 3 courses, 1 is I | I course excluded from SGPA; CH not counted | ✅ Pass |
| TC-27 | 3 courses, 1 is W | W course excluded from SGPA; CH not counted | ✅ Pass |
| TC-28 | All courses = I | SGPA = 0.00; no division-by-zero crash | ✅ Pass |
| TC-29 | All courses = W | SGPA = 0.00; no division-by-zero crash | ✅ Pass |
| TC-30 | I in sem 1, normal in sem 2 | CGPA uses only sem 2 eligible courses | ✅ Pass |
| TC-31 | Enter lowercase "i" | Treated identically to uppercase "I" | ✅ Pass |
| TC-32 | Enter lowercase "w" | Treated identically to uppercase "W" | ✅ Pass |

---

## Test Category 4: SGPA Manual Verification

### Test Case TC-33 — Mixed grades, 3 courses

| Course | CH | Marks | Grade | GP   | QP    |
|--------|----|-------|-------|------|-------|
| Programming Fund. | 3 | 87 | A  | 4.00 | 12.00 |
| ICT Fundamentals  | 2 | 75 | B+ | 3.33 |  6.67 |
| English           | 2 | 68 | B- | 2.67 |  5.33 |

**Manual Calculation:**
```
Total QP = 12.00 + 6.67 + 5.33 = 24.00
Total CH = 3 + 2 + 2 = 7
SGPA = 24.00 / 7 = 3.4286 → displayed as 3.43
```
**Software Output:** `SGPA: 3.43`  **Verdict:** ✅ Match

---

### Test Case TC-34 — I/W courses excluded correctly

| Course | CH | Marks | Grade | GP   | QP    |
|--------|----|-------|-------|------|-------|
| Math     | 3 | 91  | A+   | 4.00 | 12.00 |
| Physics  | 2 | W   | W    | —    | —     |
| CS Lab   | 1 | I   | I    | —    | —     |

**Manual Calculation:**
```
Eligible: only Math (W and I excluded)
Total QP = 12.00
Total CH = 3      ← Physics CH=2 and CS Lab CH=1 NOT included
SGPA = 12.00 / 3 = 4.00
```
**Software Output:** `SGPA: 4.00`  **Verdict:** ✅ Match

---

## Test Category 5: CGPA Manual Verification

### Test Case TC-35 — 2 semesters

| Semester | Courses | Total QP | Total CH |
|----------|---------|----------|----------|
| Sem 1 | PF(3,87) ICT(2,75) Eng(2,68) | 24.00 | 7 |
| Sem 2 | Math(3,91) Stats(3,80) OOP(3,85) | 12.00+11.01+12.00 = 35.01 | 9 |

> Sem 2 detail: Math 91→4.00×3=12.00 | Stats 80→3.67×3=11.01 | OOP 85→4.00×3=12.00

**Manual Calculation:**
```
Total QP = 24.00 + 35.01 = 59.01
Total CH = 7 + 9 = 16
CGPA = 59.01 / 16 = 3.688 → displayed as 3.69
```
**Software Output:** `CGPA: 3.69`  **Verdict:** ✅ Match

> **Note:** This is NOT the same as averaging SGPAs: (3.43 + 3.89) / 2 = 3.66 ≠ 3.69. The weighted formula is correct.

---

## Test Category 6: UI Display Tests

| Test ID | Test | Expected Behavior | Result |
|---------|------|-------------------|--------|
| TC-36 | Course name exactly 24 chars | Fits in column without overflow | ✅ Pass |
| TC-37 | Course name 25+ chars | Truncated to fit column | ✅ Pass |
| TC-38 | CGPA = 3.50 exactly | Status: Dean's List ★ | ✅ Pass |
| TC-39 | CGPA = 3.49 | Status: Good Standing ✓ | ✅ Pass |
| TC-40 | CGPA = 2.00 exactly | Status: Satisfactory ! | ✅ Pass |
| TC-41 | CGPA = 1.99 | Status: Academic Warning ✗ | ✅ Pass |

---

## Test Summary

| Category | Tests | Passed | Failed |
|----------|-------|--------|--------|
| Grade Conversion (Boundary) | 13 | 13 | 0 |
| Input Validation | 10 | 10 | 0 |
| Special Grade Handling (I/W) | 9  | 9  | 0 |
| SGPA Manual Verification | 2  | 2  | 0 |
| CGPA Manual Verification | 1  | 1  | 0 |
| UI Display Tests | 6  | 6  | 0 |
| **Total** | **41** | **41** | **0** |

> **Conclusion:** All 41 test cases passed. SGPA/CGPA results matched manual calculations. No crashes detected for any invalid input scenario.
