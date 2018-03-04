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

	m_transform.m_posX = _Parent->m_transform.m_posX;
	m_transform.m_posY = _Parent->m_transform.m_posY;

	m_transform.m_sizeW = (float)m_weaponType->m_weaponTexture->getWidth();
	m_transform.m_sizeH = (float)m_weaponType->m_weaponTexture->getHeight();

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

void MainWeapon::render(bool _flip)
{
	if (!m_weaponType->m_enemy)
	{
		//Weapon::render(_flip);
	}

	if (!m_weaponType->m_enemy)
	{
		m_weaponType->m_shootAnimation->render(int(m_transform.m_posX + m_weaponType->m_shootAnimation->m_frameWidth / 2), int(m_transform.m_posY - m_transform.m_sizeH / 2), _flip);
	}
	else
	{
		m_weaponType->m_shootAnimation->render(int(m_transform.m_posX), int(m_transform.m_posY), _flip);
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
			b->m_type->m_enemy = m_weaponType->m_enemy;
			
			if (!b->m_type->m_enemy)
			{
				b->m_transform.m_posX = m_transform.m_posX + (m_transform.m_sizeW / 2) - (b->m_type->m_travelAnimation->m_frameWidth / 2);
				b->m_transform.m_posY = m_transform.m_posY - float(b->m_type->m_travelAnimation->m_frameHeight) - m_weaponType->m_shootAnimation->m_frameHeight/2;
			}
			else
			{
				b->m_transform.m_posX = m_transform.m_posX + m_Parent->m_transform.m_sizeW/2 - b->m_transform.m_sizeW/2;
				b->m_transform.m_posY = m_transform.m_posY + m_Parent->m_transform.m_sizeH + m_weaponType->m_shootAnimation->m_frameHeight/2;
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