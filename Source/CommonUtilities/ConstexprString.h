#pragma once

namespace CU
{
	template<char... C>
	class CConstexprString final
	{
	public:
		static constexpr char const* Data();
		static constexpr unsigned int Size();

		static constexpr char At(const unsigned int aIndex);

	private:
		static constexpr char const myData[sizeof...(C) + 1] = { C..., '\0' };
		static constexpr unsigned int mySize = sizeof...(C);
	};

	template<char... C>
	constexpr char const* CConstexprString<C...>::Data()
	{
		return &myData[0];
	}

	template<char... C>
	constexpr unsigned int CConstexprString<C...>::Size()
	{
		return mySize;
	}

	template<char... C>
	constexpr char CConstexprString<C...>::At(const unsigned int aIndex)
	{
		static_assert(aIndex >= 0u && aIndex <= mySize, "constexpr string index out of range");
		return myData[aIndex];
	}
}