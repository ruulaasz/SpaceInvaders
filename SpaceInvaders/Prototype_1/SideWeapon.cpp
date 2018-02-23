#include "stdafx.h"

SideWeapon::SideWeapon()
{
	m_rateOfFire = 0.3f;
	m_life = 10;
}

SideWeapon::~SideWeapon()
{

}

void SideWeapon::init(Pawn* _Parent)
{
	Weapon::init(_Parent);

	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("SideWeaponA"));
	m_weaponReadyTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("SideWeaponA_Selected"));

	m_shootSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("shoot_subweapon"));

	m_posY = _Parent->m_posY;
	m_posX = _Parent->m_posX;
	m_sizeW = m_texture->getWidth();
	m_sizeH = m_texture->getHeight();

	Pawn::init();

	m_shieldCollider = new SideWeaponBox();
	m_shieldCollider->SetActor(this);
	m_shieldCollider->SetFunction(&SideWeapon::shieldColision);
	m_shieldCollider->SetSize(m_posX, m_posY, m_sizeW, m_sizeH);
	LCF::ColliderManager::GetInstance().RegistrerCollider(m_shieldCollider);

	m_colliderBox->SetEnabled(false);
}

void SideWeapon::update(float _deltaTime)
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
		m_shieldCollider->SetEnabled(false);
	}

	if (m_rateTimer < m_rateOfFire)
	{
		m_rateTimer += _deltaTime;
	}
	else
	{
		m_canShoot = true;
	}
}

void SideWeapon::collision(const Actor * _actor)
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

void SideWeapon::shieldColision(const Actor * _actor)
{
	
}