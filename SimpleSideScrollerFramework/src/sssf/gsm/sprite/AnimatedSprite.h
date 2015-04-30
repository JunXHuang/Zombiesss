/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	AnimatedSprite.h

	This class represents a sprite that can can
	be used to animate a game character or object.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\physics\CollidableObject.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\world\World.h"
#include "sssf\gui\Viewport.h"

class AnimatedSprite : public CollidableObject {
protected:
	// SPRITE TYPE FOR THIS SPRITE. THE SPRITE TYPE IS THE ID
	// OF AN AnimatedSpriteType OBJECT AS STORED IN THE SpriteManager
	AnimatedSpriteType *spriteType;

	// TRANSPARENCY/OPACITY
	int alpha;

	bool dieOnAnimEnd;

	// THE "current" STATE DICTATES WHICH ANIMATION SEQUENCE 
	// IS CURRENTLY IN USE, BUT IT MAP ALSO BE USED TO HELP
	// WITH OTHER GAME ACTIVITIES, LIKE PHYSICS
	wstring currentState;

	// THE INDEX OF THE CURRENT FRAME IN THE ANIMATION SEQUENCE
	// NOTE THAT WE WILL COUNT BY 2s FOR THIS SINCE THE VECTOR
	// THAT STORES THIS DATA HAS (ID,DURATION) TUPLES
	unsigned int frameIndex;

	// USED TO ITERATE THROUGH THE CURRENT ANIMATION SEQUENCE
	unsigned int animationCounter;
	int LevelCheck;
	bool walked;
	int frameCounter;
public:
	// INLINED ACCESSOR METHODS
	int					getAlpha()			{ return alpha;				}
	wstring				getCurrentState()	{ return currentState;		}
	unsigned int		getFrameIndex()		{ return frameIndex;		}
	AnimatedSpriteType*	getSpriteType()		{ return spriteType;		}
	void				setLevelCheck(int i)		{ LevelCheck = i; }
	int					getLevelCheck()		{ return LevelCheck; }
	bool				getWalk()			{ return walked; }
	void				setWalk(bool w)		{ walked = w; }
	int					getFC()				{ return frameCounter; }
	void				setFC(int fc)		{ frameCounter = fc; }
	void				setDieOnAnimEnd(bool die) { dieOnAnimEnd = die; }

	// INLINED MUTATOR METHODS
	void setAlpha(int initAlpha)
	{	alpha = initAlpha;						}

	// METHODS DEFINED IN AnimatedSprite.cpp
	AnimatedSprite();
	~AnimatedSprite();
	void setSpriteType(AnimatedSpriteType *initSpriteType);
	void changeFrame(Game *game);
	unsigned int getCurrentImageID();
	void setCurrentState(wstring newState);
	void updateSprite(Game *game);
};