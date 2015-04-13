#include "sssf_VS\stdafx.h"

#include "sssf\gsm\physics\CollidableObject.h"
#include "sssf\gsm\state\GameStateManager.h"

void CollidableObject::applyPhysics(Game* game)
{
	bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	bodyDef->position.Set(0.0f, 0.0f);
	body = game->getGSM()->getWorld()->getPWorld()->CreateBody(bodyDef);
	body->CreateFixture(fixDef);
	body->SetUserData(this);

	physics = true;
}
