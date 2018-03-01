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

	m_posY = _Parent->m_posY;
	m_posX = _Parent->m_posX;
	m_sizeW = (float)m_weaponType->m_weaponTexture->getWidth();
	m_sizeH = (float)m_weaponType->m_weaponTexture->getHeight();

	Pawn::init();
}

void SideWeapon::update(float _deltaTime)
{
	Weapon::update(_deltaTime);

	if (m_life <= 0)
	{
		m_colliderBox->SetEnabled(false);
	}

	if (m_rateTimer < m_weaponType->m_rateOfFire)
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
	if (!m_bulletType->m_enemy)
	{
		Weapon::render(_renderer);
	}

	int posx = 0;

	if (!m_bulletType->m_enemy)
	{
		posx = (m_weaponType->m_shootAnimation->m_frameWidth * m_direction);
		m_weaponType->m_shootAnimation->render(m_posX + posx, m_posY + m_sizeH / 4, _renderer);
	}
	else
	{
		posx = (m_weaponType->m_shootAnimation->m_frameWidth * m_direction);
		m_weaponType->m_shootAnimation->render(m_posX, m_posY + m_Parent->m_sizeH/2 - m_weaponType->m_shootAnimation->m_frameWidth/2, _renderer);
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

			if (!b->m_type->m_enemy)
			{
				posY = (int)m_posY + m_weaponType->m_weaponTexture->getHeight() / 2;
			}
			else
			{
				posY = (int)m_posY + m_Parent->m_sizeH - m_weaponType->m_weaponTexture->getHeight() / 2;
			}

			if (m_direction > DIRECTION_STOP)
			{
				if (!b->m_type->m_enemy)
				{
					posX = (int)m_Parent->m_posX + m_Parent->m_sizeW - m_sizeW;
				}
				else
				{
					posX = (int)m_Parent->m_posX + m_Parent->m_sizeW + m_bulletType->m_travelAnimation->m_frameWidth;
				}
			}
			else
			{
				posX = (int)m_Parent->m_posX - m_sizeW - m_bulletType->m_travelAnimation->m_frameWidth;
			}

			b->m_posX = posX;
			b->m_posY = posY;
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