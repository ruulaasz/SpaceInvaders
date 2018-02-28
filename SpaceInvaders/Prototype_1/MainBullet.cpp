#include "stdafx.h"

MainBullet::MainBullet()
{

}

MainBullet::~MainBullet()
{

}

void MainBullet::init()
{
	m_sizeW = (float)m_type->m_travelAnimation->m_frameWidth - 10;
	m_sizeH = (float)m_type->m_travelAnimation->m_frameHeight - 10;

	m_currentAnimation = m_type->m_travelAnimation;

	Pawn::init();

	m_colliderBox->SetOffset(5, 5);
}

void MainBullet::render(SDL_Renderer * _renderer)
{
	m_currentAnimation->render((int)m_posX, (int)m_posY, _renderer);
}

void MainBullet::update(float _deltaTime)
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
		if (!m_type->m_enemy)
		{
			m_posY -= m_type->m_movementSpeed * _deltaTime;
		}
		else
		{
			m_posY += m_type->m_movementSpeed * _deltaTime;
		}

		if (m_posY < -100)
		{
			LCF::World::GetInstance().deleteActorByID(m_id);
		}
	}

	m_currentAnimation->update(_deltaTime);
	
}

void MainBullet::collision(const Actor * _actor)
{
	if (const SkyEnemy* temp = dynamic_cast<const SkyEnemy*>(_actor))
	{
		m_type->m_impactSFX->play(-1);
	}

	if (const PlayerVehicle* temp = dynamic_cast<const PlayerVehicle*>(_actor))
	{
		m_type->m_impactSFX->play(-1);
	}
}

void MainBullet::setType(BulletType * _type)
{
	m_type = _type;
}