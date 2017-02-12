#include "stdafx.h"
#include "MemoryManagedObject.h"

namespace CU
{
	GrowingArray<IMemoryManagedObject*> IMemoryManagedObject::ourLiveObjects(32);
	GrowingArray<IMemoryManagedObject*> IMemoryManagedObject::ourDeadObjects(32);

	void IMemoryManagedObject::CollectGarbage()
	{
		ourDeadObjects.DeleteAll();
	}

	void IMemoryManagedObject::CollectRemainingGarbage()
	{
		if (!ourLiveObjects.Empty())
		{
			MEMORY_LOG("Garbage Collection: %u memory managed objects not deleted", ourLiveObjects.Size());
			DL_DEBUG_ASSERT("Garbage Collection: %u memory managed objects not deleted", ourLiveObjects.Size());
		}

		ourLiveObjects.DeleteAll();
	}

	IMemoryManagedObject::IMemoryManagedObject()
		: myRefCount(1)
	{
		ourLiveObjects.Add(this);
	}

	IMemoryManagedObject::~IMemoryManagedObject()
	{
		assert(myRefCount == 0u && "Memory managed object destroyed with bad refcount");
	}

	void IMemoryManagedObject::AddRef()
	{
		++myRefCount;
	}

	void IMemoryManagedObject::DecRef()
	{
		--myRefCount;

		if (myRefCount <= 0)
		{
			ourLiveObjects.RemoveCyclic(this);
			ourDeadObjects.Add(this);
		}
	}
}