#pragma once

class IRenderObject
{
public:
	IRenderObject();
	virtual ~IRenderObject();

	virtual bool Init() = 0;
	virtual void Render() = 0;
};

