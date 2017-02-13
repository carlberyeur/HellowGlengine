#include "stdafx.h"
#include "Game.h"

#include "StateStack.h"

#include "../PythonWrapper/PythonWrapper.h"
#include "../CommonUtilities/CommandLineParser.h"

#include "../PythonWrapper/PythonModule.h"
#include "../PythonWrapper/PythonFunction.h"
#include "../PythonWrapper/PythonList.h"
#include "../PythonWrapper/PythonTuple.h"

#include "ScriptLoader.h"

CGame::CGame()
	: myStateStack(nullptr)
{
}

CGame::~CGame()
{
	SAFE_DELETE(myStateStack);
}

void CGame::Init()
{
	CPythonWrapper pythonWrapper(CommandLineManagerW::GetInstance()->GetArgV()[0], ScriptLoader::InitPythonModules);


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

	myStateStack = new CStateStack();
}

void CGame::Update(const CU::Time& aDeltaTime)
{
	myStateStack->Update(aDeltaTime);
}

void CGame::Render()
{
	myStateStack->Render();
}
