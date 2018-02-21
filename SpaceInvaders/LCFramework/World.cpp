#include "World.h"

namespace LCF
{
	World::World()
	{

	}

	World::~World()
	{

	}

	void World::registerActor(Actor * _actor)
	{
		m_allActors.push_back(_actor);
	}

	void World::deleteActor(int _id)
	{

	}

	void World::render(SDL_Renderer* _renderer)
	{
		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			m_allActors.at(i)->render(_renderer);
		}
	}

	void World::update(float _deltaTime)
	{
		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			m_allActors.at(i)->update(_deltaTime);
		}
	}
}