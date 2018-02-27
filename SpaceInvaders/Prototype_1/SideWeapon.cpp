#include "stdafx.h"

SideWeapon::SideWeapon()
{
	m_rateOfFire = 0.3f;
	m_life = 100;
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

	m_shootAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("main_weapon_shoot"));
	m_shootAnimation->m_frameHeight = 32;
	m_shootAnimation->m_frameWidth = 90;
	m_shootAnimation->m_animSpeed = 0.04f;
	m_shootAnimation->m_numOfFrames = 8;
	m_shootAnimation->m_maxRepetitions = 1;
	m_shootAnimation->m_finished = true;

	m_posY = _Parent->m_posY;
	m_posX = _Parent->m_posX;
	m_sizeW = (float)m_texture->getWidth();
	m_sizeH = (float)m_texture->getHeight();

	Pawn::init();
}

void SideWeapon::update(float _deltaTime)
{
	Weapon::update(_deltaTime);

	if (m_life <= 0)
	{
		m_colliderBox->SetEnabled(false);
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

void SideWeapon::render(SDL_Renderer * _renderer)
{
	Weapon::render(_renderer);

	m_shootAnimation->render(m_posX - m_sizeW + (28 * m_direction), m_posY + m_sizeH/4, _renderer);
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
			
			posY = (int)m_posY + m_texture->getHeight() / 2;

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
			
			m_canShoot = false;
			m_rateTimer = 0;

			m_shootAnimation->resetAnimation();
		}
	}
	else
	{
		m_weaponSelected = true;
		m_changeWeaponSFX->play(-1);
	}
}