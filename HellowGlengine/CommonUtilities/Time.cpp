#include "stdafx.h"
#include "Time.h"

#define self (*this)

namespace CU
{
	Time::Time()
		: myMicroSeconds(0.f)
	{
	}

	Time::Time(const Time& aRight)
		: myMicroSeconds(aRight.myMicroSeconds)
	{
	}

	Time::Time(const float aMicroSeconds)
		: myMicroSeconds(aMicroSeconds)
	{
	}

	Time::~Time()
	{
	}

	Time& Time::operator=(const float aMicroSeconds)
	{
		myMicroSeconds = aMicroSeconds;
		return self;
	}

	Time& Time::operator=(const Time& aRight)
	{
		myMicroSeconds = aRight.myMicroSeconds;
		return self;
	}

	Time& Time::operator+=(const Time& aRight)
	{
		myMicroSeconds += aRight.myMicroSeconds;
		return self;
	}

	Time& Time::operator-=(const Time& aRight)
	{
		myMicroSeconds -= aRight.myMicroSeconds;
		return self;
	}

	Time Time::operator+(const Time& aRight) const
	{
		return Time(self) += aRight;
	}

	Time Time::operator-(const Time& aRight) const
	{
		return Time(self) -= aRight;
	}
}