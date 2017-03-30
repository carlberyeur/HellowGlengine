#include "stdafx.h"
#include "ScriptComponent.h"
#include "ComponentMessage.h"

#include "../PythonWrapper/PythonModule.h"
#include "../PythonWrapper/PythonFunction.h"
#include "../PythonWrapper/PythonTuple.h"
#include "../PythonWrapper/PythonList.h"

CScriptComponent::CScriptComponent()
	: myPythonModule(nullptr)
{
}

CScriptComponent::~CScriptComponent()
{
	SAFE_DELETE(myPythonModule);
}

void CScriptComponent::Recieve(const SComponentMessage& aMessage)
{
	CPythonFunction function;

	switch (aMessage.myType)
	{
	case SComponentMessage::eType::eCollisionEnter:
		if (myPythonModule->GetFunction("OnCollisionEnter", function))
		{
			CPythonList args;
			args.Init();
			args.Append(aMessage.myData);
			function(args.AsTuple());

			function(aMessage.myData);
		}
		break;
	case SComponentMessage::eType::eCollisionExit:
		break;
	}
}

bool CScriptComponent::Answer(SComponentMessage& aMessage)
{
	return false;
}

IComponent* CScriptComponent::Copy()
{
	return nullptr;
}

bool CScriptComponent::Load(CU::ISerializer& aSerializer)
{
	return false;
}

bool CScriptComponent::Save(CU::ISerializer& aSerializer)
{
	return false;
}

CPythonTuple CScriptComponent::CallFunction(const CPythonTuple& aArguments)
{
	return CPythonTuple();
}
