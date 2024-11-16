#include <Python.h>
#include <iostream>
#include <string>
#include <filesystem>

int main(int argc, char *argv[]) {
    // Initialize the Python Interpreter
    Py_Initialize();

    // Check if two arguments are provided (excluding the program name)
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " num1 num2" << std::endl;
        return 1;
    }

    // Variables to hold the numbers
    int num1 = 0;
    int num2 = 0;

    // Try to convert the arguments to integers
    try {
        num1 = std::stoi(argv[1]);
        num2 = std::stoi(argv[2]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: One of the inputs is not a valid integer." << std::endl;
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: One of the inputs is too large to be an integer." << std::endl;
        return 1;
    }

    try {
        // Get the current path
        std::filesystem::path current_path = std::filesystem::current_path();

        // Construct the path to the 'scripts' directory
        std::filesystem::path scripts_dir = current_path / "scripts";

        // Verify that the 'scripts' directory exists
        if (!std::filesystem::exists(scripts_dir)) {
            throw std::runtime_error("Scripts directory not found: " + scripts_dir.string());
        }

        // Add the 'scripts' directory to sys.path
        std::string add_path = "import sys; sys.path.insert(0, r'" + scripts_dir.string() + "')";
        PyRun_SimpleString(add_path.c_str());

        // Import the module 'functions'
        PyObject* pName = PyUnicode_DecodeFSDefault("functions");
        PyObject* pModule = PyImport_Import(pName);
        Py_DECREF(pName);

        if (pModule == nullptr) {
            PyErr_Print();
            throw std::runtime_error("Failed to load module 'functions'");
        }

        // Get the function 'add_numbers' from the module
        PyObject* pFunc = PyObject_GetAttrString(pModule, "add_numbers");
        if (pFunc && PyCallable_Check(pFunc)) {
            // Prepare arguments (two numbers)
            PyObject* pArgs = PyTuple_New(2);

            // Convert C++ integers to Python objects
            PyObject* pValue1 = PyLong_FromLong(num1);
            PyObject* pValue2 = PyLong_FromLong(num2);

            if (!pValue1 || !pValue2) {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                throw std::runtime_error("Cannot convert arguments to Python objects");
            }

            // Set the arguments in the tuple
            PyTuple_SetItem(pArgs, 0, pValue1); // Note: PyTuple_SetItem steals a reference
            PyTuple_SetItem(pArgs, 1, pValue2);

            // Call the function
            PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pResult != nullptr) {
                // Function returned successfully
                // Process the result
                if (PyLong_Check(pResult)) {
                    long result = PyLong_AsLong(pResult);
                    std::cout << "Result of addition: " << result << std::endl;
                } else if (PyFloat_Check(pResult)) {
                    double result = PyFloat_AsDouble(pResult);
                    std::cout << "Result of addition: " << result << std::endl;
                } else {
                    std::cout << "Function did not return a number" << std::endl;
                }
                Py_DECREF(pResult);
            } else {
                // An exception occurred
                if (PyErr_Occurred()) {
                    PyErr_Print(); // Print the exception details to stderr
                }
                throw std::runtime_error("Error occurred while calling the function");
            }
            Py_DECREF(pFunc);
        } else {
            if (PyErr_Occurred()) {
                PyErr_Print();
            }
            Py_DECREF(pModule);
            throw std::runtime_error("Cannot find function 'add_numbers'");
        }
        Py_DECREF(pModule);
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    // Finalize the Python Interpreter
    Py_Finalize();

    return 0;
}
