#pragma once

#include "InputListener.h"

namespace CU
{
	class Time;
	class CStopWatch;
}

namespace wendy
{
	class IWindow;
	class IGraphicsFramework;

	class IMeshManager;
	class ITextureManager;
	class IEffectManager;
	
	class CSpriteManager;
	class CRenderer;
	class CInputManager;

	class CEngine : public IInputListener
	{
	public:
		struct SCreationParameters
		{
			enum eCreationFlags : unsigned int
			{
				eGL = 1 << 0,
				eDX = 1 << 1,
				eFullScreen = 1 << 2,
				eWindows = 1 << 3,
				eLinux = 1 << 4
			};

			std::function<void(void)> myInitCallback;
			std::function<bool(const CU::Time)> myUpdateCallback;
			std::function<void(void)> myRenderCallback;

			unsigned int myWindowHeight;
			unsigned int myWindowWidth;
			unsigned int myCreationFlags;
			//unsigned int myDebugFlags;
		};

		static bool CreateInstance(const SCreationParameters& aCreationParameters);
		static void DestroyInstance();
		static CEngine& GetInstance();
		static CEngine* GetInstancePtr();

		void Start();
		void Shutdown();

		void Update();
		void Render();

		inline IGraphicsFramework& GetGraphicsFramework();
		inline IMeshManager& GetMeshManager();
		inline ITextureManager& GetTextureManager();
		inline IEffectManager& GetEffectManager();
		inline CSpriteManager& GetSpriteManager();
		inline CRenderer& GetRenderer();

		inline CU::Vector2ui GetWindowSize() const;
		inline CU::Vector2f GetWindowSizeF() const;

	private:
		CEngine();
		~CEngine();

		bool InternalInit(const SCreationParameters& aCreationParameters);
		eResult TakeInput(const CInputMessage& aMessage) override;

		std::function<void(void)> myInitCallback;
		std::function<bool(const CU::Time)> myUpdateCallback;
		std::function<void(void)> myRenderCallback;

		CU::UniquePointer<IWindow> myWindow;
		CU::UniquePointer<IGraphicsFramework> myGraphicsFramework;

		CU::UniquePointer<IMeshManager> myMeshManager;
		CU::UniquePointer<ITextureManager> myTextureManager;
		CU::UniquePointer<IEffectManager> myEffectManager;
		
		CU::UniquePointer<CSpriteManager> mySpriteManager;
		CU::UniquePointer<CRenderer> myRenderer;
		CU::UniquePointer<CInputManager> myInputManager;

		CU::UniquePointer<CU::CStopWatch> myLogicTimer;
		CU::UniquePointer<CU::CStopWatch> myRenderTimer;

		CU::Vector2ui myWindowSize;

		static CEngine* ourInstance;
	};

	inline IGraphicsFramework& CEngine::GetGraphicsFramework()
	{
		return *myGraphicsFramework;
	}

	inline IMeshManager& CEngine::GetMeshManager()
	{
		return *myMeshManager;
	}

	inline ITextureManager& CEngine::GetTextureManager()
	{
		return *myTextureManager;
	}

	inline IEffectManager& CEngine::GetEffectManager()
	{
		return *myEffectManager;
	}

	inline CSpriteManager& CEngine::GetSpriteManager()
	{
		return *mySpriteManager;
	}

	inline CRenderer& CEngine::GetRenderer()
	{
		return *myRenderer;
	}

	inline CU::Vector2ui CEngine::GetWindowSize() const
	{
		return myWindowSize;
	}

	inline CU::Vector2f CEngine::GetWindowSizeF() const
	{
		return CU::Vector2f(myWindowSize);
	}
}
