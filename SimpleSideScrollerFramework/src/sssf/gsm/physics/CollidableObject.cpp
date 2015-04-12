#include "sssf_VS\stdafx.h"

#include "sssf\gsm\physics\CollidableObject.h"

void CollidableObject::applyPhysics(World* world, float initX, float initY)
{
	bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	bodyDef->position.Set(initX / PIXELS_PER_METER, initY / PIXELS_PER_METER);
	body = world->getPWorld()->CreateBody(bodyDef);
	body->CreateFixture(fixDef);
	body->SetUserData(this);

	physics = true;
}

void CollidableObject::applyPhysics(World* world)
{
	applyPhysics(world, 0.0f, 0.0f);
}
