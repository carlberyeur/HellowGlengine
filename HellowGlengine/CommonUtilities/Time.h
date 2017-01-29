#pragma once

namespace CU
{
	struct Hours {};
	struct Minutes {};
	struct Seconds {};
	struct MilliSeconds {};
	struct MicroSeconds {};

	const float THOUSANDTH = 0.001f;
	const float SIXTIETH = 1.f / 60.f;

	class Time
	{
	public:
		Time();
		Time(const Time& aRight);
		Time(const float aMicroSeconds);
		~Time();

		Time& operator=(const float aMilliSeconds);
		Time& operator=(const Time& aRight);

		Time& operator+=(const Time& aRight);
		Time& operator-=(const Time& aRight);

		Time operator+(const Time& aRight) const;
		Time operator-(const Time& aRight) const;

		template <typename T>
		inline float Get();

	private:
		float myMicroSeconds;
	};

	template<>
	inline float Time::Get<MicroSeconds>()
	{
		return myMicroSeconds;
	}

	template<>
	inline float Time::Get<MilliSeconds>()
	{
		return Get<MicroSeconds>() * THOUSANDTH;
	}

	template<>
	inline float Time::Get<Seconds>()
	{
		return Get<MilliSeconds>() * THOUSANDTH;
	}

	template<>
	inline float Time::Get<Minutes>()
	{
		return Get<Seconds>() * SIXTIETH;
	}

	template<>
	inline float Time::Get<Hours>()
	{
		return Get<Minutes>() * SIXTIETH;
	}
}
