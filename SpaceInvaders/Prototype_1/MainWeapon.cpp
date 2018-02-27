#include "stdafx.h"

MainWeapon::MainWeapon()
{
	
}

MainWeapon::~MainWeapon()
{

}

void MainWeapon::init(Pawn * _Parent)
{
	Weapon::init(_Parent);

	m_posX = _Parent->m_posX;
	m_posY = _Parent->m_posY;
	m_sizeW = (float)m_weaponType->m_weaponTexture->getWidth();
	m_sizeH = (float)m_weaponType->m_weaponTexture->getHeight();

	Pawn::init();

	m_colliderBox->SetEnabled(false);
}

void MainWeapon::update(float _deltaTime)
{
	Weapon::update(_deltaTime);

	if (m_rateTimer < m_weaponType->m_rateOfFire)
	{
		m_rateTimer += _deltaTime;
	}
	else
	{
		m_canShoot = true;
	}
}

void MainWeapon::render(SDL_Renderer * _renderer)
{
	Weapon::render(_renderer);

	m_weaponType->m_shootAnimation->render(m_posX - m_sizeW/2+8, m_posY - m_sizeH/2, _renderer);
}

void MainWeapon::shoot()
{
	if (m_weaponSelected)
	{
		if (m_canShoot)
		{
			MainBullet* b = new MainBullet(m_posX + ((float)m_weaponType->m_weaponTexture->getWidth() / 2) - 10, m_posY - 40);
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
