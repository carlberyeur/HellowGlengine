#pragma once

namespace picojson
{
	class value;
	using object = std::map<std::string, value>;
}

namespace CU
{
	class CJsonValue;

	class CJsonIterator
	{
	public:
		CJsonIterator(const picojson::value& aValue);
		CJsonIterator(picojson::object::const_iterator aIterator);
		~CJsonIterator();

		const std::string& First();
		CJsonValue Second();

		void operator++();
		void operator++(int);
		bool operator==(const CJsonIterator& aRight) const;
		bool operator!=(const CJsonIterator& aRight) const;

	private:
		picojson::object::const_iterator myIterator;
	};
}
