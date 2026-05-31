# Debug & Fix Issues

---

## Debugging Log

This log documents all bugs discovered during development and testing. Each entry includes the root cause and the exact fix applied. Keeping this log is a professional practice — it demonstrates that you understand *why* bugs occur, not just how to patch them.

---

## Bug Table

| Bug ID | Description | Root Cause | Fix Applied | Status |
|--------|-------------|------------|-------------|--------|
| BUG-01 | SGPA was wrong when a semester contained an I/W course | I/W courses were included in `totalCH` denominator | Added `if (grade == "I" \|\| grade == "W") continue;` in both SGPA and CGPA loops | ✅ Fixed |
| BUG-02 | Program crashed when user typed text (e.g. "abc") for marks | `cin >> float` fails silently on non-numeric input; stream enters error state, `marks` gets 0 | Changed to `string` input + `stof()` inside a `try-catch` block | ✅ Fixed |
| BUG-03 | CGPA was calculated per semester (not cumulatively) | `totalQP` and `totalCH` accumulator variables were declared **inside** the outer semester loop — reset on every iteration | Moved both accumulators **outside** the loop in `calculateCGPA()` | ✅ Fixed |
| BUG-04 | Division by zero when all courses in a semester were I/W | After the I/W skip, `totalCH` remained 0; dividing `totalQP / totalCH` = undefined behaviour | Added `if (totalCH == 0) return 0.0f;` guard before the division | ✅ Fixed |
| BUG-05 | Grade point for marks = 85 was 3.67 (A-) instead of 4.00 (A) | Off-by-one: `if (marks > 85)` used `>` instead of `>=` | Changed to `if (marks >= 85) return 4.00f;` | ✅ Fixed |
| BUG-06 | Report table columns misaligned for long course names | `setw(15)` was too narrow — names > 15 chars pushed all subsequent columns right | Increased to `setw(25)` and defined a named constant `COL_COURSE` | ✅ Fixed |
| BUG-07 | Main menu re-displayed after invalid choice with no error message | Missing `default` case in `switch (choice)` | Added `default: cout << "[!] Invalid choice.\n";` | ✅ Fixed |
| BUG-08 | `getline()` for course name skipped immediately (read empty string) | After `cin >> n` for course count, a `\n` linefeed remained in the stream; `getline()` consumed it instantly | Added `cin.ignore(1000, '\n');` before each `getline()` call | ✅ Fixed |
| BUG-09 | CGPA incorrectly calculated as the average of SGPA values | Used `(sum of SGPAs) / numSemesters` — gives wrong result when semesters have different credit loads | Rewrote `calculateCGPA()` to accumulate raw QP and CH across all semesters | ✅ Fixed |

---

## Detailed Bug Walkthroughs

### BUG-02 — `cin` fails on text input

**Before (broken):**
```cpp
float marks;
cout << "Enter marks: ";
cin >> marks;          // if user types "abc": marks = 0, cin enters fail state
                        // all subsequent cin >> calls ALSO fail silently
```

**After (fixed):**
```cpp
string input;
cout << "Marks (0-100) or I/W: ";
cin >> input;

try {
    float marks = stof(input);       // throws invalid_argument if not a number
    if (!validateMarks(marks)) {
        cout << "[!] Marks must be 0–100.\n";
    } else {
        // safe to use marks
    }
} catch (const invalid_argument&) {
    cout << "[!] That's not a number. Enter marks or I/W.\n";
}
```

---

### BUG-03 — CGPA reset on every semester

**Before (broken):**
```cpp
for (auto& sem : semesters) {
    float totalQP = 0;    // ← WRONG: declared inside loop, resets each iteration
    int   totalCH = 0;
    for (auto& c : sem.courses) { ... }
}
return totalQP / totalCH;  // only reflects the LAST semester
```

**After (fixed):**
```cpp
float totalQP = 0;    // ← declared OUTSIDE both loops
int   totalCH = 0;
for (auto& sem : semesters) {
    for (auto& c : sem.courses) {
        if (c.grade == "I" || c.grade == "W") continue;
        totalQP += c.qualityPoints;
        totalCH += c.creditHours;
    }
}
return (totalCH == 0) ? 0.0f : totalQP / totalCH;
```

---

### BUG-05 — Off-by-one at grade boundary 85

**Before (broken):**
```cpp
if (marks > 85) return 4.00f;    // marks=85 falls through to next condition
if (marks > 80) return 3.67f;    // marks=85 → 3.67 ← WRONG
```

**After (fixed):**
```cpp
if (marks >= 85) return 4.00f;   // marks=85 → 4.00 ✅
if (marks >= 80) return 3.67f;
```

---

### BUG-08 — `getline()` skips course name

**Root cause:** After `cin >> courseCount` reads an integer, the newline `\n` from the Enter key stays in the input buffer. The next `getline()` reads that empty `\n` and immediately returns an empty string.

**Fix:**
```cpp
int getCourseCount(int semNum) {
    int n;
    cin >> n;
    // ... validation ...
    return n;
}

// In inputCourse(), BEFORE the first getline():
cin.ignore(1000, '\n');   // discard the leftover '\n' from getCourseCount's cin >>
getline(cin, c.courseName);
```

---

## Debugging Techniques Used

### 1. Trace Printing
Temporary `cout` statements inserted to inspect variable values mid-execution:

```cpp
// DEBUG trace — remove before final submission
cout << "[DEBUG] totalQP=" << totalQP
     << " totalCH=" << totalCH
     << " SGPA=" << (totalCH ? totalQP/totalCH : 0.0f) << "\n";
```

### 2. Manual Desk Check
Traced through the `getGradePoint()` if-else chain on paper with specific boundary inputs (84.9, 85.0, 85.1) before running the code. This caught BUG-05 before it was compiled.

### 3. Boundary Testing
Deliberately entered edge-case values (0, 49.9, 50.0, 84.9, 85.0, 89.9, 90.0, 100.0, 100.1, -1) to verify each grade boundary.

### 4. Incremental Compilation
Compiled and tested `grading.cpp` functions individually using a small `test_main.cpp` before integrating all modules — isolated bugs to specific components before the full build.

### 5. CLion Debugger
Set breakpoints inside `calculateSGPA()` and used the watch window to inspect `totalQP` and `totalCH` at each loop iteration. This caught BUG-03 (reset inside loop) immediately.

---

## Lessons Learned

| Lesson | Applied To |
|--------|------------|
| Always guard against `totalCH == 0` before dividing | `calculateSGPA()`, `calculateCGPA()` |
| Use `>=` not `>` at every grade boundary in the if-else chain | `getGradePoint()` |
| Read as `string` first, convert with `stof()` inside `try-catch` | `inputCourse()` |
| Declare accumulators **outside** loops they accumulate across | `calculateCGPA()` |
| Call `cin.ignore()` before every `getline()` that follows a `cin >>` | `inputCourse()` |
| CGPA ≠ average of SGPAs — always use raw QP/CH totals | `calculateCGPA()` |
