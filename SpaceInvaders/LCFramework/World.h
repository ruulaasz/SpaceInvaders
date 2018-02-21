#pragma once

#include "Actor.h"
#include <vector>
#include "SDL_Manager.h"
#include "Module.h"

namespace LCF
{
	/**
	* A container class for a world
	*/
	class World : public LCF::Module<World>
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
		* deletes an actor of the world
		*
		* @param _actor
		* A pointer to an actor
		*
		*/
		void deleteActor(int _id);

		/**
		* Render the content of the world
		*
		* @param _renderer
		* a SDL renderer
		*
		*/
		void render(SDL_Renderer* _renderer);

		/**
		* Updates the content of the world
		*
		* @param _deltaTime
		* the change of time.
		*
		*/
		void update(float _deltaTime);
	};
}