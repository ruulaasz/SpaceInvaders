#include "stdafx.h"

SideWeaponB::SideWeaponB()
{
	m_rateOfFire = 0.8f;
	m_life = 10;
}

SideWeaponB::~SideWeaponB()
{

}

void SideWeaponB::init(Pawn * _Parent)
{
	Weapon::init(_Parent);

	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("SideWeaponA"));
	m_weaponReadyTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("SideWeaponA_Selected"));

	m_shootSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("shoot_subweapon"));

	m_posY = _Parent->m_posY;
	m_posX = _Parent->m_posX;
	m_sizeW = (float)m_texture->getWidth();
	m_sizeH = (float)m_texture->getHeight();

	Pawn::init();
}

void SideWeaponB::update(float _deltaTime)
{
	Weapon::update(_deltaTime);
	if (m_beDestroyed)
	{
		//animacion o cualquier cosa que se requiera
		//Usar esta bandera para que el manager lo elimine
		m_DestroyMe = true;
	}
	if (m_life <= 0)
	{
		m_colliderBox->SetEnabled(false);
	}

	if (m_weaponSelected)
	{
		m_rateTimer += _deltaTime;
	}

	if (m_rateTimer > m_rateOfFire)
	{
		m_canShoot = true;
		m_rateTimer = 0;
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
				int posY = (int)m_posY + m_texture->getHeight() / 2;

				if (m_direction > DIRECTION_STOP)
				{
					posX = (int)m_Parent->m_posX + (m_Parent->m_texture->getWidth() + m_texture->getWidth());
				}
				else
				{
					posX = (int)m_Parent->m_posX - m_texture->getWidth();
				}


				SubBullet* b = new SubBullet((float)posX, (float)posY, m_direction);
				b->init();
				LCF::World::GetInstance().registerActor(b);

				m_shootSFX->play(-1);
			}
		}
		else
		{
			m_isShooting = false;
			m_bulletsFired = 0;
			m_rateTimer = 0;
		}
	}
}

void SideWeaponB::collision(const Actor * /*_actor*/)
{

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
		m_changeWeaponSFX->play(-1);
	}
}