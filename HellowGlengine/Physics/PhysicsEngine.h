#pragma once

class b2World;

class CPhysicsEngine
{
public:
	CPhysicsEngine();
	~CPhysicsEngine();

	bool InitWorld(const CU::Vector2f aGravity);

private:
	CU::UniquePointer<b2World> myWorld;
};
