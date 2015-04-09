#pragma once

#include "sssf\game\Game.h"
#include "Box2D\Dynamics\b2WorldCallbacks.h"

class BugginOutCollisionListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};