#pragma once

#include "sssf\game\Game.h"
#include "sssf\gsm\physics\CollidableObject.h"
#include "Box2D\Dynamics\b2WorldCallbacks.h"

class BugginOutCollisionListener : public CollisionListener
{
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void OutOfBounds(Game* game);
};