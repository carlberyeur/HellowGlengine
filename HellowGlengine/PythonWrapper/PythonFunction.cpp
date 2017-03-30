#include "stdafx.h"

CPythonFunction::CPythonFunction()
	: myFunctionObject(nullptr)
{
}

CPythonFunction::CPythonFunction(const CPythonFunction& aCopy)
	: CPythonFunction()
{
	*this = aCopy;
}

CPythonFunction::CPythonFunction(CPythonFunction&& aTemporary)
	: CPythonFunction()
{
	*this = std::move(aTemporary);
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

	return *this;
}

CPythonFunction& CPythonFunction::operator=(CPythonFunction&& aTemporary)
{
	Py_XDECREF(myFunctionObject);
	myFunctionObject = aTemporary.myFunctionObject;
	aTemporary.myFunctionObject = nullptr;

	return *this;
}

//void CPythonFunction::operator()()
//{
//	if (PyCallable_Check(myFunctionObject))
//	{
//		PyObject_CallObject(myFunctionObject, nullptr);
//	}
//}

CPythonTuple CPythonFunction::operator()(const CPythonTuple& aArguments)
{
	if (PyCallable_Check(myFunctionObject))
	{
		PyObject* args = aArguments.myTupleObject;
		PyObject* returnValue = PyObject_CallObject(myFunctionObject, args);
		if (!returnValue)
		{
			PyErr_Print();
		}
		return CPythonTuple(returnValue);
	}

	return CPythonTuple();
}

bool CPythonFunction::Init(PyObject* aMaybeFunctionObject)
{
	Py_CLEAR(myFunctionObject);

	if (PyCallable_Check(aMaybeFunctionObject))
	{
		myFunctionObject = aMaybeFunctionObject;
		Py_INCREF(myFunctionObject);
		return true;
	}

	return false;
}

//template<>
//inline void CPythonFunction::BuildArgument<int>(CPythonList& aList, const int& aLonely)
//{
//	aList.Append(aLonely);
//}
//
//template<>
//inline void CPythonFunction::BuildArgument<float>(CPythonList& aList, const float& aLonely)
//{
//}
//
//template<>
//inline void CPythonFunction::BuildArgument<std::string>(CPythonList & aList, const std::string& aLonely)
//{
//}

