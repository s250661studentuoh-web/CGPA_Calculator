# Define Project Scope & Requirements

---

## Functional Requirements

| # | Requirement | Acceptance Criteria |
|---|-------------|---------------------|
| FR-01 | Accept course name, credit hours, and marks as input | Names up to 30 chars; CH 1–4; marks 0–100 or I/W |
| FR-02 | Convert marks to grade and grade points using UOH policy | All 12 grade bands produce correct letter + GP value |
| FR-03 | Calculate SGPA for each semester | SGPA = Σ(QP) / Σ(CH) for eligible courses only |
| FR-04 | Calculate cumulative CGPA across all semesters | CGPA uses total QP and CH across every semester |
| FR-05 | Support multiple semesters (user-defined count, ≥ 1) | Works correctly for 1, 2, and 8 semesters |
| FR-06 | Support multiple courses per semester (user-defined count, ≥ 1) | Works correctly for 1 course and 10 courses per semester |
| FR-07 | Validate all user inputs | Re-prompt on invalid entry; never crash on bad input |
| FR-08 | Handle I (Incomplete) and W (Withdrawn) — exclude from GPA | These courses contribute 0 QP and 0 to CH totals |
| FR-09 | Display a formatted per-semester report table | Aligned columns: Course, CH, Marks, Grade, GP, QP |
| FR-10 | Display a final CGPA summary with academic standing | Shows all semester SGPAs, CGPA, and standing label |
| FR-11 | Display the UOH grading policy table on demand | All 14 rows shown cleanly from the main menu |

---

## Non-Functional Requirements

| # | Requirement | Description |
|---|-------------|-------------|
| NFR-01 | **Correctness** | Calculations match manual hand-computation to 2 decimal places |
| NFR-02 | **Reliability** | No crashes for any valid or invalid input — all edge cases handled |
| NFR-03 | **Portability** | Compiles cleanly on any system with GCC / MinGW / Clang, C++17 |
| NFR-04 | **Usability** | Console menus require no manual to operate; prompts are self-explanatory |
| NFR-05 | **Maintainability** | Modular design; any function can be updated without touching others |
| NFR-06 | **Readability** | Every function has a header comment; all non-obvious lines have inline comments |

---

## User Stories

> *"As a student, I want to enter my marks each semester so that the system automatically calculates my SGPA without manual errors."*

> *"As a student, I want to see my cumulative CGPA after all semesters so that I can track my academic standing over time."*

> *"As a student, I want the system to warn me when I enter invalid marks so that I don't get wrong results silently."*

> *"As a student, I want to enter I or W for special grades so that incomplete or withdrawn courses don't unfairly affect my CGPA."*

> *"As a student, I want to view the UOH grading policy table at any time so that I can confirm how my marks translate to grades."*

> *"As a student, I want to see my academic standing (Dean's List, Good Standing, etc.) so that I understand what my CGPA means."*

---

## Constraints

| Constraint | Detail |
|------------|--------|
| Language | C++ (C++17 standard) |
| Interface | Console only — no GUI, no web |
| Compiler | MinGW / GCC 13+ on Windows; also compatible with Clang on macOS/Linux |
| Libraries | Standard library only: `<iostream>`, `<iomanip>`, `<string>`, `<vector>`, `<stdexcept>` |
| Input source | Keyboard only — no file input in base version |
| Platform | Windows 10/11 primary; Linux/macOS compatible |

---

## Input / Output Specification

### Inputs

| Input | Type | Valid Range | Error Handling |
|-------|------|-------------|----------------|
| Number of semesters | `int` | 1 – 20 | Re-prompt if ≤ 0 or > 20 |
| Number of courses | `int` | 1 – 15 | Re-prompt if ≤ 0 or > 15 |
| Course name | `string` | Non-empty, ≤ 30 chars | Re-prompt if empty |
| Credit hours | `int` | 1 – 4 | Re-prompt if out of range |
| Marks / special grade | `string` | 0.0 – 100.0 or "I" or "W" | Re-prompt on invalid |

### Outputs

| Output | Format |
|--------|--------|
| Per-semester table | 6-column `iomanip`-aligned table with SGPA footer |
| Final CGPA summary | All semester SGPAs + cumulative CGPA + academic standing |
| Grading policy table | 14-row table: marks range, grade letter, grade points |
| Validation errors | Inline `cout` messages, loop re-prompts — no exceptions thrown to user |
