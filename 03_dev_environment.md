# Set Up Development Environment

---

## Tools & Software

| Tool | Purpose | Version |
|------|---------|---------| 
| **CLion** | Primary C++ IDE (JetBrains) | 2024.x or later |
| **MinGW (GCC)** | C++ compiler for Windows | GCC 13+ (winlibs build) |
| **C++ Standard** | Language standard used | C++17 |
| **CMake** | Build system (bundled with CLion) | 3.20+ |
| **Git** *(recommended)* | Version control — backup your work | 2.x latest |
| **GitHub** *(recommended)* | Remote backup and portfolio | — |

---

## Compiler Setup (Windows — MinGW)

**Step-by-step:**

1. Download **MinGW** from [winlibs.com](https://winlibs.com) — choose the `UCRT` runtime, `x86_64`, with `POSIX` threads
2. Extract to a short path, e.g. `C:\mingw64`
3. Add `C:\mingw64\bin` to your system `PATH`:
   - Open **System Properties → Advanced → Environment Variables**
   - Edit `Path` under *System variables* → add `C:\mingw64\bin`
4. Open a new terminal and verify:
   ```bash
   g++ --version
   # Expected: g++ (MinGW-W64 ...) 13.x.x
   ```

---

## CLion Project Setup

1. Launch CLion → **New Project → C++ Executable → C++17**
2. Name the project `CGPA-Calculator`
3. Replace the generated `CMakeLists.txt` with:

```cmake
cmake_minimum_required(VERSION 3.20)
project(CGPA_Calculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable strict warnings — important for clean code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(CGPA_Calculator
    main.cpp
    functions.cpp
    grading.cpp
    report.cpp
)
```

4. Press **Shift+F10** (or click the green ▶ button) to build and run
5. Use **Ctrl+Alt+L** to auto-format code before submission

### Useful CLion Shortcuts

| Shortcut | Action |
|----------|--------|
| `Shift+F10` | Build and Run |
| `Shift+F9` | Build and Debug |
| `Ctrl+Alt+L` | Reformat code |
| `F9` | Resume debugger |
| `F8` | Step over (debugger) |
| `F7` | Step into (debugger) |
| `Alt+F8` | Evaluate expression in debugger |

---

## Alternative: VS Code Setup

If CLion is unavailable, use **VS Code** with the C/C++ extension:

1. Install [VS Code](https://code.visualstudio.com)
2. Install extensions: `C/C++` (Microsoft), `C/C++ Extension Pack`
3. Create `.vscode/tasks.json`:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build CGPA Calculator",
      "type": "shell",
      "command": "g++",
      "args": [
        "-std=c++17", "-Wall", "-g",
        "main.cpp", "functions.cpp", "grading.cpp", "report.cpp",
        "-o", "cgpa_calculator"
      ],
      "group": { "kind": "build", "isDefault": true }
    }
  ]
}
```

4. Press **Ctrl+Shift+B** to build, then run `./cgpa_calculator` in the terminal

---

## Command-Line Build (No IDE)

For compiling directly from the terminal:

```bash
# Compile all source files with warnings enabled
g++ -std=c++17 -Wall -Wextra -g main.cpp functions.cpp grading.cpp report.cpp -o cgpa_calculator

# Run
./cgpa_calculator          # Linux / macOS
cgpa_calculator.exe        # Windows
```

### Optional: Makefile

Save as `Makefile` in the project root for one-command builds:

```makefile
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET   = cgpa_calculator
SRCS     = main.cpp functions.cpp grading.cpp report.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
```

Then just run:
```bash
make        # build
make clean  # remove binary
```

---

## Recommended Folder Structure

```text
CGPA-Calculator/
│
├── main.cpp              ← Entry point; orchestrates all modules
├── structs.h             ← Shared Course and Semester struct definitions
├── functions.h           ← Declarations: input + validation functions
├── functions.cpp         ← Definitions: input + validation logic
├── grading.h             ← Declarations: grade mapping + GPA functions
├── grading.cpp           ← Definitions: getGrade, getGradePoint, SGPA, CGPA
├── report.h              ← Declarations: display functions
├── report.cpp            ← Definitions: displayMainMenu, semester table, final summary
│
├── CMakeLists.txt        ← CLion build configuration
├── Makefile              ← Optional command-line build
│
├── testcases/
│   └── test_log.md       ← Manual test case results (19+ test cases)
│
├── screenshots/
│   ├── 01_main_menu.png
│   ├── 02_course_input.png
│   ├── 03_semester_report.png
│   └── 04_final_cgpa.png
│
└── README.md             ← Project overview, build instructions
```

> **Why separate `structs.h`?** Both `grading.h`, `functions.h`, and `report.h` need the `Course` and `Semester` types. Putting them in one shared header prevents circular include issues and keeps each module header clean.

---

## README.md Template

```markdown
# UOH CGPA Calculator

A console-based CGPA calculator for University of Haripur students.
Built in C++ (C++17) for the Programming Fundamentals course.

## How to Build & Run

### Using CLion
Open the project folder in CLion — it auto-configures from `CMakeLists.txt`.
Press **Shift+F10** to build and run.

### Using g++ directly
```bash
g++ -std=c++17 -Wall main.cpp functions.cpp grading.cpp report.cpp -o cgpa_calculator
./cgpa_calculator
```

## Features
- SGPA calculation per semester
- Cumulative CGPA across all semesters
- Input validation (marks 0–100, credit hours 1–4)
- I (Incomplete) and W (Withdrawn) grade support
- Formatted console report tables
- Academic standing display (Dean's List, Good Standing, etc.)

## Project Structure
See `04_architecture_and_data_structures.md` for module diagram.

## Author
[Your Name] — University of Haripur, [Your Registration Number]
```
