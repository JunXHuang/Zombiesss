#include "sssf_VS\stdafx.h"

#include "sssf\gsm\physics\CollidableObject.h"

void CollidableObject::applyPhysics(World* world)
{
	bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	bodyDef->position.Set(0.0f, 4.0f);
	body = world->getPWorld()->CreateBody(bodyDef);
	body->SetUserData(this);

	b2PolygonShape* dynamicBox = new b2PolygonShape();
	dynamicBox->SetAsBox(width, height);
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = dynamicBox;
	fixtureDef->density = 1.0f;
	body->CreateFixture(fixtureDef);
}
