#include "sssf\game\Game.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gsm\ai\Bot.h"
#include "buggin_out\BugginOutCollisionListener.h"
#include "tmxmi\TMXMapImporter.h"
#include "Box2D\Dynamics\Contacts\b2Contact.h"
#include "Box2D\Dynamics\b2Fixture.h"
#include "buggin_out\BugginOut.h"
#include "buggin_out\BugginOutKeyEventHandler.h"
#include "sssf\XAudio2\XAudio2.h"
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
	AnimatedSprite *player= game->getGSM()->getSpriteManager()->getPlayer();
	XAudio2 *xAudio2 = game->getGSM()->getXAudio2();
	if (player->getLevelCheck() != 3){
		if (player->getX() > game->getGSM()->getWorld()->getWorldWidth() || player->getY() > game->getGSM()->getWorld()->getWorldHeight()){
			TMXMapImporter tmxMapImporter;
			BugginOutKeyEventHandler temp;
			game->getGSM()->getSpriteManager()->unloadSprites();
			game->getGSM()->getWorld()->unloadWorld();
			player->setLevelCheck((player->getLevelCheck() + 1) % 3);
			switch (player->getLevelCheck()){
			case 2:
				tmxMapImporter.loadWorld(game, W_LEVEL_2_DIR, W_LEVEL_2_NAME);
				player->setPosition(PLAYER_LEVEL2_X, PLAYER_LEVEL2_Y);
				xAudio2->FreeAudioEngine();
				xAudio2->initXAudio();
				xAudio2->loadWavFile(Level2Sound);
				xAudio2->createSource();
				xAudio2->playAudio();
				temp.loadSprites(game);
				break;
			case 0:
				player->setLevelCheck(3);
				tmxMapImporter.loadWorld(game, W_LEVEL_3_DIR, W_LEVEL_3_NAME);
				player->setPosition(PLAYER_LEVEL3_X, PLAYER_LEVEL3_Y);
				xAudio2->FreeAudioEngine();
				xAudio2->initXAudio();
				xAudio2->loadWavFile(Level3Sound);
				xAudio2->createSource();
				xAudio2->playAudio();
				temp.loadSprites(game);
				break;
			default: break;
			}
		}
	}
}

