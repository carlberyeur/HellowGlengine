#pragma once

typedef struct _object PyObject;

class CPythonTuple
{
public:
	friend class CPythonList;
	friend class CPythonFunction;

	CPythonTuple();
	CPythonTuple(const CPythonTuple& aCopy);
	CPythonTuple(CPythonTuple&& aTemporary);
	~CPythonTuple();

	CPythonTuple& operator=(const CPythonTuple& aCopy);
	CPythonTuple& operator=(CPythonTuple&& aTemporary);

	template<typename T>
	T At(const int aIndex) const;

	int Size() const;

private:
	CPythonTuple(const CPythonList& aPythonList);
	CPythonTuple(PyObject* aTupleObject);

	PyObject* myTupleObject;
};
