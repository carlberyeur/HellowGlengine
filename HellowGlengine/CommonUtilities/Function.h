#pragma once

namespace CU
{
	template<typename Ret, typename... Args>
	class CFunction
	{
	public:
		using FunctionPointerType = Ret(*)(Args...);

		CFunction();
		CFunction(FunctionPointerType aFunctionPointer);
		~CFunction();

		Ret operator()(Args... aArgs);

	private:
		FunctionPointerType myFunctionPointer;
	};

	template<typename Ret, typename ...Args>
	inline CFunction<Ret, Args...>::CFunction()
	{
	}

	template<typename Ret, typename ...Args>
	inline CFunction<Ret, Args...>::CFunction(FunctionPointerType aFunctionPointer)
	{
		myFunctionPointer = aFunctionPointer;
	}

	template<typename Ret, typename ...Args>
	inline CFunction<Ret, Args...>::~CFunction()
	{
	}

	template<typename Ret, typename ...Args>
	inline Ret CFunction<Ret, Args...>::operator()(Args... aArgs)
	{
		return myFunctionPointer(aArgs...);
	}
}
