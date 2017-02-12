#pragma once
#include<functional>
namespace CU
{
	template<typename ClassType, typename Ret, typename... Args>
	class CMemberFunction
	{
	public:
		using FunctionPtrType = Ret(ClassType::*)(Args...);

		CMemberFunction();
		CMemberFunction(const CMemberFunction&) = default;
		CMemberFunction(ClassType* aClassObject, FunctionPtrType aFunction);
		~CMemberFunction();

		Ret operator()(Args... aArgs);

	private:
		FunctionPtrType myFunction;
		ClassType* myClassObject;
	};

	template<typename ClassType, typename Ret, typename... Args>
	CMemberFunction<ClassType, Ret, Args...>::CMemberFunction()
		: myFunction(nullptr)
		, myClassObject(nullptr)
	{
	}

	template<typename ClassType, typename Ret, typename... Args>
	inline CMemberFunction<ClassType, Ret, Args...>::CMemberFunction(ClassType* aClassObject, FunctionPtrType aFunction)
		: myFunction(aFunction)
		, myClassObject(aClassObject)
	{
	}

	template<typename ClassType, typename Ret, typename... Args>
	CMemberFunction<ClassType, Ret, Args...>::~CMemberFunction()
	{
	}

	template<typename ClassType, typename Ret, typename... Args>
	inline Ret CMemberFunction<ClassType, Ret, Args...>::operator()(Args... aArgs)
	{
		return (myClassObject->*myFunction)(aArgs...);
	}

	template<typename ClassType, typename Ret, typename... Args>
	class CMemberFunction<ClassType, Ret, Args...> Bind(Ret(ClassType::*aFunction)(Args...), ClassType*& const aClassObject)
	{
		return CMemberFunction<ClassType, Ret, Args...>(aClassObject, aFunction);
	}
}
