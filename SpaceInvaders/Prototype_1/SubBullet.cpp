#include "stdafx.h"

SubBullet::SubBullet()
{

}

SubBullet::~SubBullet()
{

}

void SubBullet::init()
{
	float resizeW = (float)(m_type->m_travelAnimation->m_frameWidth / 4);
	float resizeH = (float)(m_type->m_travelAnimation->m_frameHeight / 4);

	m_sizeW = (float)m_type->m_travelAnimation->m_frameWidth;
	m_sizeH = (float)m_type->m_travelAnimation->m_frameHeight;

	m_currentAnimation = m_type->m_travelAnimation;

	Pawn::init();

	m_colliderBox->SetSize(m_posX, m_posY, m_sizeW - resizeW, m_sizeH - resizeH);
	m_colliderBox->SetOffset(resizeW / 2, resizeH / 2);
}

void SubBullet::update(float _deltaTime)
{
	if (m_beDestroyed)
	{
		if (!m_dead)
		{
			m_colliderBox->SetEnabled(false);
			m_currentAnimation = m_type->m_deadAnimation;

			m_posY = m_posY - m_type->m_deadAnimation->m_frameHeight/2;

			m_dead = true;
		}


		if (m_type->m_deadAnimation->m_finished)
		{
			m_DestroyMe = true;
		}
	}
	else
	{
		m_posX += m_type->m_movementSpeed * _deltaTime * m_direction;

		if (m_posX < -100)
		{
			LCF::World::GetInstance().deleteActorByID(m_id);
		}

		if (m_posX > SCREEN_WIDTH)
		{
			LCF::World::GetInstance().deleteActorByID(m_id);
		}
	}

	m_currentAnimation->update(_deltaTime);
}

void SubBullet::collision(const Actor * _actor)
{
	if (const SkyEnemy* temp = dynamic_cast<const SkyEnemy*>(_actor))
	{
		if (!m_type->m_enemy)
		{
			m_type->m_impactSFX->play(-1);
		}
	}

	if (const GroundEnemy* temp = dynamic_cast<const GroundEnemy*>(_actor))
	{
		if (!m_type->m_enemy)
		{
			m_type->m_impactSFX->play(-1);
		}
	}

	if (const PlayerVehicle* temp = dynamic_cast<const PlayerVehicle*>(_actor))
	{
		if (m_type->m_enemy)
		{
			m_type->m_impactSFX->play(-1);
		}
	}
}

void SubBullet::setType(BulletType * _type)
{
	m_type = _type;
}