#include "stdafx.h"
#include "ScriptComponent.h"
#include "ComponentMessage.h"

#include "../PythonWrapper/PythonWrapper.h"
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

bool CScriptComponent::InitModule(const std::string& aFilePath)
{
	myPythonModule = new CPythonModule();
	if (!CPythonWrapper::GetInstance()->ImportModule(aFilePath, *myPythonModule))
	{
		BREAK_POINT_HERE;
		return false;
	}

	return true;
}

void CScriptComponent::Init()
{
	CPythonFunction function;
	if (myPythonModule->GetFunction("init", function))
	{
		function(GetID());
	}
}

void CScriptComponent::Recieve(const SComponentMessage& aMessage)
{
	CPythonFunction function;

	switch (aMessage.myType)
	{
	case SComponentMessage::eType::eCollisionEnter:
		if (myPythonModule->GetFunction("OnCollisionEnter", function))
		{
			//CPythonList args;
			//args.Init();
			//args.Append(aMessage.myData);
			//function(args.AsTuple());

			//function(aMessage.myData);
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
