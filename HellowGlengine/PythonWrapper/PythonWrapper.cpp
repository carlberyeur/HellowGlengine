#include "stdafx.h"

#pragma comment(lib, "../Dependencies/python34/libs/python34.lib")

std::string CPythonWrapper::ourLastError;
CPythonWrapper* CPythonWrapper::ourInstance = nullptr;

CPythonWrapper::CPythonWrapper(wchar_t* aArgv0, const VoidFunction& aInitModulesFunction)
{
	assert(ourInstance == nullptr && "Python wrapper should not be created twice");
	ourInstance = this;

	Py_SetProgramName(aArgv0);

	if (aInitModulesFunction != nullptr)
	{
		aInitModulesFunction();
	}

	Py_Initialize();
	AddSearchPath("Bin", "Scripts/Python");
}

CPythonWrapper::~CPythonWrapper()
{
	assert(ourInstance == this && "Python wrapper should not be created twice");
	ourInstance = nullptr;

	Py_Finalize();
}

void CPythonWrapper::AddSearchPath(const std::string& aPathToAppendFrom, const std::string& aPathToAppend)
{
	std::string pythonCode(1024u, 'p');

	pythonCode =
		"import sys\n"
		"scriptModule = ''\n"
		"for p in sys.path:\n"
		"\t""if p.find('";

	pythonCode += aPathToAppendFrom;

	pythonCode += "') != -1:\n"
		"\t\t""scriptModule = p\n"
		"\t\t""break\n"
		"scriptModule += '\\";

	pythonCode += aPathToAppend;

	pythonCode += "'\n"
		"sys.path.append(scriptModule)\n"

		"for p in sys.path:\n"
		"\tprint(p)\n";

	PyRun_SimpleString(pythonCode.c_str());
}

bool CPythonWrapper::ImportModule(const std::string& aModuleName, CPythonModule& aModuleOut)
{
	if (aModuleName.empty())
	{
		ourLastError = "Tried to import module, got empty name string";
		return false;
	}

	PyObject* name = PyUnicode_FromString(aModuleName.c_str());
	if (!name && HasError())
	{
		return false;
	}

	PyObject* module = PyImport_Import(name);

	aModuleOut.Init(module);
	Py_XDECREF(name);

	return !HasError();
}

bool CPythonWrapper::RunCode(const std::string& aPieceOfCode)
{
	int result = PyRun_SimpleString(aPieceOfCode.c_str());
	if (result == -1)
	{
		if (!HasError())
		{
			ourLastError = "Failed to run code piece: " + aPieceOfCode;
		}

		return false;
	}

	return true;
}

const std::string& CPythonWrapper::GetLastError()
{
	return ourLastError;
}

CPythonWrapper* CPythonWrapper::GetInstance()
{
	return ourInstance;
}

bool CPythonWrapper::IsCreated()
{
	return ourInstance != nullptr;
}

bool CPythonWrapper::HasError()
{
	if (PyErr_Occurred())
	{
		PyObject *errorType, *errorString, *stackTraceBack;
		PyErr_Fetch(&errorType, &errorString, &stackTraceBack);

		if (errorString)
		{
			wchar_t* errorCString = PyUnicode_AsWideCharString(errorString, nullptr);

			if (errorCString)
			{
				std::wstring errorWString(errorCString);
				PyMem_Free(errorCString);
				ourLastError = std::string(errorWString.begin(), errorWString.end());
			}
		}

		Py_XDECREF(errorType);
		Py_XDECREF(errorString);
		Py_XDECREF(stackTraceBack);

		return true;
	}

	return false;
}
