#include "Box2D\Dynamics\b2WorldCallbacks.h"

class Game;

class CollisionListener : public b2ContactListener
{
public:
	virtual void OutOfBounds(Game* game) {}
};