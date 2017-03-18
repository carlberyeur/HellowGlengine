#pragma once

#ifndef assert
#include <cassert>
#endif // !assert

namespace CU
{
	template<typename ObjectType>
	struct DefaultDeleter
	{
		__forceinline static void Destroy(ObjectType* aObject)
		{
			delete aObject;
		}
	};

	template <typename ObjectType, typename Deleter = DefaultDeleter<ObjectType>>
	class UniquePointer
	{
	public:
		template <typename AnyType, typename AnyDeleter>
		friend class UniquePointer;

		UniquePointer();
		UniquePointer(ObjectType* aObject);
		UniquePointer(UniquePointer&& aTemporary);
		UniquePointer(const UniquePointer& aCopy) = delete;
		~UniquePointer();

		__forceinline UniquePointer& operator=(UniquePointer&& aTemporary);
		template <typename Derived, typename DerivedDeleter>
		__forceinline UniquePointer& operator=(UniquePointer<Derived, DerivedDeleter>&& aTemporary);

		UniquePointer& operator=(const UniquePointer& aCopy) = delete;

		inline ObjectType& operator*() const;
		inline ObjectType* operator->() const;
		inline ObjectType* GetRawPointer();

		inline bool operator!() const;
		inline bool operator==(const ObjectType* aObject) const;
		inline bool operator==(const UniquePointer& aSmartPointer) const;
		inline bool IsValid() const;

		inline void SafeDelete();

	private:
		__forceinline void Destroy();

		ObjectType* myObject;
	};

	template <typename ObjectType, typename Deleter>
	UniquePointer<ObjectType, Deleter>::UniquePointer()
		: myObject(nullptr)
	{
	}

	template <typename ObjectType, typename Deleter>
	UniquePointer<ObjectType, Deleter>::UniquePointer(ObjectType* aObject)
		: myObject(aObject)
	{
	}

	template<typename ObjectType, typename Deleter>
	UniquePointer<ObjectType, Deleter>::UniquePointer(UniquePointer&& aTemporary)
		: myObject(aTemporary.myObject)
	{
		aTemporary.myObject = nullptr;
	}

	template <typename ObjectType, typename Deleter>
	UniquePointer<ObjectType, Deleter>::~UniquePointer()
	{
		Destroy();
	}

	template<typename ObjectType, typename Deleter>
	__forceinline UniquePointer<ObjectType, Deleter>& UniquePointer<ObjectType, Deleter>::operator=(UniquePointer&& aTemporary)
	{
		if (myObject)
		{
			Destroy();
		}

		myObject = aTemporary.myObject;
		aTemporary.myObject = nullptr;

		return *this;
	}

	template<typename ObjectType, typename Deleter>
	template<typename Derived, typename DerivedDeleter>
	__forceinline UniquePointer<ObjectType, Deleter>& UniquePointer<ObjectType, Deleter>::operator=(UniquePointer<Derived, DerivedDeleter>&& aTemporary)
	{
		if (myObject)
		{
			Destroy();
		}

		myObject = aTemporary.myObject;
		aTemporary.myObject = nullptr;

		return *this;
	}

	template <typename ObjectType, typename Deleter>
	inline ObjectType& UniquePointer<ObjectType, Deleter>::operator*() const
	{
		assert(myObject != nullptr && "Tried to dereference null smart pointer");
		return *myObject;
	}

	template <typename ObjectType, typename Deleter>
	inline ObjectType* UniquePointer<ObjectType, Deleter>::operator->() const
	{
		assert(myObject != nullptr && "Tried to dereference null smart pointer");
		return myObject;
	}

	template<typename ObjectType, typename Deleter>
	inline ObjectType* UniquePointer<ObjectType, Deleter>::GetRawPointer()
	{
		return myObject;
	}

	template <typename ObjectType, typename Deleter>
	inline bool UniquePointer<ObjectType, Deleter>::operator!() const
	{
		return !myObject;
	}

	template <typename ObjectType, typename Deleter>
	inline bool UniquePointer<ObjectType, Deleter>::operator==(const ObjectType* aObject) const
	{
		return myObject == aObject;
	}

	template <typename ObjectType, typename Deleter>
	inline bool UniquePointer<ObjectType, Deleter>::operator==(const UniquePointer& aSmartPointer) const
	{
		return myObject == aSmartPointer.myObject;
	}

	template <typename ObjectType, typename Deleter>
	inline bool UniquePointer<ObjectType, Deleter>::IsValid() const
	{
		return myObject != nullptr;
	}

	template<typename ObjectType, typename Deleter>
	inline void UniquePointer<ObjectType, Deleter>::SafeDelete()
	{
		if (myObject)
		{
			Destroy();
			myObject = nullptr;
		}
	}

	template <typename ObjectType, typename Deleter>
	__forceinline  void UniquePointer<ObjectType, Deleter>::Destroy()
	{
		Deleter::Destroy(myObject);
	}

	template <typename ObjectType, typename... Args>
	UniquePointer<ObjectType> MakeUnique(Args&&... aArgs)
	{
		return (UniquePointer<ObjectType>(new ObjectType(std::forward<Args>(aArgs)...)));
	}
}
