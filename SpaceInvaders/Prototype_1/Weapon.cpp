#include "stdafx.h"

Weapon::Weapon()
{

}

Weapon::~Weapon()
{

}

void Weapon::init(Pawn * _Parent)
{
	m_changeWeaponSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("change_weapon"));

	m_Parent = _Parent;
	m_posX = _Parent->m_posX;
	m_posY = _Parent->m_posY;

	m_canShoot = true;
}

void Weapon::render(SDL_Renderer * _renderer)
{
	if (m_weaponSelected)
	{
		m_weaponType->m_weaponReadyTexture->render((int)m_posX, (int)m_posY, _renderer);
	}
	else
	{
		m_weaponType->m_weaponTexture->render((int)m_posX, (int)m_posY, _renderer);
	}
}

void Weapon::update(float _deltaTime)
{
	if (m_direction > DIRECTION_STOP)
	{
		m_posX = m_Parent->m_posX + m_Parent->m_sizeW;
	}
	
	if (m_direction < DIRECTION_STOP)
	{
		m_posX = m_Parent->m_posX - m_weaponType->m_weaponTexture->getWidth();
	}
	
	if (m_direction == DIRECTION_STOP)
	{
		m_posX = m_Parent->m_posX;
		m_posY = m_Parent->m_posY;
	}

	m_weaponType->m_shootAnimation->update(_deltaTime);
}

void Weapon::collision(const Actor * /*_actor*/)
{

}

void Weapon::recieveDamage(int _damage)
{
	if (!m_dead)
	{
		m_life -= _damage;

		FallingText* fall = new FallingText();

		fall->m_String = std::to_string(_damage);
		fall->m_posX = m_posX;
		fall->m_posY = m_posY - (m_sizeH / 2);
		fall->m_originPosX = fall->m_posX;
		fall->m_originPosY = fall->m_posY;

		SDL_Color c;
		c.r = 0;
		c.g = 0;
		c.b = 0;

		fall->m_color = c;

		TextManager::GetInstance().m_fallingText.push_back(fall);

		if (m_life <= 0)
		{
			m_dead = true;
		}
	}
}

void Weapon::setType(WeaponType * _type)
{
	m_weaponType = _type;
	m_life = _type->m_life;
}