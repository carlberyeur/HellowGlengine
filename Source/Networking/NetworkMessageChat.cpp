#include "stdafx.h"
#include "NetworkMessageChat.h"


CNetworkMessageChat::CNetworkMessageChat()
	: INetworkMessage(eNetworkMessageType::eChat)
{
}

CNetworkMessageChat::~CNetworkMessageChat()
{
}

void CNetworkMessageChat::Init(const std::string& aMessage)
{
	myMessage = aMessage;
}

const std::string& CNetworkMessageChat::GetMessageString() const
{
	return myMessage;
}

void CNetworkMessageChat::DoSerialize(CU::ISerializer& aSerializer)
{
	aSerializer.Cerealize(myMessage);
}
