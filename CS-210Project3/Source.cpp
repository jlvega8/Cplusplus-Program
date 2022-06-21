#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:#
		To call this function, simply pass the function name in Python that you wish to call.
Example:
		callProcedure("printsomething");
Output:
		python will print on the screen: Hello from python!
Return:
		None
*/
void CallProcedure(string pName) 
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonFile");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
		To call this function, pass the name of the python function you wish to call and the string parameter you want to send
Example:
		int x = callIntFunc("PrintMe","Test");
Output:
		Python will print on the screen:
				You sent me: Test
Return:
		100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());

	PyObject * pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonFile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

/*
Description:
		To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
		int x = callIntFunc("doublevalue",5);
Return: 
		25 is returned to the C++ 
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonFile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else 
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void Menu() {
	/*
	This will print a menu to the console and give the user 4 options
	The do while will continue untill user exits program
	*/

	bool program_Run = true;
	bool correct_Input;
	int user_Choice;
	string grocery_Type;


	do {

		cout << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << "|||                      Please Select an Option                           |||" << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << endl;
		cout << "1. Print List of All Purchased Items and How Many Were purchased" << endl;
		cout << "2. Print Total Amount Purchased of a Specific Item" << endl;
		cout << "3. Display Text Histogram" << endl;
		cout << "4. Exit Program" << endl;
		cout << endl;

		try {
			std::cin >> user_Choice;
			cout << "|||||||||||||||||||||||||||||||||||||||" << endl;
			cout << endl;

			while (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(256, '\n');
				cout << "Unkown entry. Please Try Agian." << endl;

				cout << "Please enter 1, 2, 3, or 4" << endl;
				std::cin >> user_Choice;
				cout << "|||||||||||||||||||||||||||||||||||||||" << endl;
				cout << endl;
			}
			if (user_Choice >= 0) {
				// Passes the try test 
				// Makes sure the user entered a Positive integer
				correct_Input = true;
			}
			else { throw (user_Choice); }
		}
		catch (...) { cout << "Please Enter only 1, 2, 3, or 4" << endl; }

		if (user_Choice == 1) {

			system("Color 0D");

			cout << endl;
			cout << "###################################" << endl;
			cout << "#  Total Produce Purchased Today  #" << endl;
			cout << "###################################" << endl;
			cout << endl;

			CallProcedure("read_File"); //reads file in python 
		}
		else if (user_Choice == 2) {

			system("Color 03");
			string userString;
			cout << "Please Enter the Product you wish to look up: ";
			std::cin >> userString;

			int tot = callIntFunc("locate_Total_Product_Amount", userString); // gets frequency of chosen user itemproduct

			if (tot == 1) {
				cout << "The item could not be located within the data file. Make sure input is correct" << endl;
			}
			else {
				cout << "There were a total of " << tot << " " << userString << " sold today." << endl;
			}
		}
		else if (user_Choice == 3) {
			// calls python function that will read a file 
			// write it to a .dat file 
			system("Color 06");
			CallProcedure("read_AND_Write_File");
		}
		else { program_Run = false; system("Color 04"); }

	} while (program_Run == true);  //controls program flow 
}

int main()
{

	system("Color 03");

	// starter code 
	CallProcedure("printsomething");
	cout << callIntFunc("PrintMe", "House") << endl;
	cout << callIntFunc("SquareValue", 2);

	// calls menu for main functionality of the program
	Menu();

	// Message when user exits program
	cout << endl;
	cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "|||         Program Shutting Down        |||" << endl;
	cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;

	return 0;
}

