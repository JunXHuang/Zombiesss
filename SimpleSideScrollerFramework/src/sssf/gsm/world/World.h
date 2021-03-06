/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	World.h

	This class manages the static data for the game level being
	played. This means all game backgrounds, which are stored and
	manipulated in WorldLayer objects. A given level can have
	a game background rendered using multiple layers, some which
	can be tiled, others that can be sparse, and others that
	can be isometric.

	This class stores these layers and ensures they are rendered
	in the proper order, low index to high. Layers that need to
	be drawn first (the back-most layer), should be added first.
*/
#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\data_loader\GameDataLoader.h"
#include "sssf\graphics\RenderList.h"
#include "sssf\gsm\world\WorldLayer.h"
#include "sssf\gsm\physics\CollisionListener.h"

#include "Box2D\Dynamics\b2World.h"
#include "Box2D\Common\b2Math.h"

static const float PIXELS_PER_METER = 32.0f;

class Game;
class SpriteManager;

class World
{
private:
	// NOTE, THE worldWidth & worldHeight REPRESENT THE FULL
	// SIZE OF THIS LEVEL. WHICH SHOULD BE AT LEAST THE SIZE OF
	// THE VIEWPORT, AND LIKELY MUCH LARGER, WHICH WOULD THEN
	// REQUIRE SCROLLING TO SEE IT.
	int worldWidth;
	int worldHeight;

	// THESE ARE THE BACKGROUND LAYERS
	vector<WorldLayer*> *layers;

	CollisionListener* listener;

	b2Vec2* b2grav = new b2Vec2(0.0f, 9.8f);
	b2World* b2world = new b2World(*b2grav);
public:
	// INLINED ACCESSOR METHODS
	vector<WorldLayer*>*	getLayers()			{ return layers;			}
	int						getNumLayers()		{ return layers->size();	}
	int						getWorldHeight()	{ return worldHeight;		}
	int						getWorldWidth()		{ return worldWidth;		}
	b2World*				getPWorld()			{ return b2world;			}
	CollisionListener*		getListener()		{ return listener;			}


	// INLINED MUTATOR METHODS
	void setWorldHeight(int initWorldHeight)
	{ worldHeight = initWorldHeight;							}
	void setWorldWidth(int initWorldWidth)
	{ worldWidth = initWorldWidth;								}
	void setCollisionListener(CollisionListener* initListener)
	{ listener = initListener; b2world->SetContactListener(listener); }
	void setGravity(float initGravity) {
		b2grav = new b2Vec2(0.0f, initGravity);
		b2world->SetGravity(*b2grav);
	}

	// METHODS DEFINED in GameStateManager.cpp
	World();
	~World();
	void	addLayer(WorldLayer *layerToAdd);
	void	addWorldRenderItemsToRenderList(Game *game);
	void	unloadWorld();
	void	update(Game *game);
};