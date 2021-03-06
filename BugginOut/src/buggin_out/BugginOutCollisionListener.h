#pragma once

#include "sssf\game\Game.h"
#include "sssf\gsm\physics\CollidableObject.h"
#include "Box2D\Dynamics\b2WorldCallbacks.h"

class BugginOutCollisionListener : public CollisionListener
{
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void OutOfBounds(Game* game);
	void shake(Game* game);
	void LoopBackGroundMusic(Game* game);
	void WinLoseDisplay(Game* game);
};