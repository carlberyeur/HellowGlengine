#pragma once

class CInputMessage
{
public:
	friend class CInputManager;
	friend class CU::VectorOnStack<CInputMessage, 16, short, false>/*::VectorOnStack()*/;

	enum class eType
	{
		eMouseMoved,
		eMousePressed,
		eMouseReleased,
		eKeyboardPressed,
		eKeyboardReleased
	};

	union Data
	{
		Data(const int aInt);
		Data(const short aValueX, const short aValueY);

		int GetInt() const;
		short GetShortX() const;
		short GetShortY() const;

	private:
		int myInt;
		struct Shorts
		{
			Shorts(const short aX, const short aY);
			short x, y;
		} myShorts;
	};

	CInputMessage(const eType aType, const int aValue);
	CInputMessage(const eType aType, const short aValueX, const short aValueY);
	~CInputMessage();

private:
	CInputMessage();
	CInputMessage(const CInputMessage& aCopy);

	eType myType;
	Data myData;
};

static_assert(sizeof(CInputMessage) <= 8u, "Something is wrong with the allignment or default enum size");
