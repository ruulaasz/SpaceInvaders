#include "stdafx.h"

SideWeaponB::SideWeaponB()
{
	m_rateOfFire = 0.8f;
}

SideWeaponB::~SideWeaponB()
{

}

void SideWeaponB::init(Pawn * _Parent)
{
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("SideWeaponA"));
	m_weaponReadyTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("SideWeaponA_Selected"));

	m_shootSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("shoot_subweapon"));
	m_changeWeaponSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("change_weapon"));

	m_Parent = _Parent;

	m_posY = SCREEN_HEIGHT - m_texture->getHeight();
	m_posX = SCREEN_WIDTH - m_texture->getWidth();
	m_sizeW = m_texture->getWidth();
	m_sizeH = m_texture->getHeight();
	Pawn::init();
}

void SideWeaponB::update(float _deltaTime)
{
	Weapon::update(_deltaTime);

	if (m_weaponSelected)
	{
		m_timer += _deltaTime;
	}

	if (m_timer > m_rateOfFire)
	{
		m_canShoot = true;
		m_timer = 0;
	}

	if (m_isShooting)
	{
		m_burstTimer += _deltaTime;

		if (m_bulletsFired < 3)
		{
			if (m_burstTimer > 0.05f)
			{
				m_bulletsFired++;
				int posX;
				m_burstTimer = 0;
				int posY = m_posY + m_texture->getHeight() / 2;

				if (m_direction > DIRECTION_STOP)
				{
					posX = m_Parent->m_posX + (m_Parent->m_texture->getWidth() + m_texture->getWidth());
				}
				else
				{
					posX = m_Parent->m_posX - m_texture->getWidth();
				}


				SubBullet* b = new SubBullet(posX, posY, m_direction);
				b->init();
				LCF::World::GetInstance().registerActor(b);

				m_shootSFX->play(SUBWEAPON_SHOOT_SFXCHANNEL);
			}
		}
		else
		{
			m_isShooting = false;
			m_bulletsFired = 0;
			m_timer = 0;
		}
	}
}

void SideWeaponB::shoot()
{
	if (m_weaponSelected)
	{
		if (m_canShoot)
		{
			if (!m_isShooting)
			{
				m_isShooting = true;
				m_canShoot = false;
			}
		}
	}
	else
	{
		m_weaponSelected = true;
		m_changeWeaponSFX->play(CHANGEWEAPON_SFXCHANNEL);
	}
}