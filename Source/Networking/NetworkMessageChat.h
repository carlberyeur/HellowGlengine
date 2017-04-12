#pragma once
#include "NetworkMessage.h"

class CNetworkMessageChat :	public INetworkMessage
{
public:
	CNetworkMessageChat();
	~CNetworkMessageChat();

	void Init(const std::string& aMessage);
	const std::string& GetMessageString() const;

private:
	virtual void DoSerialize(CU::ISerializer& aSerializer) override;

	std::string myMessage;
};
