#include "stdafx.h"

WeaponType::WeaponType()
{
	m_shootAnimation = new LCF::Animator();
}

WeaponType::WeaponType(const WeaponType & _type)
{
	m_rateOfFire = _type.m_rateOfFire;
	m_weaponTexture = _type.m_weaponTexture;
	m_weaponReadyTexture = _type.m_weaponReadyTexture;
	m_shootAnimation = new LCF::Animator(*_type.m_shootAnimation);
	m_shootSFX = new LCF::Sfx(*_type.m_shootSFX);
	m_bulletType = _type.m_bulletType;
	m_life = _type.m_life;
}

WeaponType::~WeaponType()
{

}

void WeaponType::init(std::string _info)
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
				m_rateOfFire = (float)atof(value.c_str());
				value.clear();
				break;

			case 2:
				m_weaponTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset(value));
				value.clear();
				break;

			case 3:
				m_weaponReadyTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset(value));
				value.clear();
				break;

			case 4:
				m_shootAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset(value));
				value.clear();
				break;

			case 5:
				m_shootAnimation->m_numOfFrames = atoi(value.c_str());
				value.clear();
				break;

			case 6:
				m_shootAnimation->m_animSpeed = (float)atof(value.c_str());
				value.clear();
				break;

			case 7:
				m_shootSFX = new LCF::Sfx(*reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset(value)));
				value.clear();
				break;

			case 8:
				m_bulletType = value;
				value.clear();
				break;

			case 9:
				m_life = atoi(value.c_str());
				value.clear();
				break;
			}
		}
	}

	m_shootAnimation->m_frameHeight = m_shootAnimation->m_sprite->getHeight();
	m_shootAnimation->m_frameWidth = m_shootAnimation->m_sprite->getWidth() / m_shootAnimation->m_numOfFrames;
	m_shootAnimation->m_maxRepetitions = 1;
	m_shootAnimation->m_finished = true;
}