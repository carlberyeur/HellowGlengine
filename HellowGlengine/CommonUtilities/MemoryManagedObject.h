#pragma once

#include "GrowingArray.h"

namespace CU
{
	class IMemoryManagedObject
	{
	public:
		static void CollectGarbage();
		static void CollectRemainingGarbage();

		IMemoryManagedObject();
		virtual ~IMemoryManagedObject();

		void AddRef();
		void DecRef();

	private:
		short myRefCount;

		static GrowingArray<IMemoryManagedObject*> ourLiveObjects;
		static GrowingArray<IMemoryManagedObject*> ourDeadObjects;

		static unsigned int ourHighestLiveObjects;
	};
}
