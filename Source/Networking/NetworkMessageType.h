#pragma once

#include "../RakNet/Source/MessageIdentifiers.h"

enum class eNetworkMessageType : unsigned char
{
	eChat = static_cast<unsigned char>(ID_USER_PACKET_ENUM)
};
