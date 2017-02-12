#include "stdafx.h"
#include "Game.h"

#include "../PythonWrapper/PythonWrapper.h"
#include "../CommonUtilities/CommandLineParser.h"

#include "../PythonWrapper/PythonModule.h"
#include "../PythonWrapper/PythonFunction.h"
#include "../PythonWrapper/PythonList.h"
#include "../PythonWrapper/PythonTuple.h"

CGame::CGame()
	: myGameWorld(nullptr)
{
}

CGame::~CGame()
{
}

void CGame::Init()
{
	CPythonWrapper pythonWrapper(CommandLineManagerW::GetInstance()->GetArgV()[0], nullptr);


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
}

void CGame::Update(const CU::Time& /*aDeltaTime*/)
{
}

void CGame::Render()
{
}
