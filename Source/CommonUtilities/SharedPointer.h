#pragma once

#ifndef assert
#include <cassert>
#endif // !assert

namespace CU
{
	template <typename T>
	class SharedPointer
	{
	public:
		SharedPointer();
		SharedPointer(T* aObject);
		SharedPointer(SharedPointer&& aTemporary);
		SharedPointer(const SharedPointer& aSmartPointer);
		~SharedPointer();

		SharedPointer& operator=(T* aObject);
		SharedPointer& operator=(SharedPointer&& aTemporary);
		SharedPointer& operator=(const SharedPointer& aSmartPointer);

		inline T& operator*() const;
		inline T* operator->() const;
		inline T* GetRawPointer();

		inline bool operator!() const;
		inline bool operator==(const T* aObject) const;
		inline bool operator==(const SharedPointer& aSmartPointer) const;
		inline bool IsValid() const;

	private:
		T* myObject;
	};

	template <typename T>
	SharedPointer<T>::SharedPointer()
		: myObject(nullptr)
	{
	}

	template <typename T>
	SharedPointer<T>::SharedPointer(T* aObject)
		: SharedPointer()
	{
		*this = aObject;
	}

	template<typename T>
	inline SharedPointer<T>::SharedPointer(SharedPointer && aTemporary)
		: myObject(aTemporary.myObject)
	{
		aTemporary.myObject = nullptr;
	}

	template <typename T>
	SharedPointer<T>::SharedPointer(const SharedPointer& aSmartPointer)
		: SharedPointer()
	{
		*this = aSmartPointer;
	}

	template <typename T>
	SharedPointer<T>::~SharedPointer()
	{
		if (myObject != nullptr)
		{
			myObject->DecRef();
		}
	}

	template <typename T>
	inline SharedPointer<T>& SharedPointer<T>::operator=(T* aObject)
	{
		if (myObject != nullptr)
		{
			myObject->DecRef();
		}
		myObject = aObject;
		if (myObject != nullptr)
		{
			myObject->AddRef();
		}

		return *this;
	}

	template<typename T>
	inline SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer&& aTemporary)
	{
		if (myObject != nullptr)
		{
			myObject->DecRef();
		}

		myObject = aTemporary.myObject;
		aTemporary.myObject = nullptr;

		return *this;
	}

	template <typename T>
	inline SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer& aSmartPointer)
	{
		if (myObject != nullptr)
		{
			myObject->DecRef();
		}
		myObject = aSmartPointer.myObject;
		if (myObject != nullptr)
		{
			myObject->AddRef();
		}

		return *this;
	}

	template <typename T>
	inline T& SharedPointer<T>::operator*() const
	{
		assert(myObject != nullptr && "Tried to dereference null smart pointer");
		return *myObject;
	}

	template <typename T>
	inline T* SharedPointer<T>::operator->() const
	{
		assert(myObject != nullptr && "Tried to dereference null smart pointer");
		return myObject;
	}

	template<typename T>
	inline T* SharedPointer<T>::GetRawPointer()
	{
		return myObject;
	}

	template <typename T>
	inline bool SharedPointer<T>::operator!() const
	{
		return !myObject;
	}

	template <typename T>
	inline bool SharedPointer<T>::operator==(const T* aObject) const
	{
		return myObject == aObject;
	}

	template <typename T>
	inline bool SharedPointer<T>::operator==(const SharedPointer& aSmartPointer) const
	{
		return myObject == aSmartPointer.myObject;
	}

	template <typename T>
	inline bool SharedPointer<T>::IsValid() const
	{
		return myObject != nullptr;
	}
}
