#include "stdafx.h"
#include "PythonModule.h"
#include "PythonFunction.h"

#define DIS (*this)

CPythonModule::CPythonModule()
	: myModuleObject(nullptr)
{
}

CPythonModule::CPythonModule(const CPythonModule& aCopy)
{
	DIS = aCopy;
}

CPythonModule::CPythonModule(CPythonModule&& aTemporary)
{
	DIS = std::move(aTemporary);
}

CPythonModule::~CPythonModule()
{
	Py_XDECREF(myModuleObject);
}

void CPythonModule::Init(PyObject* aModuleObject)
{
	Py_XDECREF(myModuleObject);
	myModuleObject = aModuleObject;
}

CPythonModule CPythonModule::operator=(const CPythonModule& aCopy)
{
	Py_XDECREF(myModuleObject);
	myModuleObject = aCopy.myModuleObject;
	Py_XINCREF(myModuleObject);

	return DIS;
}

CPythonModule CPythonModule::operator=(CPythonModule&& aTemporary)
{
	Py_XDECREF(myModuleObject);
	myModuleObject = aTemporary.myModuleObject;
	aTemporary.myModuleObject = nullptr;

	return DIS;
}

bool CPythonModule::HasAttribute(const std::string& aAttributeName) const
{
	return PyObject_HasAttrString(myModuleObject, aAttributeName.c_str()) == 1;
}

bool CPythonModule::GetFunction(const std::string& aFunctionName, CPythonFunction& aFunctionOut)
{
	bool result = false;
	PyObject* function = PyObject_GetAttrString(myModuleObject, aFunctionName.c_str());
	if (function && PyFunction_Check(function))
	{
		aFunctionOut.Init(function);
		result = true;
	}

	Py_XDECREF(function);
	return result;
}
