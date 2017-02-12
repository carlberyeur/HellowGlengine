#pragma once

#ifndef assert
#include <cassert>
#endif // !assert

namespace CommonUtilities
{
	template <typename T>
	class SmartPointer
	{
	public:
		inline SmartPointer();
		inline SmartPointer(T* aObject);
		inline SmartPointer(const SmartPointer& aSmartPointer);
		~SmartPointer();

		SmartPointer& operator=(T* aObject);
		SmartPointer& operator=(const SmartPointer& aSmartPointer);

		inline T& operator*() const;
		inline T* operator->() const;
		inline T* GetRawPointer();

		inline bool operator!() const;
		inline bool operator==(const T* aObject) const;
		inline bool operator==(const SmartPointer& aSmartPointer) const;
		inline bool IsValid() const;

	private:
		T* myObject;
	};

	template <typename T>
	inline SmartPointer<T>::SmartPointer()
	{
		myObject = nullptr;
	}

	template <typename T>
	inline SmartPointer<T>::SmartPointer(T* aObject)
		: SmartPointer()
	{
		*this = aObject;
	}

	template <typename T>
	inline SmartPointer<T>::SmartPointer(const SmartPointer& aSmartPointer)
		: SmartPointer()
	{
		*this = aSmartPointer;
	}

	template <typename T>
	inline SmartPointer<T>::~SmartPointer()
	{
		if (myObject != nullptr)
		{
			myObject->DecRef();
		}
	}

	template <typename T>
	inline SmartPointer<T>& SmartPointer<T>::operator=(T* aObject)
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

	template <typename T>
	inline SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& aSmartPointer)
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
	inline T& SmartPointer<T>::operator*() const
	{
		assert(myObject != nullptr && "Tried to dereference null smart pointer");
		return *myObject;
	}

	template <typename T>
	inline T* SmartPointer<T>::operator->() const
	{
		assert(myObject != nullptr && "Tried to dereference null smart pointer");
		return myObject;
	}

	template<typename T>
	inline T* SmartPointer<T>::GetRawPointer()
	{
		return myObject;
	}

	template <typename T>
	inline bool SmartPointer<T>::operator!() const
	{
		return !myObject;
	}

	template <typename T>
	inline bool SmartPointer<T>::operator==(const T* aObject) const
	{
		return myObject == aObject;
	}

	template <typename T>
	inline bool SmartPointer<T>::operator==(const SmartPointer& aSmartPointer) const
	{
		return myObject == aSmartPointer.myObject;
	}

	template <typename T>
	inline bool SmartPointer<T>::IsValid() const
	{
		return myObject != nullptr;
	}
}
