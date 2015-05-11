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

	if (Obj1 && Obj2){
		int obj1ID = Obj1->getSpriteType()->getSpriteTypeID();
		int obj2ID = Obj2->getSpriteType()->getSpriteTypeID();
		if ((obj1ID == PLAYER_SPRITE_TYPE || obj2ID == PLAYER_SPRITE_TYPE) && (obj1ID == ZOMBIE_SPRITE_TYPE || obj2ID == ZOMBIE_SPRITE_TYPE)) {
			//player vs zombie - kill player
			AnimatedSprite* player;
			Bot* bot;
			if (obj1ID == PLAYER_SPRITE_TYPE) {
				player = static_cast<AnimatedSprite*>(Obj1);
				bot = static_cast<Bot*>(Obj2);
			} else {
				player = static_cast<AnimatedSprite*>(Obj2);
				bot = static_cast<Bot*>(Obj1);
			}
			if (!bot->isDieOnAnimEnd()) {
				if (player->getY() + (player->getSpriteType()->getTextureHeight() / 2) < bot->getY()) {
					bot->getGame()->getGSM()->getSpriteManager()->removeBot(bot);
				} else {
					player->setCurrentState(DEAD);
					player->setDieOnAnimEnd(true);
				}
			}
		} else if ((obj1ID == BAT_SPRITE_TYPE || obj2ID == BAT_SPRITE_TYPE) && (obj1ID != PLAYER_SPRITE_TYPE && obj2ID != PLAYER_SPRITE_TYPE)) {
			Bot* bat;
			Bot* bot;
			if (obj1ID == BAT_SPRITE_TYPE) {
				bat = static_cast<Bot*>(Obj1);
				bot = static_cast<Bot*>(Obj2);
			} else {
				bat = static_cast<Bot*>(Obj2);
				bot = static_cast<Bot*>(Obj1);
			}
			int botID = bot->getSpriteType()->getSpriteTypeID();
			if (botID == BALL_SPRITE_TYPE) {
				//bat vs ball - reverse velocity
				bot->setVelocity(-bot->getVelocityX(), bot->getVelocityY());
			} else if (botID == ZOMBIE_SPRITE_TYPE) {
				//bat vs zombie - kill zombie
				if (bot->getVelocityX() < -1.0) {
					bot->setCurrentState(LEFT_DEAD);
					bot->setVelocity(0.0, bot->getVelocityY());
					bot->setDieOnAnimEnd(true);
				} else if (bot->getVelocityX() > 1.0) {
					bot->setCurrentState(RIGHT_DEAD);
					bot->setVelocity(0.0, bot->getVelocityY());
					bot->setDieOnAnimEnd(true);
				} else bot->getGame()->getGSM()->getSpriteManager()->removeBot(bot);
			}
			//screen shake
			shake(bot->getGame());
		} else if ((obj1ID == BALL_SPRITE_TYPE || obj2ID == BALL_SPRITE_TYPE)) {
			Bot* ball;
			AnimatedSprite* other;
			if (obj1ID == BALL_SPRITE_TYPE) {
				ball = static_cast<Bot*>(Obj1);
				other = static_cast<AnimatedSprite*>(Obj2);
			} else {
				ball = static_cast<Bot*>(Obj2);
				other = static_cast<AnimatedSprite*>(Obj1);
			}
			int otherID = other->getSpriteType()->getSpriteTypeID();
			if (otherID == PLAYER_SPRITE_TYPE) {
				//player vs ball
				other->stun(15);
				if (other->getCurrentState() == ATTACKING_LEFT)
					other->setCurrentState(STUNNED_LEFT);
				else
					other->setCurrentState(STUNNED_RIGHT);
				//remove ball
				ball->getGame()->getGSM()->getSpriteManager()->removeBot(ball);
			} else if (otherID == ZOMBIE_SPRITE_TYPE) {
				//zombie vs ball - kill zombie
				AnimatedSprite* player = ball->getGame()->getGSM()->getSpriteManager()->getPlayer();
				if ((ball->getVelocityX() > 0 && player->getX() < ball->getX()) ||
					(ball->getVelocityX() < 0 && player->getX() > ball->getX())) {
					//ball hostile to zombies
					Bot* otherBot = static_cast<Bot*>(other);
					if (otherBot->getVelocityX() < -1.0) {
						otherBot->setCurrentState(LEFT_DEAD);
						otherBot->setVelocity(0.0, otherBot->getVelocityY());
						otherBot->setDieOnAnimEnd(true);
					} else if (otherBot->getVelocityX() > 1.0) {
						otherBot->setCurrentState(RIGHT_DEAD);
						otherBot->setVelocity(0.0, otherBot->getVelocityY());
						otherBot->setDieOnAnimEnd(true);
					} else otherBot->getGame()->getGSM()->getSpriteManager()->removeBot(otherBot);
					//remove ball
					ball->getGame()->getGSM()->getSpriteManager()->removeBot(ball);
				}
			}
		}
	} else if (Obj1) {
		if (Obj1->getSpriteType()->getSpriteTypeID() == BALL_SPRITE_TYPE) {
			Bot* ball = static_cast<Bot*>(Obj1);
			ball->getGame()->getGSM()->getSpriteManager()->removeBot(ball);
		}
	} else if (Obj2) {
		if (Obj2->getSpriteType()->getSpriteTypeID() == BALL_SPRITE_TYPE) {
			Bot* ball = static_cast<Bot*>(Obj2);
			ball->getGame()->getGSM()->getSpriteManager()->removeBot(ball);
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


void BugginOutCollisionListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	AnimatedSprite *Obj1 = NULL, *Obj2 = NULL;
	if (bodyUserData)
		Obj1 = static_cast<AnimatedSprite*>(bodyUserData);
	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		Obj2 = static_cast<AnimatedSprite*>(bodyUserData);

	if (Obj1 && Obj2) {
		int obj1ID = Obj1->getSpriteType()->getSpriteTypeID();
		int obj2ID = Obj2->getSpriteType()->getSpriteTypeID();
		if ((obj1ID == ZOMBIE_SPRITE_TYPE || obj2ID == ZOMBIE_SPRITE_TYPE)) {
			//zombie vs ball - pass through if ball is not hostile
			Bot* zombie;
			AnimatedSprite* other;
			if (obj1ID == ZOMBIE_SPRITE_TYPE) {
				zombie = static_cast<Bot*>(Obj1);
				other = static_cast<AnimatedSprite*>(Obj2);
			} else {
				zombie = static_cast<Bot*>(Obj2);
				other = static_cast<AnimatedSprite*>(Obj1);
			}
			int otherID = other->getSpriteType()->getSpriteTypeID();
			if (zombie->isDieOnAnimEnd())
				contact->SetEnabled(false);
			else if (otherID == BALL_SPRITE_TYPE || otherID == BALL_SPRITE_TYPE) {
				Bot* ball = static_cast<Bot*>(other);
				AnimatedSprite* player = ball->getGame()->getGSM()->getSpriteManager()->getPlayer();
				if ((ball->getVelocityX() > 0 && player->getX() > ball->getX()) ||
					(ball->getVelocityX() < 0 && player->getX() < ball->getX())) {
					//ball not hostile to zombies, no collision
					contact->SetEnabled(false);
				}
			}
		}
	}
}

void BugginOutCollisionListener::OutOfBounds(Game* game) {
	//player out of bounds
	AnimatedSprite *player= game->getGSM()->getSpriteManager()->getPlayer();
	XAudio2 *xAudio2 = game->getGSM()->getXAudio2();
	if (player->getLevelCheck() != 3){
		if (player->getX() > game->getGSM()->getWorld()->getWorldWidth() || player->getY() > game->getGSM()->getWorld()->getWorldHeight()){
			TMXMapImporter tmxMapImporter;
			BugginOutKeyEventHandler temp;
			game->getGSM()->unloadCurrentLevel();
			player->setLevelCheck((player->getLevelCheck() + 1) % 3);
			switch (player->getLevelCheck()){
			case 1:
				tmxMapImporter.loadWorld(game, W_LEVEL_1_DIR, W_LEVEL_1_NAME);
				player->setPosition(PLAYER_LEVEL1_X, PLAYER_LEVEL1_Y);
				player->setMFC();
				xAudio2->initXAudio();
				xAudio2->loadWavFile(Level1Sound);
				xAudio2->createSource();
				xAudio2->getSource()->SetVolume(0.05);
				xAudio2->playAudio();
				temp.loadSprites(game);
				break;
			case 2:
				tmxMapImporter.loadWorld(game, W_LEVEL_2_DIR, W_LEVEL_2_NAME);
				player->setPosition(PLAYER_LEVEL2_X, PLAYER_LEVEL2_Y);
				player->setMFC();
				xAudio2->initXAudio();
				xAudio2->loadWavFile(Level2Sound);
				xAudio2->createSource();
				xAudio2->getSource()->SetVolume(0.05);
				xAudio2->playAudio();
				temp.loadSprites(game);
				break;
			case 0:
				player->setLevelCheck(3);
				tmxMapImporter.loadWorld(game, W_LEVEL_3_DIR, W_LEVEL_3_NAME);
				player->setPosition(PLAYER_LEVEL3_X, PLAYER_LEVEL3_Y);
				player->setMFC();
				xAudio2->initXAudio();
				xAudio2->loadWavFile(Level3Sound);
				xAudio2->createSource();
				xAudio2->getSource()->SetVolume(0.05);
				xAudio2->playAudio();
				temp.loadSprites(game);
				break;
			default: break;
			}
		}
	}
}


void BugginOutCollisionListener::shake(Game* game) {
	float randX = 0;
	float randY = 0;
	(std::rand() % 2) == 0 ? randX = -16 : randX = 16;
	(std::rand() % 2) == 0 ? randY = -16 : randY = 16;
	Viewport* view = game->getGUI()->getViewport();
	World* world = game->getGSM()->getWorld();
	view->moveViewport((int)floor(randX), (int)floor(randY), world->getWorldWidth(), world->getWorldHeight());
}
void BugginOutCollisionListener::LoopBackGroundMusic(Game* game){
	XAudio2 *xAudio2 = game->getGSM()->getXAudio2();
	AnimatedSprite *player = game->getGSM()->getSpriteManager()->getPlayer();
	switch (player->getLevelCheck()){
	case 1:
		if (player->getMFC() == 1300){
			player->setMFC();
			xAudio2->FreeAudioEngine();
			xAudio2->initXAudio();
			xAudio2->loadWavFile(Level1Sound);
			xAudio2->createSource();
			xAudio2->getSource()->SetVolume(0.05);
			xAudio2->playAudio();
		}
		break;
	case 2:
		if (player->getMFC() == 930){
			player->setMFC();
			xAudio2->FreeAudioEngine();
			xAudio2->initXAudio();
			xAudio2->loadWavFile(Level2Sound);
			xAudio2->createSource();
			xAudio2->getSource()->SetVolume(0.05);
			xAudio2->playAudio();
		}
		break;
	case 3:
		if (player->getMFC() == 1100){
			player->setMFC();
			xAudio2->FreeAudioEngine();
			xAudio2->initXAudio();
			xAudio2->loadWavFile(Level3Sound);
			xAudio2->createSource();
			xAudio2->getSource()->SetVolume(0.05);
			xAudio2->playAudio();
		}
		break;
	default: break;
	}
	player->incMFC();
}