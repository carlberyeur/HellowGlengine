#pragma once

#include <mutex>
#include <cstdint>

const std::uint32_t BufferSize = 512u;

template<typename T, typename SizeType = std::uint32_t>
class CSynchronizer
{
public:
	CSynchronizer();
	CSynchronizer(const CSynchronizer& aCopy) = delete;
	~CSynchronizer();

	inline T At(const SizeType aIndex);
	inline void Write(T aObject);
	inline SizeType ReadSize() const;

	inline T operator[](const SizeType aIndex);
	inline void operator <<(T aObject);
	inline SizeType operator!() const;

	inline void SwapWrite();
	inline void SwapRead();
	inline void ClearWrite();
	inline void ClearAll();

private:
	CU::StaticArray<CU::GrowingArray<T, SizeType>, 3> myBuffers;

	std::mutex mySwapMutex;

	std::uint8_t myWriteTo;
	std::uint8_t myReadFrom;
	std::uint8_t myFreeBuffer;

	volatile bool myHasFresh;
};

template<typename T, typename SizeType>
inline void CSynchronizer<T, SizeType>::ClearAll()
{
	for (char i = 0; i < myBuffers.Size(); ++i)
	{
		myBuffers[i].DeleteAll();
	}
}

template<typename T, typename SizeType>
inline CSynchronizer<T, SizeType>::CSynchronizer()
{
	myBuffers[0].Init(BufferSize);
	myBuffers[1].Init(BufferSize);
	myBuffers[2].Init(BufferSize);

	myWriteTo = 0;
	myReadFrom = 1;
	myFreeBuffer = 2;

	myHasFresh = false;
}

template<typename T, typename SizeType>
inline CSynchronizer<T, SizeType>::~CSynchronizer()
{
	ClearAll();
}

template<typename T, typename SizeType>
inline T CSynchronizer<T, SizeType>::At(const SizeType aIndex)
{
	return myBuffers[myReadFrom][aIndex];
}

template<typename T, typename SizeType>
inline void CSynchronizer<T, SizeType>::Write(T aObject)
{
	myBuffers[myWriteTo].Add(aObject);
}

template<typename T, typename SizeType>
inline SizeType CSynchronizer<T, SizeType>::ReadSize() const
{
	return myBuffers[myReadFrom].Size();
}

template<typename T, typename SizeType>
T CSynchronizer<T, SizeType>::operator[](const SizeType aIndex)
{
	return At(aIndex);
}

template<typename T, typename SizeType>
inline void CSynchronizer<T, SizeType>::operator<<(T aObject)
{
	Write(aObject);
}

template<typename T, typename SizeType>
inline SizeType CSynchronizer<T, SizeType>::operator!() const
{
	return ReadSize();
}

template<typename T, typename SizeType>
inline void CSynchronizer<T, SizeType>::SwapWrite()
{
	mySwapMutex.lock();

	std::uint8_t lastFree = myFreeBuffer;
	myFreeBuffer = myWriteTo;
	myWriteTo = lastFree;

	myHasFresh = true;

	mySwapMutex.unlock();

	ClearWrite();

}

template<typename T, typename SizeType>
inline void CSynchronizer<T, SizeType>::SwapRead()
{
	if (!myHasFresh)
	{
		return;
	}
	
	mySwapMutex.lock();

	myHasFresh = false;

	std::uint8_t lastFree = myFreeBuffer;
	myFreeBuffer = myReadFrom;
	myReadFrom = lastFree;

	mySwapMutex.unlock();
}

template<typename T, typename SizeType>
inline void CSynchronizer<T, SizeType>::ClearWrite()
{
	myBuffers[myWriteTo].DeleteAll();
}
