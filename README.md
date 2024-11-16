# example-of-embedding-python-in-c++

## Overview

This code is a demonstration project that showcases how to embed Python scripts within a C++ application. The project illustrates:

- Initializing and finalizing the Python interpreter in C++.
- Adjusting `sys.path` to include custom script directories.
- Importing and executing Python functions from a script.
- Passing arguments from C++ to Python functions.
- Retrieving results from Python functions back into C++.
- Handling exceptions raised in Python and displaying them in C++.

This project serves as a practical example for developers interested in integrating Python scripting capabilities into their C++ applications.

---

## Features

- **Embed Python Interpreter**: Learn how to initialize and finalize the Python interpreter in a C++ program.
- **Call Python Functions**: Execute Python functions from scripts located in specific directories.
- **Argument Passing**: Pass numerical arguments from C++ to Python functions.
- **Result Handling**: Retrieve and process results returned by Python functions in C++.
- **Exception Handling**: Capture and display Python exceptions in the C++ application.

---

## Getting Started

### Prerequisites

- **C++ Compiler**: A compiler that supports C++17 (for `std::filesystem`), such as minGW
- **CMake**: Version 3.10 or higher.

### Project Structure

```plaintext
CppPythonEmbed/
├── CMakeLists.txt
├── src/
│   └── main.cpp
├── scripts/
│   └── functions.py
├── include/
│   └── Python.h
│   └── ... (other headers)
└── python-3.13.0-embed-amd64/
    └── python313.dll
    └── ... (other files)
```
### To run the project in Windows, run the file run.ps1
```bash
  ./run.ps1
```

## Python Embeddable Distribution:

The project includes files from the Python Embeddable Distribution, which is owned by the Python Software Foundation.
These files are subject to the Python Software Foundation License.
The Python license file is included in the python-3.13.0-embed-amd64 folder.
For more information, refer to the Python License.
