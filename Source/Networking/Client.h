#pragma once
#include "Networker.h"

class CClient : public INetworker
{
public:
	CClient();
	~CClient();

	bool Connect(const std::string& aIP, const unsigned short aServerPort);
};
