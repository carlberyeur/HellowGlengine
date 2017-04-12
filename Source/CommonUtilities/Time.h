#pragma once

namespace CU
{
	struct Hours {};
	struct Minutes {};
	struct Seconds {};
	struct MilliSeconds {};
	struct MicroSeconds {};

	const float THOUSANDTH = 0.001f;
	const float THOUSAND = 1000.f;
	const float SIXTIETH = 1.f / 60.f;
	const float SIXTY = 60.f;

	class Time
	{
	public:
		Time();
		Time(const Time& aRight);
		Time(const float aMicroSeconds);
		~Time();

		Time& operator=(const Time& aRight);

		Time& operator+=(const Time& aRight);
		Time& operator-=(const Time& aRight);

		Time operator+(const Time& aRight) const;
		Time operator-(const Time& aRight) const;

		bool operator<(const Time& aRight) const;
		bool operator>(const Time& aRight) const;

		void Reset();

		template <typename T>
		inline void Set(const float aTimeValue);

		template <typename T>
		inline float Get() const;

	private:
		float myMicroSeconds;
	};

	template<>
	inline float Time::Get<MicroSeconds>() const
	{
		return myMicroSeconds;
	}

	template<>
	inline float Time::Get<MilliSeconds>() const
	{
		return Get<MicroSeconds>() * THOUSANDTH;
	}

	template<>
	inline float Time::Get<Seconds>() const
	{
		return Get<MilliSeconds>() * THOUSANDTH;
	}

	template<>
	inline float Time::Get<Minutes>() const
	{
		return Get<Seconds>() * SIXTIETH;
	}

	template<>
	inline float Time::Get<Hours>() const
	{
		return Get<Minutes>() * SIXTIETH;
	}

	template<>
	inline void Time::Set<MicroSeconds>(const float aTimeValue)
	{
		myMicroSeconds = aTimeValue;
	}

	template<>
	inline void Time::Set<MilliSeconds>(const float aTimeValue)
	{
		Set<MicroSeconds>(aTimeValue * THOUSAND);
	}

	template<>
	inline void Time::Set<Seconds>(const float aTimeValue)
	{
		Set<MilliSeconds>(aTimeValue * THOUSAND);
	}

	template<>
	inline void Time::Set<Minutes>(const float aTimeValue)
	{
		Set<Seconds>(aTimeValue * SIXTY);
	}

	template<>
	inline void Time::Set<Hours>(const float aTimeValue)
	{
		Set<Minutes>(aTimeValue * SIXTY);
	}
}
