#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\world\World.h"

#include "Box2D\Box2D.h"
#include "Box2D\Dynamics\b2Body.h"

class CollidableObject
{
protected:
	b2BodyDef* bodyDef;
	b2FixtureDef* fixDef;
	b2Body* body;
	bool physics = false;
public:
	CollidableObject()	{}
	~CollidableObject()	{}

	float getX() { return body->GetPosition().x * PIXELS_PER_METER; }
	float getY() { return body->GetPosition().y * PIXELS_PER_METER; }
	float getVelocityX() { return body->GetLinearVelocity().x * PIXELS_PER_METER; }
	float getVelocityY() { return body->GetLinearVelocity().y * PIXELS_PER_METER; }
	float isPhysicsSet() { return physics; }

	void setPosition(float initX, float initY) {
		b2Vec2 position;
		position.x = initX / PIXELS_PER_METER;
		position.y = initY / PIXELS_PER_METER;
		body->SetTransform(position, 0.0f);
	}
	void setVelocity(float initX, float initY) {
		b2Vec2 velocity;
		velocity.x = initX / PIXELS_PER_METER;
		velocity.y = initY / PIXELS_PER_METER;
		body->SetLinearVelocity(velocity);
	}

	void applyPhysics(World* world, float initX, float initY);
	void applyPhysics(World* world);
};