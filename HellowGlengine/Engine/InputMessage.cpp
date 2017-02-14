#include "stdafx.h"
#include "InputMessage.h"


CInputMessage::CInputMessage(const eType aType, const int aValue)
	: myType(aType)
	, myData(aValue)
{
}

CInputMessage::CInputMessage(const eType aType, const short aValueX, const short aValueY)
	: myType(aType)
	, myData(aValueX, aValueY)
{
}

CInputMessage::~CInputMessage()
{
}

CInputMessage::CInputMessage()
	: myType(eType::eMouseMoved)
	, myData(0, 0)
{
}

CInputMessage::CInputMessage(const CInputMessage& aCopy)
	: myType(aCopy.myType)
	, myData(aCopy.myData)
{
}

CInputMessage::Data::Data(const int aInt)
	: myInt(aInt)
{
}

CInputMessage::Data::Data(const short aValueX, const short aValueY)
	: myShorts(aValueX, aValueY)
{
}

int CInputMessage::Data::GetInt() const
{
	return myInt;
}

short CInputMessage::Data::GetShortX() const
{
	return myShorts.x;
}

short CInputMessage::Data::GetShortY() const
{
	return myShorts.y;
}

CInputMessage::Data::Shorts::Shorts(const short aX, const short aY)
	: x(aX)
	, y(aY)
{
}
