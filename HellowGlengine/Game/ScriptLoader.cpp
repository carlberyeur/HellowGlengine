#include "stdafx.h"
#include "ScriptLoader.h"

#include "../PythonWrapper/HelperMacros.h"

//declaring a c function for python
PyObject* PythonExtension(PyObject* aSelf, PyObject* aArgs);
DEFINE_PYTHON_FUNCTION(pyExt, PythonExtension);

//declaring a module for python, sending in c-functions as variadic args
DEFINE_PYTHON_MODULE(wendy, pyExt);


namespace ScriptLoader
{
	void InitPythonModules()
	{
		//add declared module to python's module collection
		APPEND_MODULE_INIT_TAB(wendy);
	}
}

//definision of c-function declared above
#include <iostream>
PyObject* PythonExtension(PyObject* /*aSelf*/, PyObject* aArgs)
{
	const char* strarg = nullptr;
	PyArg_ParseTuple(aArgs, "s", &strarg);
	PyErr_Print();
	std::cout << "in c function" << std::endl;

	Py_RETURN_NONE;
}
