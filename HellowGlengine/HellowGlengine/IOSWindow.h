#pragma once

class IOSWindow
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

	IOSWindow();
	virtual ~IOSWindow();

	virtual bool Init(const SCreationParameters& aCreationParameters) = 0;
	virtual void Update() = 0;

	inline bool IsOpen() const;

protected:
	bool myIsOpen;
};

inline bool IOSWindow::IsOpen() const
{
	return myIsOpen;
}
