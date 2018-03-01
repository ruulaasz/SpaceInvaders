#include "stdafx.h"

GroundEnemy::GroundEnemy()
{

}

GroundEnemy::~GroundEnemy()
{

}

void GroundEnemy::init()
{
	float resizeW = float(m_type->m_moveAnimation->m_frameWidth / 4);
	float resizeH = float(m_type->m_moveAnimation->m_frameHeight / 4);

	m_sizeW = (float)m_type->m_moveAnimation->m_frameWidth;
	m_sizeH = (float)m_type->m_moveAnimation->m_frameHeight;

	m_currentAnimation = m_type->m_moveAnimation;

	m_type->m_moveSFX->play(-1, -1);

	m_weapon->init(this);
	m_weapon->m_weaponSelected = true;
	m_weapon->m_direction = m_direction;

	m_weapon->m_colliderBox->SetEnabled(false);

	Pawn::init();

	m_colliderBox->SetSize(m_posX, m_posY, m_sizeW - resizeW, m_sizeH - resizeH);
	m_colliderBox->SetOffset(resizeW / 2, resizeH / 2);
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
			m_currentAnimation = m_type->m_deadAnimation;
			m_dead = true;
		}
		
		if (!LCF::AudioManager::GetInstance().PlayingChannel(m_type->m_deadSFX->m_currentChannel))
		{
			m_DestroyMe = true;
		}
	}
	else
	{
		m_posX += (m_direction * m_type->m_movementSpeed * _deltaTime);

		if (!m_dead)
		{
			m_weapon->update(_deltaTime);
		}
	}

	m_currentAnimation->update(_deltaTime);
}

void GroundEnemy::render(SDL_Renderer * _renderer)
{
	Enemy::render(_renderer);

	if (!m_dead)
	{
		m_weapon->render(_renderer);
	}
}

void GroundEnemy::collision(const Actor * _actor)
{
	if (const SubBullet* temp = dynamic_cast<const SubBullet*>(_actor))
	{
		if (!temp->m_type->m_enemy)
		{
			recieveDamage(temp->m_type->m_damage);
			LCF::World::GetInstance().deleteActorByID(temp->m_id);
		}

		//m_weapon->shoot();
	}
}

void GroundEnemy::setType(EnemyType * _type)
{
	m_type = _type;
	m_life = m_type->m_life;
}