#include "stdafx.h"
#include "PhysicsEngine.h"

#include "Box2D\Box2D.h"

//#ifdef _DEBUG
//#pragma comment(lib, "../Dependencies/Box2D/libs/Debug/Box2D.lib")
//#else
//#pragma comment(lib, "../Dependencies/Box2D/libs/Release/Box2D.lib")
//#endif // _DEBUG


CPhysicsEngine::CPhysicsEngine()
{
}

CPhysicsEngine::~CPhysicsEngine()
{
}

bool CPhysicsEngine::InitWorld(const CU::Vector2f /*aGravity*/)
{
	//myWorld = CU::MakeUnique<b2World>(b2Vec2(aGravity.x, aGravity.y));
	//return myWorld.IsValid();
	return false;
}
