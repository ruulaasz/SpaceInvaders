#pragma once

#include "Actor.h"
#include <vector>
#include "SDL_Manager.h"

class World
{
public:
	World();
	virtual ~World();

	std::vector<Actor*> m_allActors;

	void registerActor(Actor* _actor);
	void render(SDL_Renderer* _renderer);
};

