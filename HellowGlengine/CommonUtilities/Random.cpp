#include "stdafx.h"
#include "Random.h"

#include <random>

float CU::RandomFloat(const float aLowest, const float aHighest)
{
	assert(aLowest <= aHighest);

	int lowest = static_cast<int>(aLowest);
	int highest = static_cast<int>(aHighest);
	int range = lowest - highest;

	int base = std::rand();
	base %= range;
	base += lowest;

	float baseF = static_cast<float>(base);

	return baseF;
}
