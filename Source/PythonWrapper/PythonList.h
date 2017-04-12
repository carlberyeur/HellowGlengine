#pragma once

typedef struct _object PyObject;

class CPythonList
{
public:
	friend class CPythonTuple;
	friend class ItemRef;

	template<typename T>
	class ItemRef
	{
	public:
		ItemRef(CPythonList& aList, const int aIndex) : myList(aList), myIndex(aIndex) {}
		~ItemRef() {}

		void operator=(const T& aValue);
		operator T() { return const_cast<const CPythonList&>(myList).At(myIndex); }

	private:
		CPythonList& myList;
		int myIndex;
	};

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

	template<typename T>
	T At(const int aIndex) const;

	template<typename T>
	ItemRef<T> At(const int aIndex);

	int Size() const;

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
