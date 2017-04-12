#include "stdafx.h"
#include "JsonIterator.h"
#include "JsonValue.h"
#include "picojson.h"

namespace CU
{
	CJsonIterator::CJsonIterator(const picojson::value& aValue)
		: myIterator(aValue.get<picojson::object>().begin())
	{
	}

	CJsonIterator::CJsonIterator(picojson::object::const_iterator aIterator)
		: myIterator(aIterator)
	{
	}

	CJsonIterator::~CJsonIterator()
	{
	}

	const std::string& CJsonIterator::First()
	{
		return myIterator->first;
	}

	CJsonValue CJsonIterator::Second()
	{
		return CJsonValue(myIterator->second);
	}

	void CJsonIterator::operator++()
	{
		++myIterator;
	}

	void CJsonIterator::operator++(int)
	{
		myIterator++;
	}

	bool CJsonIterator::operator==(const CJsonIterator& aRight) const
	{
		return myIterator == aRight.myIterator;
	}

	bool CJsonIterator::operator!=(const CJsonIterator& aRight) const
	{
		return myIterator != aRight.myIterator;
	}
}