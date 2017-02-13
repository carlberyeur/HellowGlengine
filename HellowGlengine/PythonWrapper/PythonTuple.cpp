#include "stdafx.h"

CPythonTuple::CPythonTuple()
	: myTupleObject(nullptr)
{
}

CPythonTuple::CPythonTuple(const CPythonTuple& aCopy)
	: CPythonTuple()
{
	*this = aCopy;
}

CPythonTuple::CPythonTuple(CPythonTuple&& aTemporary)
	: CPythonTuple()
{
	*this = std::move(aTemporary);
}

CPythonTuple::~CPythonTuple()
{
	Py_XDECREF(myTupleObject);
}

CPythonTuple& CPythonTuple::operator=(const CPythonTuple& aCopy)
{
	Py_XDECREF(myTupleObject);
	myTupleObject = aCopy.myTupleObject;
	Py_XINCREF(myTupleObject);

	return *this;
}

CPythonTuple& CPythonTuple::operator=(CPythonTuple&& aTemporary)
{
	Py_XDECREF(myTupleObject);
	myTupleObject = aTemporary.myTupleObject;
	aTemporary.myTupleObject = nullptr;

	return *this;
}

CPythonTuple::CPythonTuple(const CPythonList& aPythonList)
{
	PyObject* newTuple = PyList_AsTuple(aPythonList.myListObject);

	myTupleObject = newTuple;
}

CPythonTuple::CPythonTuple(PyObject* aTupleObject)
	: myTupleObject(aTupleObject)
{
}
