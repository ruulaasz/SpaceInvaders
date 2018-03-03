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

	float resizeW = (float)(m_weaponType->m_weaponTexture->getWidth() / 4);
	float resizeH = (float)(m_weaponType->m_weaponTexture->getHeight() / 4);

	m_posY = _Parent->m_posY;
	m_posX = _Parent->m_posX;

	m_sizeW = (float)m_weaponType->m_weaponTexture->getWidth();
	m_sizeH = (float)m_weaponType->m_weaponTexture->getHeight();

	Pawn::init();

	m_colliderBox->SetSize(m_posX, m_posY, m_sizeW - resizeW, m_sizeH - resizeH);
	m_colliderBox->SetOffset(resizeW / 2, resizeH / 2);
}

void SideWeapon::update(float _deltaTime)
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

void SideWeapon::render(SDL_Renderer * _renderer, bool _flip)
{
	if (!m_weaponType->m_enemy)
	{
		Weapon::render(_renderer, _flip);
	}

	if (m_direction > 0)
	{
		if (!m_weaponType->m_enemy)
		{
			m_weaponType->m_shootAnimation->render(m_posX, m_posY, _renderer);
		}
		else
		{
			m_weaponType->m_shootAnimation->render(m_posX, m_posY, _renderer, true);
		}
	}
	else
	{
		if (!m_weaponType->m_enemy)
		{
			m_weaponType->m_shootAnimation->render(m_posX - m_sizeW / 2, m_posY, _renderer, true);
		}
		else
		{
			m_weaponType->m_shootAnimation->render(m_posX, m_posY, _renderer);
		}
	}
}

void SideWeapon::collision(const Actor * _actor)
{
	if (const SubBullet* temp = dynamic_cast<const SubBullet*>(_actor))
	{
		if (temp->m_type->m_enemy)
		{
			recieveDamage(temp->m_type->m_damage);
			LCF::World::GetInstance().deleteActorByID(temp->m_id);
		}
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
			SubBullet* b = new SubBullet();
			b->m_direction = m_direction;
			b->m_type = new BulletType(*m_bulletType);
			b->init();
			b->m_type->m_enemy = m_weaponType->m_enemy;

			posY = int(m_posY + m_weaponType->m_weaponTexture->getHeight() / 2);

			if (m_direction > DIRECTION_STOP)
			{
				posX = int(m_Parent->m_posX + m_Parent->m_sizeW + m_sizeW);
			}
			else
			{
				posX = int(m_Parent->m_posX - m_sizeW - m_bulletType->m_travelAnimation->m_frameWidth);
			}

			b->m_posX = (float)posX;
			b->m_posY = (float)posY;
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