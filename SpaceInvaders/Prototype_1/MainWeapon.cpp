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
	if (!m_bulletType->m_enemy)
	{
		Weapon::render(_renderer);
	}

	if (!m_bulletType->m_enemy)
	{
		m_weaponType->m_shootAnimation->render(m_posX + m_weaponType->m_shootAnimation->m_frameWidth / 2, m_posY - m_sizeH / 2, _renderer);
	}
	else
	{
		m_weaponType->m_shootAnimation->render(m_Parent->m_posX + m_Parent->m_sizeW/2 - m_weaponType->m_shootAnimation->m_frameWidth / 2, m_Parent->m_posY + m_Parent->m_sizeH, _renderer);
	}
}

void MainWeapon::shoot()
{
	if (m_weaponSelected)
	{
		if (m_canShoot)
		{
			MainBullet* b = new MainBullet();
			b->m_type = new BulletType(*m_bulletType);
			b->init();
			
			if (!b->m_type->m_enemy)
			{
				b->m_posX = m_posX + ((float)m_weaponType->m_weaponTexture->getWidth() / 2) - (b->m_type->m_travelAnimation->m_frameWidth / 2);
				b->m_posY = m_posY - b->m_type->m_travelAnimation->m_frameHeight * 1.5;
			}
			else
			{
				b->m_posX = m_posX + m_Parent->m_sizeW/2 - b->m_sizeW/2;
				b->m_posY = m_posY + m_Parent->m_sizeH + m_weaponType->m_shootAnimation->m_frameHeight;
			}

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