#include "stdafx.h"
#include "NetworkMessage.h"

//#define ENUM_UNSIGNED_CHAR(A_ENUM) (*reinterpret_cast<unsigned char*>(&A_ENUM))

INetworkMessage::INetworkMessage(const eNetworkMessageType aType)
{
}

INetworkMessage::~INetworkMessage()
{
}

void INetworkMessage::Pack()
{
	CU::CSerializerSaver saver(MaxMessageSize);
	DoSerialize(saver);
}

void INetworkMessage::Unpack(const char aRawData[])
{
	CU::CSerializerLoader loader(MaxMessageSize);
	loader.Assign(aRawData, MaxMessageSize);
}

const char* INetworkMessage::GetStream() const
{
	return myStream.AsPointer();
}

int INetworkMessage::GetStreamSize() const
{
	return myStream.Size();
}

void INetworkMessage::DoSerialize(CU::ISerializer& aSerializer)
{
	aSerializer.Cerealize(myType);
	//aSerializer.Cerealize(ENUM_UNSIGNED_CHAR(myType));
}
