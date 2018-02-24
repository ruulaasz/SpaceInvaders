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
		m_weaponReadyTexture->render(m_posX, m_posY, _renderer);
	}
	else
	{
		m_texture->render(m_posX, m_posY, _renderer);
	}
}

void Weapon::update(float /*_deltaTime*/)
{
	if (m_direction > DIRECTION_STOP)
	{
		m_posX = m_Parent->m_posX + m_Parent->m_texture->getWidth();
	}
	
	if (m_direction < DIRECTION_STOP)
	{
		m_posX = m_Parent->m_posX - m_texture->getWidth();
	}
	
	if (m_direction == DIRECTION_STOP)
	{
		m_posX = m_Parent->m_posX;
	}
}

void Weapon::collision(const Actor * _actor)
{

}

void Weapon::recieveDamage(int _damage)
{
	m_life -= _damage;
}