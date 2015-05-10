/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	AnimatedSprite.cpp

	See AnimatedSprite.h for a class description.
*/

#include "sssf_VS\stdafx.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\state\GameStateManager.h"

#include "Box2D\Dynamics\b2World.h"
#include "Box2D\Dynamics\b2Fixture.h"
#include "Box2D\Collision\Shapes\b2PolygonShape.h"

/*
	AnimatedSprite - Default constructor, just sets everything to 0.
*/
AnimatedSprite::AnimatedSprite()  
{
	spriteType = 0;
	frameIndex = 0;
	animationCounter = 0;
	walked = false;
	frameCounter = 0;
	isZombie = false;
	dieOnAnimEnd = false;
}

/*
	Destructor - Nothing to clean up. We don't want to clean up the
	sprite type because it is a shared variable.
*/
AnimatedSprite::~AnimatedSprite() 
{
	if (physics)
		body->GetWorld()->DestroyBody(body);
	physics = false;
}

/*
	changeFrame - This method allows for the changing of an image in an 
	animation sequence for a given animation state.
*/
void AnimatedSprite::changeFrame(Game *game)
{
	// RESET THE COUNTER
	animationCounter = 0;

	// REMEMBER, WE COUNT BY 2s
	frameIndex += 2;

	// GO BACK TO FIRST INDEX IF NECESSARY
	if (frameIndex == spriteType->getSequenceSize(currentState)) {
		if (dieOnAnimEnd) {
			SpriteManager* spriteManager = game->getGSM()->getSpriteManager();
			if (this != spriteManager->getPlayer()){
				Bot* bot = static_cast<Bot*>(this);
				game->getGSM()->getSpriteManager()->removeBot(bot);
				frameIndex -= 2;
			} else
				frameIndex = 0;
		} else
			frameIndex = 0;
	}
}

void AnimatedSprite::setSpriteType(AnimatedSpriteType *initSpriteType) {
	spriteType = initSpriteType;

	width = spriteType->getTextureWidth();
	height = spriteType->getTextureHeight();

	fixDef = spriteType->getFixtureDef();
}

/*
	getCurrentImageID - This method does the work of retrieving
	the image id that corresponds to this sprite's current state
	and frame index.
*/
unsigned int AnimatedSprite::getCurrentImageID()
{
	return spriteType->getAnimationFrameID(currentState, frameIndex);
}

/*
	setCurrentState - This method sets this sprite to the newState
	state and starts its animtion sequence from the beginning.
*/
void AnimatedSprite::setCurrentState(wstring newState) 
{
	string cs(currentState.begin(), currentState.end());
	string ns(newState.begin(), newState.end());
	if (strcmp(cs.c_str(), ns.c_str()) != 0)
	{
		// SET THE ANIMATINO STATE
		currentState = newState;

		// AND RESET OUR COUNTERS
		animationCounter = 0;
		frameIndex = 0;
	}
}

/*
	updateSprite - To be called every frame of animation. This
    method advances the animation counter appropriately per
	the animation speed. It also updates the sprite location
	per the current velocity.
*/
void AnimatedSprite::updateSprite(Game* game)
{
	this->updateVelocity();
	stunned--;

	unsigned int duration = spriteType->getDuration(currentState, frameIndex);
	animationCounter++;

	// WE ONLY CHANGE THE ANIMATION FRAME INDEX WHEN THE
	// ANIMATION COUNTER HAS REACHED THE DURATION
	if (animationCounter >= duration)
		changeFrame(game);
}