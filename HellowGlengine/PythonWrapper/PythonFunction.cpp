#include "stdafx.h"
#include "PythonFunction.h"
#include "PythonTuple.h"

#define mememe (*this)

CPythonFunction::CPythonFunction()
	: myFunctionObject(nullptr)
{
}

CPythonFunction::CPythonFunction(const CPythonFunction& aCopy)
	: CPythonFunction()
{
	mememe = aCopy;
}

CPythonFunction::CPythonFunction(CPythonFunction&& aTemporary)
	: CPythonFunction()
{
	mememe = std::move(aTemporary);
}

CPythonFunction::~CPythonFunction()
{
	Py_XDECREF(myFunctionObject);
}

CPythonFunction& CPythonFunction::operator=(const CPythonFunction& aCopy)
{
	Py_XDECREF(myFunctionObject);
	myFunctionObject = aCopy.myFunctionObject;
	Py_XINCREF(myFunctionObject);

	return mememe;
}

CPythonFunction& CPythonFunction::operator=(CPythonFunction&& aTemporary)
{
	Py_XDECREF(myFunctionObject);
	myFunctionObject = aTemporary.myFunctionObject;
	aTemporary.myFunctionObject = nullptr;

	return mememe;
}

void CPythonFunction::operator()()
{
	if (/*myFunctionObject &&*/ PyCallable_Check(myFunctionObject))
	{
		PyObject* args = Py_BuildValue("(l)", 23456);
		PyObject_CallObject(myFunctionObject, args);
	}
}

CPythonTuple CPythonFunction::operator()(const CPythonTuple& aArguments)
{
	if (/*myFunctionObject &&*/ PyCallable_Check(myFunctionObject))
	{
		PyObject* args = aArguments.myTupleObject;
		PyObject* returnValue = PyObject_CallObject(myFunctionObject, args);
		return CPythonTuple(returnValue);
	}

	return CPythonTuple();
}

bool CPythonFunction::Init(PyObject* aMaybeFunctionObject)
{
	if (!aMaybeFunctionObject) return false;

	Py_XDECREF(myFunctionObject);
	if (PyCallable_Check(aMaybeFunctionObject))
	{
		myFunctionObject = aMaybeFunctionObject;
		Py_INCREF(myFunctionObject);
	}

	return false;
}
