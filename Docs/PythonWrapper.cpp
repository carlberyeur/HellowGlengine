#include "stdafx.h"
#include "PythonWrapper.h"
#include "PythonModule.h"

//#ifdef _DEBUG
//#undef _DEBUG
//#include <Python.h>
//#define _DEBUG
//#else
//#include <Python.h>
//#endif // _DEBUG

std::string CPythonWrapper::ourLastError;

CPythonWrapper::CPythonWrapper(wchar_t* aArgv0, const std::function<void()>& aInitModulesFunction)
{
	Py_SetProgramName(aArgv0);

	if (aInitModulesFunction != nullptr)
	{
		aInitModulesFunction();
	}

	Py_Initialize();

	AddSearchPath("Bin", "Scripts");
}

CPythonWrapper::~CPythonWrapper()
{
	Py_Finalize();
}

void CPythonWrapper::AddSearchPath(const std::string& aPathToAppendFrom, const std::string& aPathToAppend)
{
	std::string pythonCode;
	pythonCode.reserve(1024u);

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
	PyObject* name = PyUnicode_FromString("bronto_test");
	
	PyObject* module = PyImport_Import(name);

	aModuleOut.Init(module);
	
	return module != nullptr && !HasError();
}

const std::string& CPythonWrapper::GetLastError()
{
	return ourLastError;
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
