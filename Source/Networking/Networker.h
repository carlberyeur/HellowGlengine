#pragma once

namespace RakNet
{
	class RakPeerInterface;
}

class INetworker
{
public:
	INetworker();
	~INetworker();

	bool Init(const unsigned short aPortNumber);
	//bool SendPacket(INetworkMessage* aMessage, );
	//bool RecievePacket();

private:
	RakNet::RakPeerInterface* myPeerInterface;
};

