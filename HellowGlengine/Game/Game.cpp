#include "stdafx.h"
#include "Game.h"

#include "StateStack.h"

#pragma comment(lib, "../Dependencies/python34/libs/python34.lib")

#include "../PythonWrapper/PythonWrapper.h"
#include "../CommonUtilities/CommandLineParser.h"

#include "../PythonWrapper/PythonModule.h"
#include "../PythonWrapper/PythonFunction.h"
#include "../PythonWrapper/PythonList.h"
#include "../PythonWrapper/PythonTuple.h"

#include "ScriptLoader.h"

#include "../Physics/PhysicsEngine.h"
#include "PlayState.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::Init()
{
	CPythonWrapper pythonWrapper(CommandLineManagerW::GetInstance()->GetArgV()[0], ScriptLoader::InitPythonModules);
	sizeof(CPythonWrapper);
	CPythonModule module;
	if (pythonWrapper.ImportModule("hello_wendy_program", module))
	{
		CPythonFunction function;
		module.GetFunction("hello_wendy", function);
		 
		CPythonList args;
		args.Init();
		args.Append<std::string>("hej");
		function(args.AsTuple());
	}

	myStateStack = CU::MakeUnique<CStateStack>();

	CPlayState* playState = new CPlayState(*myStateStack);
	if (playState)
	{
		myStateStack->Push(*playState);
	}
}

bool CGame::Update(const CU::Time aDeltaTime)
{
	if (!myStateStack->Update(aDeltaTime))
	{
		return false;
	}

	return true;
}

void CGame::Render()
{
	myStateStack->Render();
}
