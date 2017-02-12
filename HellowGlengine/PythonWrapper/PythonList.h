#pragma once

typedef struct _object PyObject;

class CPythonList
{
public:
	friend class CPythonTuple;

	CPythonList();
	CPythonList(const CPythonList& aCopy);
	CPythonList(CPythonList&& aTemporary);
	~CPythonList();

	CPythonList& operator=(const CPythonList& aCopy);
	CPythonList& operator=(CPythonList&& aTemporary);

	bool Init();

	class CPythonTuple AsTuple() const;

	template<typename T>
	bool Append(const T& aValue);

	template<typename First, typename... Args>
	bool Append(const First aFirst, const Args&... aRest);

private:
	PyObject* myListObject;
};

template<typename First, typename... Args>
bool CPythonList::Append(const First aFirst, const Args&... aRest)
{
	if (!Append(aFirst))
	{
		return false;
	}

	return Append(aRest...);
}
