#pragma once
#include "StaticArray.h"

namespace DL_Debug
{
	const unsigned short CONSOLE_TEXT_COLOR_RED = 12;
	const unsigned short CONSOLE_TEXT_COLOR_YELLOW = 14;
	const unsigned short CONSOLE_TEXT_COLOR_GREEN = 10;
	const unsigned short CONSOLE_TEXT_COLOR_WHITE = 15;
}

#include <assert.h>

#ifndef _RETAIL_BUILD
#define USE_FILTERLOG
#endif //RETAIL_BUILD

#ifdef USE_FILTERLOG
#define RESOURCES_LOG(message, ...) DL_WRITELOG(DL_Debug::eLogType::eResource, message, __VA_ARGS__)
#define MEMORY_LOG(message, ...) DL_WRITELOG(DL_Debug::eLogType::eMemory, message, __VA_ARGS__)
#define ENGINE_LOG(message, ...) DL_WRITELOG(DL_Debug::eLogType::eEngine, message, __VA_ARGS__)
#define GAMEPLAY_LOG(message, ...) DL_WRITELOG(DL_Debug::eLogType::eGamePlay, message, __VA_ARGS__)
#else //!USE_FILTERLOG
#define RESOURCES_LOG(...)
#define MEMORY_LOG(...)
#define ENGINE_LOG(...)
#define GAMEPLAY_LOG(...)
#endif //USE_FILTERLOG

#ifdef _DEBUG
#define DL_DEBUG_ASSERT DL_ASSERT
#else
#define DL_DEBUG_ASSERT(...)
#endif // _DEBUG

#ifndef _RETAIL_BUILD
#define DL_ASSERT(message, ...) wchar_t assertBuffer[1024]; _wassert(DL_Debug::Debug::GetInstance()->ParseVariadicArgs(assertBuffer, message, __VA_ARGS__), __FILEW__, __LINE__)
#define DL_PRINT(message, ...)  DL_Debug::Debug::GetInstance()->PrintMessage(message, __VA_ARGS__)
#define DL_PRINT_VECTOR3F(A_VECTOR) DL_PRINT("%f, %f, %f", A_VECTOR.x, A_VECTOR.y, A_VECTOR.z)
#define DL_PRINT_WARNING(message, ...) DL_Debug::Debug::GetInstance()->SetConsoleColor(DL_Debug::CONSOLE_TEXT_COLOR_YELLOW); DL_Debug::Debug::GetInstance()->PrintMessage(message, __VA_ARGS__); DL_Debug::Debug::GetInstance()->SetConsoleColor(DL_Debug::CONSOLE_TEXT_COLOR_WHITE)
#define DL_WRITELOG(logtype, message, ...) DL_Debug::Debug::GetInstance()->WriteLog(logtype, message, __VA_ARGS__); DL_PRINT(message, __VA_ARGS__)
#define DL_MESSAGE_BOX(message, ...) DL_Debug::Debug::GetInstance()->ShowMessageBox(message, __FILE__, __LINE__, __VA_ARGS__)
#define DL_FATAL_ERROR(message, ...) DL_ASSERT(message, __VA_ARGS__)
#else //!_RETAIL_BUILD
#define DL_ASSERT(message, ...) (message)
#define DL_PRINT(message, ...)  (message)
#define DL_PRINT_WARNING(message, ...) (message)
#define DL_WRITELOG(aLogTypes, ...) (aLogTypes)
#define DL_MESSAGE_BOX(message, ...) (message)
#define DL_FATAL_ERROR(message, ...) DL_Debug::Debug::GetInstance()->ShowMessageBox(message, __VA_ARGS__); exit(1)
#endif //RETAIL_BUILD

namespace DL_Debug
{
	enum class eLogType
	{
		eResource,
		eMemory,
		eEngine,
		eGamePlay,
		eCrash,
		eThreadedModels,
		eThreadPool,
		eLength
	};

	class Debug
	{
	public:
		class Log;

		static void CreateInstance();
		static void DestroyInstance();
		static Debug* GetInstance();

		void ActivateLogs();
		void Activate(const eLogType aLogType);
		void Deactivate(const eLogType aLogType);

		void PrintMessage(const char* aFormattedString, ...);
		void PrintMessage(const wchar_t* aFormattedString, ...);

		void WriteLog(const eLogType aLogType, const char* aFormattedString, ...);

		void ShowMessageBox(const char* aFormattedString, ...);
		void ShowMessageBox(const wchar_t* aFormattedString, ...);

		wchar_t* ParseVariadicArgs(wchar_t aBuffer[], const char* aFormattedString, ...);
		wchar_t* ParseVariadicArgs(wchar_t aBuffer[], const wchar_t* aFormattedString, ...);

		void SetConsoleColor(const unsigned short aColor);

	private:
		void CreateLog(eLogType aLogType);

		Debug();
		Debug(const Debug& aCopy) = delete;
		~Debug();

		CU::StaticArray<Log*, static_cast<int>(eLogType::eLength)> myLogFiles;

		static Debug* ourInstance;
	};
}
