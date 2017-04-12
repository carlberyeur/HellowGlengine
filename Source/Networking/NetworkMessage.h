#pragma once

enum class eNetworkMessageType : unsigned char;

class INetworkMessage
{
public:
	INetworkMessage(const eNetworkMessageType aType);
	virtual ~INetworkMessage();

	void Pack();
	void Unpack(const char aRawData[]);

	const char* GetStream() const;
	int GetStreamSize() const;

	static constexpr unsigned int MaxMessageSize = 512u;

protected:
	virtual void DoSerialize(CU::ISerializer& aSerializer) = 0;

private:
	CU::GrowingArray<char> myStream;

	eNetworkMessageType myType;
};
