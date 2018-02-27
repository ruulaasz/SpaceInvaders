#include "stdafx.h"

SideWeapon::SideWeapon()
{

}

SideWeapon::~SideWeapon()
{

}

void SideWeapon::init(Pawn* _Parent)
{
	Weapon::init(_Parent);

	m_posY = _Parent->m_posY;
	m_posX = _Parent->m_posX;
	m_sizeW = (float)m_weaponType->m_weaponTexture->getWidth();
	m_sizeH = (float)m_weaponType->m_weaponTexture->getHeight();

	Pawn::init();
}

void SideWeapon::update(float _deltaTime)
{
	Weapon::update(_deltaTime);

	if (m_life <= 0)
	{
		m_colliderBox->SetEnabled(false);
	}

	if (m_rateTimer < m_weaponType->m_rateOfFire)
	{
		m_rateTimer += _deltaTime;
	}
	else
	{
		m_canShoot = true;
	}
}

void SideWeapon::render(SDL_Renderer * _renderer)
{
	Weapon::render(_renderer);

	m_weaponType->m_shootAnimation->render(m_posX - m_sizeW + (28 * m_direction), m_posY + m_sizeH/4, _renderer);
}

void SideWeapon::collision(const Actor * /*_actor*/)
{

}

void SideWeapon::shoot()
{
	int posX;
	int posY;
	
	if (m_weaponSelected)
	{
		if (m_canShoot)
		{
			
			posY = (int)m_posY + m_weaponType->m_weaponTexture->getHeight() / 2;

			if (m_direction > DIRECTION_STOP)
			{
				posX = (int)m_Parent->m_posX + (m_Parent->m_texture->getWidth() + m_weaponType->m_weaponTexture->getWidth());
			}
			else
			{
				posX = (int)m_Parent->m_posX - m_weaponType->m_weaponTexture->getWidth();
			}
			
			SubBullet* b = new SubBullet((float)posX, (float)posY, m_direction);
			b->init();
			LCF::World::GetInstance().registerActor(b);

			m_weaponType->m_shootSFX->play(-1);
			
			m_canShoot = false;
			m_rateTimer = 0;

			m_weaponType->m_shootAnimation->resetAnimation();
		}
	}
	else
	{
		m_weaponSelected = true;
		m_changeWeaponSFX->play(-1);
	}
}