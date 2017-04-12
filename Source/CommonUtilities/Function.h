#pragma once

namespace CU
{
	template<typename Ret, typename... Arg>
	class IBaseFunction
	{
	public:
		IBaseFunction() {}
		virtual ~IBaseFunction() {}

		virtual Ret Call(Arg&&... aArgs) = 0;
		virtual unsigned int SizeOf() = 0;
	};

	template<typename T, typename Ret, typename... Arg>
	class CEraserFunction : public IBaseFunction<Ret, Arg...>
	{
	public:
		CEraserFunction(T aFunctionObject)
			: myFunctionObject(aFunctionObject)
		{
		}

		~CEraserFunction()
		{
		}

		virtual Ret Call(Arg&&... aArgs)
		{
			return myFunctionObject(std::forward<Arg>(aArgs)...);
		}

		virtual unsigned int SizeOf()
		{
			return sizeof(*this);
		}

	private:
		T myFunctionObject;
	};

	template<typename Ret, typename... Arg>
	class CFunction
	{
	public:
		CFunction()
			: myFunctionObject(nullptr)
		{
			memset(myMemoryBlob, 0, sizeof(myMemoryBlob));
		}

		~CFunction()
		{
			Destroy();
		}

		template<typename T>
		CFunction(T aFunctionObject)
		{
			memset(myMemoryBlob, 0, sizeof(myMemoryBlob));
			Create<T>(aFunctionObject);
		}

		template<typename T>
		CFunction& operator=(T aFunctionObject)
		{
			Destroy();
			Create<T>(aFunctionObject);
			return *this;
		}

		CFunction& operator=(std::nullptr_t)
		{
			Destroy();
			return *this;
		}

		Ret operator()(Arg... aArgs)
		{
			assert(myFunctionObject);
			if (myFunctionObject)
			{
				return myFunctionObject->Call(std::forward<Arg>(aArgs)...);
			}

			return Ret();
		}

		bool operator==(const CFunction& aOther) const
		{
			return myFunctionObject == aOther.myFunctionObject;
		}

		bool operator==(std::nullptr_t) const
		{
			return !myFunctionObject;
		}

		bool operator!() const
		{
			return !myFunctionObject;
		}

		operator bool() const
		{
			return myFunctionObject != nullptr;
		}

	private:
		static constexpr unsigned int MemoryBlobSize = sizeof(Ret(*)(Arg...)) + sizeof(void*);

		template<typename T>
		void Create(T aFunctionObject)
		{
			if /*constexpr*/ (sizeof(CEraserFunction<T, Ret, Arg...>) <= MemoryBlobSize)
			{
				myFunctionObject = new (myMemoryBlob) CEraserFunction<T, Ret, Arg...>(aFunctionObject);
			}
			else
			{
				myFunctionObject = new CEraserFunction<T, Ret, Arg...>(aFunctionObject);
			}
		}

		void Destroy()
		{
			if (myFunctionObject)
			{
				if (myFunctionObject->SizeOf() <= MemoryBlobSize)
				{
					myFunctionObject->~IBaseFunction();
					myFunctionObject = nullptr;
					memset(myMemoryBlob, 0, sizeof(myMemoryBlob));
				}
				else
				{
					SAFE_DELETE(myFunctionObject);
				}
			}
		}
		
		IBaseFunction<Ret, Arg...>* myFunctionObject;
		char myMemoryBlob[MemoryBlobSize];
	};
}
