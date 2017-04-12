#pragma once

namespace CU
{
	union SplitPointer
	{
		SplitPointer(const void* aPointer) : myPointer(aPointer) {}

		const void* myPointer;
		const unsigned int myHalves[2];
		const unsigned short myQuarters[4];
		const unsigned char myEights[8];

		static_assert(sizeof(myPointer) == sizeof(myHalves), "unsigned int is wrong size");
		static_assert(sizeof(myPointer) == sizeof(myQuarters), "unsigned short is wrong size");
		static_assert(sizeof(myPointer) == sizeof(myEights), "unsigned char is wrong size");
	};
}