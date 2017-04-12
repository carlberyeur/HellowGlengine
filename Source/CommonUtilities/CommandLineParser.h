#pragma once

template<typename CHAR_TYPE>
class CommandLineManager
{
public:
	using STD_STRING = std::basic_string<CHAR_TYPE>;
	
	static void CreateInstance(int argc, CHAR_TYPE* argv[]);
	static void DestroyInstance();
	static CommandLineManager* GetInstance();
	
	bool HasParameter(const STD_STRING& aParameter);
	bool HasArgument(const STD_STRING& aParameter, const STD_STRING& aArgument);

	CHAR_TYPE** GetArgV();
	int GetArgC();

private:
	CommandLineManager(int argc, CHAR_TYPE* argv[]);
	~CommandLineManager();

	std::map<STD_STRING, CU::GrowingArray<STD_STRING>> myArgs;
	CHAR_TYPE** myArgV;
	int myArgC;

	static CommandLineManager* ourInstance;
};

using CommandLineManagerW = CommandLineManager<wchar_t>;
using CommandLineManagerA = CommandLineManager<char>;

template<typename CHAR_TYPE>
CommandLineManager<CHAR_TYPE>* CommandLineManager<CHAR_TYPE>::ourInstance = nullptr;

template<typename CHAR_TYPE>
void CommandLineManager<CHAR_TYPE>::CreateInstance(int argc, CHAR_TYPE* argv[])
{
	assert(ourInstance == nullptr && "Command line parser should not be created twice");
	ourInstance = new CommandLineManager(argc, argv);
}

template<typename CHAR_TYPE>
CommandLineManager<CHAR_TYPE>* CommandLineManager<CHAR_TYPE>::GetInstance()
{
	if (ourInstance == nullptr)
	{
		if (CommandLineManagerA::GetInstance() || CommandLineManagerW::GetInstance())
		{
			DL_MESSAGE_BOX("You are probably trying to get instance of wrong command line parser");
		}
	}
	return ourInstance;
}

template<typename CHAR_TYPE>
void CommandLineManager<CHAR_TYPE>::DestroyInstance()
{
	assert(ourInstance != nullptr && "Command line parser not created (is NULL)");
	SAFE_DELETE(ourInstance);
}

template<typename CHAR_TYPE>
bool CommandLineManager<CHAR_TYPE>::HasParameter(const STD_STRING& aParameter)
{
	return myArgs.find(aParameter) != myArgs.end();
}

template<typename CHAR_TYPE>
bool CommandLineManager<CHAR_TYPE>::HasArgument(const STD_STRING& aParameter, const STD_STRING& aArgument)
{
	if (HasParameter(aParameter) == true)
	{
		if (myArgs[aParameter].Find(aArgument) != myArgs[aParameter].FoundNone)
		{
			return true;
		}
	}

	return false;
}

template<typename CHAR_TYPE>
CHAR_TYPE** CommandLineManager<CHAR_TYPE>::GetArgV()
{
	return myArgV;
}

template<typename CHAR_TYPE>
int CommandLineManager<CHAR_TYPE>::GetArgC()
{
	return myArgC;
}

template<typename CHAR_TYPE>
CommandLineManager<CHAR_TYPE>::CommandLineManager(int aArgc, CHAR_TYPE* aArgv[])
	: myArgV(aArgv)
	, myArgC(aArgc)
{
	for (int i = 0; i < aArgc; ++i)
	{
		if (aArgv[i][0] == '-')
		{
			const CHAR_TYPE* argument = aArgv[i];
			while (i + 1 < aArgc && aArgv[i + 1][0] != '-')
			{
				if (myArgs[argument].IsInitialized() == false)
				{
					myArgs[argument].Init(4);
				}

				myArgs[argument].Add(aArgv[++i]);
			}
		}
	}

	for (auto it = myArgs.begin(); it != myArgs.end(); ++it)
	{
		it->second.Optimize();
	}
}

template<typename CHAR_TYPE>
CommandLineManager<CHAR_TYPE>::~CommandLineManager()
{
}
