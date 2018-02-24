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
				m_allActors[i]->m_beDestroyed = true;
				return MESSAGE_SUCCESS("The actor was set to destroy");
			}
		}
		return MESSAGE_WARNING("Cant find the actor");
	}

	MESSAGE_LOG World::deleteAllActorsByName(std::string _name)
	{
		bool anyDestroyed = false;
		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			if (m_allActors[i]->m_name == _name)
			{
				m_allActors[i]->m_beDestroyed;
				anyDestroyed = true;
			}
		}

		if (anyDestroyed)
			return MESSAGE_SUCCESS("Some actors was destroyed");
		else
			return MESSAGE_WARNING("Any Actor was destroyed");
	}

	void World::CheckAndDelete()
	{
		bool anyDestroyed = false;
		std::vector<int> allInts;
		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			if (m_allActors[i]->m_DestroyMe)
			{
				allInts.push_back(i);
				anyDestroyed = true;
			}
		}
		if (anyDestroyed)
		{
			for (size_t i = 0; i < allInts.size(); i++)
			{
				int j = allInts[i];
				m_allActors[j]->destroy();
				delete m_allActors[j];
				m_allActors[j] = NULL;
			}
			int number = 0;
			for (size_t i = 0; i < allInts.size(); i++)
			{
				int j = allInts[i];
				m_allActors.erase(m_allActors.begin() + j + number);
				number--;
			}
		}
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

		CheckAndDelete();
	}
}