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

	MESSAGE_LOG World::deleteActorByID(Uint64 _id)
	{
		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			if (m_allActors[i]->m_id == _id)
			{
				Actor* _actor = m_allActors[i];
				delete _actor;
				m_allActors.erase(m_allActors.begin() + i);
				return MESSAGE_SUCCESS("The actor was deleted");
			}
		}
		return MESSAGE_WARNING("Cant find the actor");
	}

	MESSAGE_LOG World::deleteAllActorsByName(std::string _name)
	{
		bool anyDestroyed = false;
		std::vector<int> allInts;
		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			if (m_allActors[i]->m_name == _name)
			{
				allInts.push_back(i);
				anyDestroyed = true;
			}
		}
		for (size_t i = 0; i < allInts.size(); i++)
		{
			int j = allInts[i];
			Actor* _actor = m_allActors[j];
			delete _actor;
			m_allActors.erase(m_allActors.begin() + j);
		}
		if (anyDestroyed)
			return MESSAGE_SUCCESS("Some actors was destroyed");
		else
			return MESSAGE_WARNING("Any Actor was destroyed");
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