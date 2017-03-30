#pragma once

typedef struct _object PyObject;

class CPythonTuple;
class CPythonList;

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

	CPythonTuple operator()(const CPythonTuple& aArguments);

	template<typename... T>
	CPythonTuple operator()(const T&... aArguments);

private:
	bool Init(PyObject* aMaybeFunctionObject);

	PyObject* myFunctionObject;
};

template<typename ...T>
inline CPythonTuple CPythonFunction::operator()(const T&... aArguments)
{
	CPythonList argumentList;
	if (argumentList.Init())
	{
		argumentList.Append(aArguments...);
	}

	CPythonTuple returnValues = (*this)(argumentList);

	return returnValues;
}
