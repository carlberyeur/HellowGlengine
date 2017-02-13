#pragma once

struct SComponentMessage
{
	SComponentMessage() : myData(), myType(eType::eNone) {}

	union Data
	{
		Data() : myVoidPointer(nullptr) {}

		void* myVoidPointer;

	} myData;

	enum class eType : char
	{
		eCollisionEnter,
		eCollisionExit,
		eNone

	} myType;
};

static_assert(sizeof(SComponentMessage) <= 16u, "If you want to pass data greater than a pointer in a message, pass a pointer");