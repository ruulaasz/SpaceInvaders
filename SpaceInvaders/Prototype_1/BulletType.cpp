#include "stdafx.h"

BulletType::BulletType()
{
	m_travelAnimation = new LCF::Animator();
	m_deadAnimation = new LCF::Animator();
}

BulletType::BulletType(const BulletType & _type)
{
	m_damage = _type.m_damage;
	m_deadAnimation = new LCF::Animator(*_type.m_deadAnimation);
	m_impactSFX = _type.m_impactSFX;
	m_movementSpeed = _type.m_movementSpeed;
	m_travelAnimation = new LCF::Animator(*_type.m_travelAnimation);
	m_enemy = _type.m_enemy;
}

BulletType::~BulletType()
{

}

void BulletType::init(std::string _info)
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
				m_impactSFX = new LCF::Sfx(*reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset(value)));
				value.clear();
				break;

			case 2:
				m_movementSpeed = (float)atof(value.c_str());
				value.clear();
				break;

			case 3:
				m_damage = atoi(value.c_str());
				value.clear();
				break;

			case 4:
				m_travelAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset(value));
				value.clear();
				break;

			case 5:
				m_travelAnimation->m_numOfFrames = atoi(value.c_str());
				value.clear();
				break;

			case 6:
				m_travelAnimation->m_animSpeed = (float)atof(value.c_str());
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
				m_deadAnimation->m_animSpeed = (float)atof(value.c_str());
				value.clear();
				break;

			case 10:
				m_deadAnimation->m_maxRepetitions = atoi(value.c_str());
				value.clear();
				break;

			case 11:
				if (atoi(value.c_str()) == 0)
				{
					m_enemy = false;
				}
				else
				{
					m_enemy = true;
				}
				value.clear();
				break;
			}
		}
	}

	m_travelAnimation->m_frameHeight = m_travelAnimation->m_sprite->getHeight();
	m_travelAnimation->m_frameWidth = m_travelAnimation->m_sprite->getWidth() / m_travelAnimation->m_numOfFrames;

	m_deadAnimation->m_frameHeight = m_deadAnimation->m_sprite->getHeight();
	m_deadAnimation->m_frameWidth = m_deadAnimation->m_sprite->getWidth() / m_deadAnimation->m_numOfFrames;
}