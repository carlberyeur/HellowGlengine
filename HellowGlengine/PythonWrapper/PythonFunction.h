#pragma once

typedef struct _object PyObject;

class CPythonTuple;

class CPythonFunction
{
public:
	friend class CPythonModule;

	CPythonFunction();
	CPythonFunction(const CPythonFunction& aCopy);
	CPythonFunction(CPythonFunction&& aTemporary);
	~CPythonFunction();

	CPythonFunction& operator=(const CPythonFunction& aCopy);
	CPythonFunction& operator=(CPythonFunction&& aTemporary);

	void operator()();
	CPythonTuple operator()(const CPythonTuple& aArguments);

private:
	bool Init(PyObject* aMaybeFunctionObject);

	PyObject* myFunctionObject;
};
