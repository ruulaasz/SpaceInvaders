#include "stdafx.h"

GroundEnemy::GroundEnemy()
{

}

GroundEnemy::~GroundEnemy()
{

}

void GroundEnemy::init()
{
	m_sizeW = (float)m_type->m_moveAnimation->m_frameWidth;
	m_sizeH = (float)m_type->m_moveAnimation->m_frameHeight;

	m_currentAnimation = m_type->m_moveAnimation;

	m_type->m_moveSFX->play(-1, -1);
	m_life = m_type->m_life;

	Pawn::init();
}

void GroundEnemy::update(float _deltaTime)
{
	if (m_beDestroyed)
	{
		if (!m_dead)
		{
			LCF::AudioManager::GetInstance().StopChannel(m_type->m_moveSFX->m_currentChannel);
			m_type->m_deadSFX->play(-1);
			m_colliderBox->SetEnabled(false);
			m_dead = true;
			m_currentAnimation = m_type->m_deadAnimation;
		}

		if (!LCF::AudioManager::GetInstance().PlayingChannel(m_type->m_deadSFX->m_currentChannel))
		{
			m_DestroyMe = true;
		}
	}

	if (!m_dead)
	{
		m_posX += (m_direction * m_type->m_movementSpeed * _deltaTime);
	}

	m_currentAnimation->update(_deltaTime);
}

void GroundEnemy::collision(const Actor * _actor)
{
	if (const SubBullet* temp = dynamic_cast<const SubBullet*>(_actor))
	{
		recieveDamage(temp->m_damage);
		LCF::World::GetInstance().deleteActorByID(temp->m_id);
	}
}