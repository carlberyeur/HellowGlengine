#include "stdafx.h"

CPythonTuple::CPythonTuple()
	: myTupleObject(nullptr)
{
}

CPythonTuple::CPythonTuple(const CPythonTuple& aCopy)
	: myTupleObject(aCopy.myTupleObject)
{
	Py_XINCREF(myTupleObject);
}

CPythonTuple::CPythonTuple(CPythonTuple&& aTemporary)
	: myTupleObject(aTemporary.myTupleObject)
{
	aTemporary.myTupleObject = nullptr;
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

template<>
int CPythonTuple::At<int>(const int aIndex) const
{
	int integer = INT_MIN;

	if (PyTuple_Check(myTupleObject) && aIndex >= 0 && aIndex < Size())
	{
		PyObject* pyInt = PyTuple_GetItem(myTupleObject, static_cast<Py_ssize_t>(aIndex));

		if (PyLong_Check(pyInt))
		{
			integer = PyLong_AsLong(pyInt);
		}
	}

	return integer;
}

template<>
double CPythonTuple::At<double>(const int aIndex) const
{
	double integer = INFINITY;
	
	if (PyTuple_Check(myTupleObject) && aIndex >= 0 && aIndex < Size())
	{
		PyObject* pyFloat = PyTuple_GetItem(myTupleObject, static_cast<Py_ssize_t>(aIndex));

		if (PyFloat_Check(pyFloat))
		{
			integer = PyFloat_AsDouble(pyFloat);
		}
	}

	return integer;
}

template<>
float CPythonTuple::At<float>(const int aIndex) const
{
	return static_cast<float>(At<double>(aIndex));
}

int CPythonTuple::Size() const
{
	if (PyTuple_Check(myTupleObject))
	{
		Py_ssize_t size = PyTuple_Size(myTupleObject);
		return static_cast<int>(size);
	}

	return 0;
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
