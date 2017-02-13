#pragma once
#include "Component.h"

class CPythonModule;

class CScriptComponent : public IComponent
{
public:
	CScriptComponent();
	~CScriptComponent();

	void Recieve(const SComponentMessage& aMessage) override;

private:
	CPythonModule* myPythonModule;
};
