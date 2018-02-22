#include "stdafx.h"

SideWeapon::SideWeapon()
{
	m_rateOfFire = 0.3f;
}

SideWeapon::~SideWeapon()
{

}

void SideWeapon::init(Pawn* _Parent)
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

void SideWeapon::update(float _deltaTime)
{
	Weapon::update(_deltaTime);

	if (m_timer < m_rateOfFire)
	{
		m_timer += _deltaTime;
	}
	else
	{
		m_canShoot = true;
	}
}

void SideWeapon::shoot()
{
	int posX;
	int posY;
	
	if (m_weaponSelected)
	{
		if (m_canShoot)
		{
			
			posY = m_posY + m_texture->getHeight() / 2;

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
			
			m_canShoot = false;
			m_timer = 0;
		}
	}
	else
	{
		m_weaponSelected = true;
		m_changeWeaponSFX->play(CHANGEWEAPON_SFXCHANNEL);
	}
}