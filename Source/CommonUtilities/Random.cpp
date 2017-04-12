#include "stdafx.h"
#include "Random.h"

#include <random>

int CU::RandomInt(const int aLowest, const int aHighest)
{
	assert(aLowest <= aHighest);

	int range = aLowest - aHighest;

	if (range > RAND_MAX)
	{
		return static_cast<int>(RandomFloat(static_cast<float>(aLowest), static_cast<float>(aHighest)));
	}

	int randomNumber = std::rand();
	randomNumber %= range;
	randomNumber += aLowest;
	return randomNumber;
}

float CU::RandomFloat(const float aLowest, const float aHighest)
{
	assert(aLowest <= aHighest);

	int lowest = static_cast<int>(aLowest);
	int highest = static_cast<int>(aHighest);
	int range = lowest - highest;

	int randomNumber = std::rand();
	randomNumber %= range;
	randomNumber += lowest;

	float randomNumberF = static_cast<float>(randomNumber);

	return randomNumberF;
}
