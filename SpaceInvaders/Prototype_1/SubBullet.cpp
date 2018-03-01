#include "stdafx.h"

SubBullet::SubBullet()
{

}

SubBullet::~SubBullet()
{

}

void SubBullet::init()
{
	m_sizeW = (float)m_type->m_travelAnimation->m_frameWidth;
	m_sizeH = (float)m_type->m_travelAnimation->m_frameHeight;

	m_currentAnimation = m_type->m_travelAnimation;

	Pawn::init();
}

void SubBullet::update(float _deltaTime)
{
	if (m_beDestroyed)
	{
		m_colliderBox->SetEnabled(false);

		m_currentAnimation = m_type->m_deadAnimation;

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

void SubBullet::render(SDL_Renderer * _renderer)
{
	m_currentAnimation->render((int)m_posX, (int)m_posY, _renderer);
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