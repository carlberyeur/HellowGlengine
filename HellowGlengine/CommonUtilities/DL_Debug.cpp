#include "stdafx.h"
#include <cstdarg>
#include <iostream>

#include "DL_Debug.h"

#include "StringHelper.h"
#include "CommandLineParser.h"

#ifdef __APPLE__
#define VSPRINTF vsprintf
#elif defined _WIN32 || defined _WIN64
#include <Windows.h>
#define VSPRINTF vsprintf_s
#else
static_assert(false, "Is this debian?");
#endif

#define SUPRESS_UNUSED_WARNING(variable) (variable)
const unsigned int MAX_STRING_BUFFER_SIZE = 1024u;

namespace DL_Debug
{
	Debug* Debug::ourInstance = nullptr;
	
	class Debug::Log
	{
	public:
		inline void CreateLog(const char* aFileName);
		inline void Write(const char* aMessage);
		inline void Activate() { myIsActive = true; }
		inline void Deactivate() { myIsActive = false; }

	private:
		std::ofstream myDebugFile;
		std::string myFile;
		bool myIsActive;
	};

	void Debug::Log::CreateLog(const char* aFilePath)
	{
		myIsActive = false;
		myFile = aFilePath;
	}

	void Debug::Log::Write(const char* aMessage)
	{
		if (myIsActive == false)
		{
			return;
		}

		myDebugFile.open(myFile, std::ios::app);

		time_t rawTime = time(nullptr);
		tm timeInfo = {};
		char timebuffer[80];
		
		localtime_s(&timeInfo, &rawTime);
		strftime(timebuffer, 80, "[%d-%m-%Y %H:%M:%S] ", &timeInfo);

		myDebugFile << timebuffer << " " << aMessage << std::endl;

		myDebugFile.close();
	}

	Debug::Debug()
		: myLogFiles(nullptr)
	{
		ActivateLogs();
	}

	Debug::~Debug()
	{
		myLogFiles.DeleteAll();
	}

	void Debug::CreateLog(eLogType aLogType)
	{
		int logType = static_cast<int>(aLogType);
		if (myLogFiles[logType] != nullptr)
		{
			assert(!"Logtype already created");
			return;
		}

		myLogFiles[logType] = new Log();
		const char* fileName;
		switch (aLogType)
		{
		case DL_Debug::eLogType::eEngine:
			fileName = "LOG_ENGINE.loggo";
			break;
		case DL_Debug::eLogType::eGamePlay:
			fileName = "LOG_GAMEPLAY.loggo";
			break;
		case DL_Debug::eLogType::eResource:
			fileName = "LOG_RESOURCES.loggo";
			break;
		case DL_Debug::eLogType::eCrash:
			fileName = "LOG_CRASH.loggo";
			break;
		case DL_Debug::eLogType::eThreadedModels:
			fileName = "LOG_THREADED_MODELS.loggo";
			break;
		case DL_Debug::eLogType::eThreadPool:
			fileName = "LOG_THREADPOOL.loggo";
			break;
		default:
			fileName = "LOG_DEFAULT.loggo";
			break;
		}

		myLogFiles[logType]->CreateLog(fileName);
	}

	void Debug::CreateInstance()
	{
		assert(ourInstance == nullptr && "Debug logger already created");
		ourInstance = new Debug();
	}

	void Debug::DestroyInstance()
	{
		assert(ourInstance != nullptr && "Debug logger not created (is NULL)");
		SAFE_DELETE(ourInstance);
	}

	Debug* Debug::GetInstance()
	{
		assert(ourInstance != nullptr && "Debug logger not created (is NULL)");
		return ourInstance;
	}

	void Debug::ActivateLogs()
	{
		CommandLineManager<wchar_t>* commandLineManager = CommandLineManager<wchar_t>::GetInstance();
		if (commandLineManager != nullptr)
		{
			if (commandLineManager->HasArgument(L"-activatelog", L"gameplay"))
			{
				Activate(DL_Debug::eLogType::eGamePlay);
			}
			if (commandLineManager->HasArgument(L"-activatelog", L"resource"))
			{
				Activate(DL_Debug::eLogType::eResource);
			}
			if (commandLineManager->HasArgument(L"-activatelog", L"engine"))
			{
				Activate(DL_Debug::eLogType::eEngine);
			}
			if (commandLineManager->HasArgument(L"-activatelog", L"crash"))
			{
				Activate(DL_Debug::eLogType::eCrash);
			}
			if (commandLineManager->HasArgument(L"-activatelog", L"threadedModels"))
			{
				Activate(DL_Debug::eLogType::eThreadedModels);
			}
			if (commandLineManager->HasArgument(L"-activatelog", L"threadPool"))
			{
				Activate(DL_Debug::eLogType::eThreadPool);
			}
		}
	}

