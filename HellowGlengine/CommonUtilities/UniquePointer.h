#pragma once

#ifndef assert
#include <cassert>
#endif // !assert

namespace CU
{
	template<typename ObjectType>
	struct DefaultDeleter
	{
		static void Destroy(ObjectType*& aObject)
		{
			delete aObject;
			aObject = nullptr;
		}
	};

	template <typename ObjectType, typename Deleter = DefaultDeleter<ObjectType>>
	class UniquePointer
	{
	public:
		UniquePointer();
		UniquePointer(ObjectType* aObject);
		UniquePointer(UniquePointer&& aTemporary);
		UniquePointer(const UniquePointer& aCopy) = delete;
		~UniquePointer();

		UniquePointer& operator=(ObjectType* aObject);
		UniquePointer& operator=(UniquePointer&& aTemporary);
		UniquePointer& operator=(const UniquePointer& aCopy) = delete;

		inline ObjectType& operator*() const;
		inline ObjectType* operator->() const;
		inline ObjectType* GetRawPointer();

		inline bool operator!() const;
		inline bool operator==(const ObjectType* aObject) const;
		inline bool operator==(const UniquePointer& aSmartPointer) const;
		inline bool IsValid() const;

	private:
		void Destroy();

		ObjectType* myObject;
	};

	template <typename ObjectType, typename Deleter>
	UniquePointer<ObjectType, Deleter>::UniquePointer()
		: myObject(nullptr)
	{
	}

	template <typename ObjectType, typename Deleter>
	UniquePointer<ObjectType, Deleter>::UniquePointer(ObjectType* aObject)
		: UniquePointer()
	{
		*this = aObject;
	}

	template<typename ObjectType, typename Deleter>
	UniquePointer<ObjectType, Deleter>::UniquePointer(UniquePointer&& aTemporary)
	{
		*this = std::move(aSmartPointer);
	}

	template <typename ObjectType, typename Deleter>
	UniquePointer<ObjectType, Deleter>::~UniquePointer()
	{
		Destroy();
	}

	template <typename ObjectType, typename Deleter>
	inline UniquePointer<ObjectType, Deleter>& UniquePointer<ObjectType, Deleter>::operator=(ObjectType* aObject)
	{
		Destroy();
		myObject = aObject;

		return *this;
	}

	template<typename ObjectType, typename Deleter>
	inline UniquePointer<ObjectType, Deleter>& UniquePointer<ObjectType, Deleter>::operator=(UniquePointer&& aTemporary)
	{
		Destroy();
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
	inline void UniquePointer<ObjectType, Deleter>::Destroy()
	{
		Deleter::Destroy(myObject);
	}
}
