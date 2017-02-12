#include "stdafx.h"
#include "PythonList.h"
#include "PythonTuple.h"


CPythonList::CPythonList()
	: myListObject(nullptr)
{
}

CPythonList::CPythonList(const CPythonList& aCopy)
	: CPythonList()
{
	*this = aCopy;
}

CPythonList::CPythonList(CPythonList&& aTemporary)
	: CPythonList()
{
	*this = std::move(aTemporary);
}

CPythonList::~CPythonList()
{
	Py_XDECREF(myListObject);
}

CPythonList& CPythonList::operator=(const CPythonList& aCopy)
{
	Py_XDECREF(myListObject);
	myListObject = aCopy.myListObject;
	Py_XINCREF(myListObject);

	return *this;
}

CPythonList& CPythonList::operator=(CPythonList&& aTemporary)
{
	Py_XDECREF(myListObject);
	myListObject = aTemporary.myListObject;
	aTemporary.myListObject = nullptr;

	return *this;
}

bool CPythonList::Init()
{
	myListObject = PyList_New(0);
	return myListObject != nullptr;
}

CPythonTuple CPythonList::AsTuple() const
{
	return CPythonTuple(*this);
}

template<>
bool CPythonList::Append<std::string>(const std::string& aValue)
{
	//insert error checking
	PyObject* str = Py_BuildValue("s", aValue.c_str());
	PyList_Append(myListObject, str);
	return true;
}

template<>
bool CPythonList::Append<int>(const int& aValue)
{
	//insert error checking
	PyObject* str = Py_BuildValue("i", aValue);
	PyList_Append(myListObject, str);
	return true;
}
