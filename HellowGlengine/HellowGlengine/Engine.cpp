#include "stdafx.h"
#include "Engine.h"

#include <assert.h>

bool CEngine::CreateInstance(const CreationParameters& aCreationParameters)
{
	assert(ourInstance == nullptr && "Engine should not be created twice!");
	ourInstance = new CEngine();
	
	if (ourInstance != nullptr)
	{
		return ourInstance->InternalInit(aCreationParameters);
	}

	return false;
}

void CEngine::DestroyInstance()
{
}

CEngine& CEngine::GetInstance()
{
	// TODO: insert return statement here
}

void CEngine::Start()
{
}

void CEngine::Shutdown()
{
}

CEngine::CEngine()
{
}

CEngine::~CEngine()
{
}

bool CEngine::InternalInit(const CreationParameters& aCreationParameters)
{
	
	return false;
}
