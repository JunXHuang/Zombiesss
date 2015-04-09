#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\world\World.h"

#include "Box2D\Box2D.h"
#include "Box2D\Dynamics\b2Body.h"

// THESE ARE THE SWEEP AND PRUNE ORDERINGS
const unsigned int LEFT_EDGE = 0;
const unsigned int RIGHT_EDGE = 1;
const unsigned int TOP_EDGE = 2;
const unsigned int BOTTOM_EDGE = 3;

class CollidableObject
{
protected:
	b2BodyDef* bodyDef;
	b2Body* body;

	float width;
	float height;
	float density;

public:
	CollidableObject()	{}
	~CollidableObject()	{}

	float getX() { return body->GetPosition().x; }
	float getY() { return body->GetPosition().y; }
	float getVelocityX() { return body->GetLinearVelocity().x; }
	float getVelocityY() { return body->GetLinearVelocity().y; }
	float getWidth() { return width; }
	float getHeight() { return height; }

	void setPosition(float initX, float initY) {
		b2Vec2 position = body->GetPosition();
		position.x = initX;
		position.y = initY;
		body->SetTransform(position, 0.0f);
	}
	void setVelocity(float initX, float initY) {
		b2Vec2 velocity = body->GetLinearVelocity();
		velocity.x = initX;
		velocity.y = initY;
		body->SetLinearVelocity(velocity);
	}

	void applyPhysics(World* world);
};