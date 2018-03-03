#include "stdafx.h"

MainBullet::MainBullet()
{

}

MainBullet::~MainBullet()
{

}

void MainBullet::init()
{
	float resizeW = float(m_type->m_travelAnimation->m_frameWidth / 4);
	float resizeH = float(m_type->m_travelAnimation->m_frameHeight / 4);

	m_transform.m_sizeW = (float)m_type->m_travelAnimation->m_frameWidth;
	m_transform.m_sizeH = (float)m_type->m_travelAnimation->m_frameHeight;

	m_currentAnimation = m_type->m_travelAnimation;

	Pawn::init();

	m_colliderBox->SetSize(m_transform.m_posX, m_transform.m_posY, m_transform.m_sizeW - resizeW, m_transform.m_sizeH - resizeH);
	m_colliderBox->SetOffset(resizeW / 2, resizeH / 2);
}

void MainBullet::update(float _deltaTime)
{
	if (m_beDestroyed)
	{
		if (!m_dead)
		{
			m_colliderBox->SetEnabled(false);
			m_currentAnimation = m_type->m_deadAnimation;

			if (!m_type->m_enemy)
			{
				m_transform.m_posY = m_transform.m_posY - m_transform.m_sizeH;
			}
			else
			{

			}

			m_dead = true;
		}

		if (m_type->m_deadAnimation->m_finished)
		{
			m_DestroyMe = true;
		}
	}
	else
	{
		if (!m_type->m_enemy)
		{
			m_transform.m_posY -= m_type->m_movementSpeed * _deltaTime;

			if (m_transform.m_posY < -100)
			{
				LCF::World::GetInstance().deleteActorByID(m_id);
			}
		}
		else
		{
			m_transform.m_posY += m_type->m_movementSpeed * _deltaTime;

			if (m_transform.m_posY > 750)
			{
				LCF::World::GetInstance().deleteActorByID(m_id);
			}
		}
	}

	m_currentAnimation->update(_deltaTime);
}

void MainBullet::collision(const Actor * _actor)
{
	
}

void MainBullet::setType(BulletType * _type)
{
	m_type = _type;
}