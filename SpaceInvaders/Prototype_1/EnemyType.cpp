#include "stdafx.h"
#include "EnemyType.h"

EnemyType::EnemyType()
{
	m_moveAnimation = new LCF::Animator();
	m_deadAnimation = new LCF::Animator();
}

EnemyType::~EnemyType()
{

}

void EnemyType::init(std::string _info)
{
	std::string value;
	int order = 0;

	for (size_t i = 0; i < _info.size(); i++)
	{
		if (_info.at(i) != ' ')
		{
			value.push_back(_info.at(i));
		}
		else
		{
			order++;

			switch (order)
			{
			default:
				break;

			case 1:
				m_moveSFX = new LCF::Sfx(*reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset(value)));
				value.clear();
				break;

			case 2:
				m_deadSFX = new LCF::Sfx(*reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset(value)));
				value.clear();
				break;

			case 3:
				m_movementSpeed = atof(value.c_str());
				value.clear();
				break;

			case 4:
				m_moveAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset(value));
				value.clear();
				break;

			case 5:
				m_moveAnimation->m_numOfFrames = atoi(value.c_str());
				value.clear();
				break;

			case 6:
				m_moveAnimation->m_animSpeed = atof(value.c_str());
				value.clear();
				break;

			case 7:
				m_deadAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset(value));
				value.clear();
				break;

			case 8:
				m_deadAnimation->m_numOfFrames = atoi(value.c_str());
				value.clear();
				break;

			case 9:
				m_deadAnimation->m_animSpeed = atof(value.c_str());
				value.clear();
				break;

			case 10:
				m_deadAnimation->m_maxRepetitions = atoi(value.c_str());
				value.clear();
				break;

			case 11:
				m_life = atoi(value.c_str());
				value.clear();
				break;

			case 12:
				m_damage = atoi(value.c_str());
				value.clear();
				break;
			}
		}
	}

	m_moveAnimation->m_frameHeight = m_moveAnimation->m_sprite->getHeight();
	m_moveAnimation->m_frameWidth = m_moveAnimation->m_sprite->getWidth() / m_moveAnimation->m_numOfFrames;

	m_deadAnimation->m_frameHeight = m_deadAnimation->m_sprite->getHeight();
	m_deadAnimation->m_frameWidth = m_deadAnimation->m_sprite->getWidth() / m_deadAnimation->m_numOfFrames;
}