	void Debug::Activate(const eLogType aLogType)
	{
		int logType = static_cast<int>(aLogType);
		if (myLogFiles[logType] == nullptr)
		{
			CreateLog(aLogType);
		}
		
		myLogFiles[logType]->Activate();
	}

	void Debug::Deactivate(const eLogType aLogType)
	{
		int logType = static_cast<int>(aLogType);
		if (myLogFiles[logType] != nullptr)
		{
			myLogFiles[logType]->Deactivate();
		}
	}

	void Debug::PrintMessage(const char* aFormattedString, ...)
	{
		char buffer[MAX_STRING_BUFFER_SIZE] = {};
		va_list args;

		va_start(args, aFormattedString);
		VSPRINTF(buffer, aFormattedString, args);
		va_end(args);

		std::cout << buffer << std::endl;
	}

	void Debug::PrintMessage(const wchar_t* aFormattedString, ...)
	{
		wchar_t buffer[MAX_STRING_BUFFER_SIZE] = {};
		va_list args;
		va_start(args, aFormattedString);
		wvsprintf(buffer, aFormattedString, args);
		va_end(args);

		std::wcout << buffer << std::endl;
	}

	void Debug::WriteLog(const eLogType aLogType, const char* aFormattedString, ...)
	{
		Log* log = myLogFiles[static_cast<int>(aLogType)];
		if (log == nullptr)
		{
			return;
		}

		char buffer[MAX_STRING_BUFFER_SIZE] = {};
		va_list args;

		va_start(args, aFormattedString);
		VSPRINTF(buffer, aFormattedString, args);
		va_end(args);

		log->Write(buffer);
	}

	void Debug::ShowMessageBox(const char* aMessage, ...)
	{
#ifdef _WIN32
		char buffer[MAX_STRING_BUFFER_SIZE] = {};
		va_list args;

		va_start(args, aMessage);
		VSPRINTF(buffer, aMessage, args);
		va_end(args);

		int returnValue = MessageBoxA(nullptr, buffer, "Error (press 'abort' to exit program, 'retry' to debug, 'ignore' to continue", MB_ABORTRETRYIGNORE);

		if (returnValue == IDABORT)
		{
			exit(EXIT_FAILURE);
		}
		else if (returnValue == IDRETRY)
		{
			DL_ASSERT(buffer);
		}
		else if (returnValue == IDIGNORE)
		{
			return;
		}
#else
		SUPRESS_UNUSED_WARNING(aMessage);
#pragma message("ShowMessageBox not implemented outside of windows")
#endif
	}

	void Debug::ShowMessageBox(const wchar_t* aMessage, ...)
	{
#ifdef _WIN32
		wchar_t buffer[MAX_STRING_BUFFER_SIZE] = {};
		va_list args;

		va_start(args, aMessage);
		wvsprintf(buffer, aMessage, args);
		va_end(args);

		int returnValue = MessageBoxW(nullptr, buffer, L"Error (press 'abort' to exit program, 'retry' to debug, 'ignore' to continue", MB_ABORTRETRYIGNORE);

		if (returnValue == IDABORT)
		{
			exit(EXIT_FAILURE);
		}
		else if (returnValue == IDRETRY)
		{
			DL_ASSERT(buffer);
		}
		else if (returnValue == IDIGNORE)
		{
			return;
		}
#else
		SUPRESS_UNUSED_WARNING(aMessage);
#pragma message("ShowMessageBox not implemented outside of windows")
#endif
	}

	void Debug::SetConsoleColor(const unsigned short aColor)
	{
#ifdef _WIN32
		HANDLE hConsole = nullptr;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		if (hConsole != nullptr)
		{
			SetConsoleTextAttribute(hConsole, aColor);
		}
#else
		SUPRESS_UNUSED_WARNING(aColor);
#pragma message("ShowMessageBox not implemented outside of windows")
#endif
	}

	wchar_t * Debug::ParseVariadicArgs(wchar_t aBuffer[], const char* aFormattedString, ...)
	{
		char buffer[MAX_STRING_BUFFER_SIZE] = {};
		va_list args;
		va_start(args, aFormattedString);
		VSPRINTF(buffer, aFormattedString, args);
		va_end(args);

		std::string charStr = buffer;
		std::wstring wcharStr(charStr.begin(), charStr.end());

		(void)memcpy_s(aBuffer, MAX_STRING_BUFFER_SIZE, wcharStr.c_str(), MAX_STRING_BUFFER_SIZE);

		return aBuffer;
	}

	wchar_t* Debug::ParseVariadicArgs(wchar_t aBuffer[], const wchar_t * aFormattedString, ...)
	{
		wchar_t buffer[MAX_STRING_BUFFER_SIZE] = {};
		va_list args;
		va_start(args, aFormattedString);
		wvsprintf(buffer, aFormattedString, args);
		va_end(args);

		(void)memcpy_s(aBuffer, MAX_STRING_BUFFER_SIZE, buffer, MAX_STRING_BUFFER_SIZE);

		return aBuffer;
	}
}