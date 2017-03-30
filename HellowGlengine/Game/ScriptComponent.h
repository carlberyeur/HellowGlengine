#pragma once
#include "Component.h"

class CPythonModule;
class CPythonTuple;

class CScriptComponent : public IComponent
{
public:
	CScriptComponent();
	~CScriptComponent();

	virtual void Recieve(const SComponentMessage& aMessage) override;
	virtual bool Answer(SComponentMessage& aMessage) override;

	virtual IComponent* Copy() override;
	virtual bool Load(CU::ISerializer& aSerializer) override;
	virtual bool Save(CU::ISerializer& aSerializer) override;

	CPythonTuple CallFunction(const CPythonTuple& aArguments);

private:
	CPythonModule* myPythonModule;
};
