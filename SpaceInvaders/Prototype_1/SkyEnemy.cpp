#include "stdafx.h"

SkyEnemy::SkyEnemy()
{
	/*m_movementSpeed = 100.f;
	m_life = 100;
	m_damage = 10;*/
}

SkyEnemy::~SkyEnemy()
{
	
}

void SkyEnemy::init()
{
	m_sizeW = (float)m_type->m_moveAnimation->m_frameWidth;
	m_sizeH = (float)m_type->m_moveAnimation->m_frameHeight;
	
	m_currentAnimation = m_type->m_moveAnimation;

	m_type->m_moveSFX->play(-1, -1);

	m_life = m_type->m_life;

	Pawn::init();
}

void SkyEnemy::update(float _deltaTime)
{
	//if (m_posY > 780 && m_dead != true)
	//{
	//	LCF::World::GetInstance().deleteActorByID(m_id);
	//}

	if (m_beDestroyed)
	{
		if (!m_dead)
		{
			LCF::AudioManager::GetInstance().StopChannel(m_type->m_moveSFX->m_currentChannel);
			m_type->m_deadSFX->play(-1);
			m_colliderBox->SetEnabled(false);
			m_currentAnimation = m_type->m_deadAnimation;
			m_dead = true;
		}

		if (!LCF::AudioManager::GetInstance().PlayingChannel(m_type->m_deadSFX->m_currentChannel))
		{
			m_DestroyMe = true;
		}
	}

	if (!m_dead)
	{
		m_posY += (m_type->m_movementSpeed * _deltaTime);
	}

	m_currentAnimation->update(_deltaTime);
}

void SkyEnemy::collision(const Actor * _actor)
{
	if (const MainBullet* temp = dynamic_cast<const MainBullet*>(_actor))
	{
		if (!temp->m_enemy)
		{
			recieveDamage(temp->m_damage);
			LCF::World::GetInstance().deleteActorByID(temp->m_id);
		}
	}

	if (const SubBullet* temp = dynamic_cast<const SubBullet*>(_actor))
	{
		if (!temp->m_enemy)
		{
			recieveDamage(temp->m_damage);
			LCF::World::GetInstance().deleteActorByID(temp->m_id);
		}
	}
}