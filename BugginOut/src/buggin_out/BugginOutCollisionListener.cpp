#include "sssf\game\Game.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gsm\ai\Bot.h"
#include "buggin_out\BugginOutCollisionListener.h"

#include "Box2D\Dynamics\Contacts\b2Contact.h"
#include "Box2D\Dynamics\b2Fixture.h"

void BugginOutCollisionListener::BeginContact(b2Contact* contact) {

	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	AnimatedSprite *Obj1=NULL,*Obj2=NULL;
	if (bodyUserData)
		Obj1 = static_cast<AnimatedSprite*>(bodyUserData);

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		Obj2 = static_cast<AnimatedSprite*>(bodyUserData);
	if (Obj1){
		//Player
		if (Obj1->getSpriteType()->getSpriteTypeID() == 2){}
		//Bot
		else{
			if (!Obj2){}
		}
	}
	if (Obj2){
		//Player
		if (Obj2->getSpriteType()->getSpriteTypeID() == 2){}
		//Bot
		else{
			if (!Obj1){}
		}
	}
}

void BugginOutCollisionListener::EndContact(b2Contact* contact) {

	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<AnimatedSprite*>(bodyUserData);

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<AnimatedSprite*>(bodyUserData);

}

void BugginOutCollisionListener::OutOfBounds(Game* game) {
	//player out of bounds
}