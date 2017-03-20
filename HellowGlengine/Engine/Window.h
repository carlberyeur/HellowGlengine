#pragma once

class IWindow
{
public:
	struct SCreationParameters
	{
		unsigned int myWindowWidth;
		unsigned int myWindowHeight;
		bool myIsWindowed;

		union
		{
			struct SWindows
			{
				void* myHWND;
				void* myHInstance;

			} myWindowsParameters;

			struct SLinuxParameters
			{
				int myGarbage;
			} myLinuxParameters;
		};
	};

	IWindow();
	virtual ~IWindow();

	virtual bool Init(const SCreationParameters& aCreationParameters) = 0;
	virtual bool LoadExtensionList(class COpenGLFramework& aHWND) = 0;
	virtual bool InitInputWrapper(class CInputManager& aInputManager) = 0;
	virtual void Update() = 0;

	inline bool IsOpen() const;
	inline void Close();

protected:
	bool myIsOpen;
};

inline bool IWindow::IsOpen() const
{
	return myIsOpen;
}

inline void IWindow::Close()
{
	myIsOpen = false;
}
