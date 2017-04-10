#include "stdafx.h"
#include "Networker.h"


INetworker::INetworker()
{
}

INetworker::~INetworker()
{
}

bool INetworker::Init()
{
	RakNet::RakPeerInterface* peerInterface = RakNet::RakPeerInterface::GetInstance();

	RakNet::SocketDescriptor socketDescriptor(1337, nullptr);
	peerInterface->Startup(2, &socketDescriptor, 1);

	return false;
}
