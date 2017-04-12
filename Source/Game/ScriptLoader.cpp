#include "stdafx.h"
#include "ScriptLoader.h"

#include "../PythonWrapper/HelperMacros.h"

PyObject* GetParent(PyObject* aSelf, PyObject* aArgs);
DEFINE_PYTHON_FUNCTION(ext_GetParent, GetParent);

//declaring a c function for python
PyObject* PythonExtension(PyObject* aSelf, PyObject* aArgs);
DEFINE_PYTHON_FUNCTION(pyExt, PythonExtension);

//declaring a module for python, sending in c-functions as variadic args
DEFINE_PYTHON_MODULE(wendy, pyExt, ext_GetParent);


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

#include "Level.h"
#include "Component.h"
#include "ComponentManager.h"
#include "GameObject.h"
PyObject* GetParent(PyObject* /*aSelf*/, PyObject* aArgs)
{
	int componentID = -1;
	if (!PyArg_ParseTuple(aArgs, "i", &componentID))
	{
		//error
		BREAK_POINT_HERE;
		return PyLong_FromLong(-1);
	}

	CComponentManager* componentManager = CComponentManager::GetInstance();
	if (!componentManager)
	{
		//error
		BREAK_POINT_HERE;
		return PyLong_FromLong(-1);
	}

	IComponent* component = componentManager->GetComponent(componentID);
	if (!component)
	{
		//error
		BREAK_POINT_HERE;
		return PyLong_FromLong(-1);
	}

	int parentID = component->GetParentID();

	return PyLong_FromLong(parentID);
}
