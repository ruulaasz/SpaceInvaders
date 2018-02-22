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
		* @param Uint64 _id
		* id of the actor
		*
		*/
		MESSAGE_LOG deleteActorByID(Uint64 _id);

		/**
		* deletes all actors of the world with that name
		*
		* @param string _name
		* A name of the actor
		*
		*/
		MESSAGE_LOG deleteAllActorsByName(std::string _name);

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