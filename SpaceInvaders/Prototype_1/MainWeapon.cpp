#include "stdafx.h"

MainWeapon::MainWeapon()
{
	m_rateOfFire = 0.2f;
}

MainWeapon::~MainWeapon()
{

}

void MainWeapon::init(Pawn * _Parent)
{
	Weapon::init(_Parent);

	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("MainWeapon"));
	m_weaponReadyTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("MainWeapon_Selected"));
	m_shootSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("shoot_mainweapon"));

	m_posX = _Parent->m_posX;
	m_posY = _Parent->m_posY;
	m_sizeW = m_texture->getWidth();
	m_sizeH = m_texture->getHeight();

	Pawn::init();

	m_colliderBox->SetEnabled(false);
}

void MainWeapon::update(float _deltaTime)
{
	Weapon::update(_deltaTime);

	if (m_rateTimer < m_rateOfFire)
	{
		m_rateTimer += _deltaTime;
	}
	else
	{
		m_canShoot = true;
	}
}

void MainWeapon::shoot()
{
	if (m_weaponSelected)
	{
		if (m_canShoot)
		{
			MainBullet* b = new MainBullet(m_posX + (m_texture->getWidth() / 2) - 10, m_posY - 20);
			b->init();
			LCF::World::GetInstance().registerActor(b);

			m_shootSFX->play(-1);

			m_canShoot = false;
			m_rateTimer = 0;
		}
	}
	else
	{
		m_weaponSelected = true;
		m_changeWeaponSFX->play(-1);
	}
}
