#include "stdafx.h"

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif // _DEBUG
#include <iostream>
#include "PythonWrapper.h"

//static PyModuleDef pythonExtensionMod;

bool ReadFile(const std::string& aFilePath, std::string& aFileContent);
void AddSearchPath(const std::string& aPathToAppendFrom, const std::string& aPathToAppend);

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

int wmain(int argc, wchar_t* argv[])
{
	CPythonWrapper pythonWrapper(argv[0], InitPyModules);

	PyObject* name = PyUnicode_FromString("bronto_test");
	
	PyErr_Print();
	PyObject* module = PyImport_Import(name);

	PyObject* function = PyObject_GetAttrString(module, "greetings");
	if (PyCallable_Check(function))
	{
		PyObject_CallObject(function, nullptr);
	}
	

	Py_Finalize();
	system("pause");
	return 0;
}

PyObject* PythonExtension(PyObject * aSelf, PyObject * aArgs)
{
	std::cout << "in c function" << std::endl;
	return nullptr;
}

PyObject* PyInit_bronto()
{
	return PyModule_Create(&pythonExtensionMod);
}

bool ReadFile(const std::string& aFilePath, std::string& aFileContent)
{
	std::ifstream newFile(aFilePath);
	if (!newFile.good())
	{
		return false;
	}

	std::stringstream fileStream;
	fileStream << newFile.rdbuf();
	aFileContent = fileStream.str();

	return true;
}

void AddSearchPath(const std::string& aPathToAppendFrom, const std::string& aPathToAppend)
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
