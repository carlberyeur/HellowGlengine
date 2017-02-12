#include "stdafx.h"
#include "PythonWrapper.h"
#include "PythonModule.h"
#include "PythonFunction.h"

#pragma comment(lib, "../Dependencies/python34/libs/python34.lib")

std::string CPythonWrapper::ourLastError;

PyObject* PythonExtension(PyObject* aSelf, PyObject* aArgs);
PyObject* PyInit_bronto();

#define DECLARE_PYTHON

static PyMethodDef pythonExtensionDef = {
	"PythonExtension",
	PythonExtension,
	METH_VARARGS,
	"Returns nothing"
};
static PyMethodDef methods[1] = { pythonExtensionDef };
static PyModuleDef pythonExtensionMod = {
	PyModuleDef_HEAD_INIT, "bronto", NULL, -1, methods,
	NULL, NULL, NULL, NULL
};

void InitPyModules()
{
	int returnvalue = PyImport_AppendInittab("bronto", &PyInit_bronto);
}

CPythonWrapper::CPythonWrapper(wchar_t* aArgv0, const std::function<void(void)>& aInitModulesFunction)
{
	Py_SetProgramName(aArgv0);

	if (aInitModulesFunction != nullptr)
	{
		aInitModulesFunction();
	}
	InitPyModules();

	Py_Initialize();
	AddSearchPath("Bin", "Scripts");
	AddSearchPath("Scripts", "Python");

	//PyObject* name = PyUnicode_FromString("hello_wendy_program");

	//PyErr_Print();
	//PyObject* module = PyImport_Import(name);
	//PyErr_Print();

	//PyObject* function = PyObject_GetAttrString(module, "hello_wendy");
	//if (PyCallable_Check(function))
	//{
	//	PyObject_CallObject(function, nullptr);
	//}

}

//CPythonWrapper::CPythonWrapper()
//{
//	CommandLineManager<wchar_t>* commandLine = CommandLineManager<wchar_t>::GetInstance();
//
//	Py_SetProgramName(commandLine->GetArgV()[0]);
//	
//	Py_Initialize();
//
//	PyRun_SimpleString("import test1");
//
//	PyObject* twoname = PyUnicode_FromString("test2");
//	PyObject* twomodule = PyImport_Import(twoname);
//	PyObject* function2 = PyObject_GetAttrString(twomodule, "greet");
//	PyObject* name = PyUnicode_FromString("test1");
//	PyObject* module = PyImport_Import(name);
//	PyObject* function = PyObject_GetAttrString(module, "apa2");
//	//PyObject_Repr
//	if (PyCallable_Check(function))
//	{
//		PyObject_CallObject(function, nullptr);
//	}
//	//PyObject_Repr(function);
//	//DL_PRINT("%s", );
//}

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
	PyObject* name = PyUnicode_FromString(aModuleName.c_str());

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

#include <iostream>
PyObject* PythonExtension(PyObject * aSelf, PyObject * aArgs)
{
	std::cout << "in c function" << std::endl;
	return nullptr;
}

PyObject* PyInit_bronto()
{
	return PyModule_Create(&pythonExtensionMod);
}