#pragma once

namespace CU
{
	template <int SIZE, typename T>
	class CMemoryBlob
	{
	public:
		CMemoryBlob();
		~CMemoryBlob();

		inline void* GetAddress();
		inline constexpr int Size() const;

		//inline static T* New();
		//inline static void Delete(T* aObject);

	private:
		char myMemoryChunk[SIZE];
	};

	template<int SIZE, typename T>
	inline CMemoryBlob<SIZE, T>::CMemoryBlob()
	{
		static_assert(SIZE == sizeof(T), "Wrong size on memory chunk");
	}

	template<int SIZE, typename T>
	inline CMemoryBlob<SIZE, T>::~CMemoryBlob()
	{
	}

	template<int SIZE, typename T>
	inline void* CMemoryBlob<SIZE, T>::GetAddress()
	{
		return myMemoryChunk;
	}

	template<int SIZE, typename T>
	inline constexpr int CMemoryBlob<SIZE, T>::Size() const
	{
		return SIZE;
	}
}
