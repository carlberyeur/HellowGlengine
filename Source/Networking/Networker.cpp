#include "stdafx.h"
#include "Networker.h"


INetworker::INetworker()
	: myPeerInterface(nullptr)
{
}

INetworker::~INetworker()
{
	if (myPeerInterface)
	{
		//myPeerInterface->Shutdown();
		RakNet::RakPeerInterface::DestroyInstance(myPeerInterface);
		myPeerInterface = nullptr;
	}
}

bool INetworker::Init(const unsigned short aPortNumber)
{
	assert(!myPeerInterface && "Don't init networker twice");
	myPeerInterface = RakNet::RakPeerInterface::GetInstance();
	   
	RakNet::SocketDescriptor socketDescriptor(aPortNumber, nullptr);
	RakNet::StartupResult result = myPeerInterface->Startup(1, &socketDescriptor, 1);
	if (result != RakNet::StartupResult::RAKNET_STARTED)
	{
		DL_ASSERT("Failed to start network interface, error code: %d", result);
		return false;
	}
	
	return true;
}
