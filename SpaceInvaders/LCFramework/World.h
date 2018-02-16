#pragma once

#include "Actor.h"
#include <vector>
#include "SDL_Manager.h"

namespace LCF
{
	/**
	* A container class for a world
	*/
	class World
	{
	public:
		World();
		virtual ~World();

		std::vector<Actor*> m_allActors;

		/**
		* Add a new actor to the world
		*
		* @param _actor
		* A pointer to an actor
		*
		*/
		void registerActor(Actor* _actor);

		/**
		* Render the content of the world
		*
		* @param _renderer
		* a SDL renderer
		*
		*/
		void render(SDL_Renderer* _renderer);
	};
}