#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\world\World.h"

#include "Box2D.h"

class CollidableObject
{
protected:
	b2BodyDef* bodyDef;
	b2FixtureDef* fixDef;
	b2Body* body;

	float width, height;
	float vx, vy;
	bool physics = false;
public:
	CollidableObject()	{}
	~CollidableObject()	{
		if (physics)
			body->GetWorld()->DestroyBody(body);
		physics = false;
	}

	float getX() {
		return (body->GetPosition().x * PIXELS_PER_METER) - (width / 2);
	}
	float getY() {
		return (body->GetPosition().y * PIXELS_PER_METER) - (height / 2);
	}
	float getVelocityX() { return body->GetLinearVelocity().x * PIXELS_PER_METER; }
	float getVelocityY() { return body->GetLinearVelocity().y * PIXELS_PER_METER; }
	float isPhysicsSet() { return physics; }

	void setPosition(float initX, float initY) {
		b2Vec2 position;
		position.x = (initX + (width/2)) / PIXELS_PER_METER;
		position.y = (initY + (height/2)) / PIXELS_PER_METER;
		body->SetTransform(position, 0.0f);
	}
	void setVelocity(float initX, float initY) {
		vx = initX / PIXELS_PER_METER;
		vy = initY / PIXELS_PER_METER;

		b2Vec2 velocity;
		velocity.x = vx;
		velocity.y = vy;
		body->SetLinearVelocity(velocity);
	}
	void updateVelocity() {
		b2Vec2 velocity = body->GetLinearVelocity();
		velocity.x = vx;
		//velocity.y = vy;
		body->SetLinearVelocity(velocity);
	}
	void applyForce(float initX, float initY) {
		b2Vec2 force;
		force.x = initX / PIXELS_PER_METER;
		force.y = initY / PIXELS_PER_METER;
		body->ApplyForce(force, body->GetWorldCenter(), true);
	}
	void setGravity(bool gravity) {
		if (gravity) {
			body->SetGravityScale(1.0);
		} else {
			body->SetGravityScale(0.0);
		}
	}

	void applyPhysics(Game* game);
};