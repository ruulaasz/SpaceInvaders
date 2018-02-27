#include "stdafx.h"

GroundEnemy::GroundEnemy()
{
	m_movementSpeed = 50.f;
	m_life = 25;
	m_damage = 10;
}

GroundEnemy::~GroundEnemy()
{

}

void GroundEnemy::init()
{
	m_moveAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("meteor_small"));
	m_moveAnimation->m_frameHeight = m_moveAnimation->m_sprite->getHeight();
	m_moveAnimation->m_numOfFrames = 5;
	m_moveAnimation->m_frameWidth = m_moveAnimation->m_sprite->getWidth() / m_moveAnimation->m_numOfFrames;
	m_moveAnimation->m_animSpeed = 0.1f;

	m_deadAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("meteor_small_dead"));
	m_deadAnimation->m_frameHeight = m_deadAnimation->m_sprite->getHeight();
	m_deadAnimation->m_numOfFrames = 5;
	m_deadAnimation->m_frameWidth = m_deadAnimation->m_sprite->getWidth() / m_deadAnimation->m_numOfFrames;
	m_deadAnimation->m_animSpeed = 0.1f;
	m_deadAnimation->m_maxRepetitions = 1;

	m_moveSFX = new LCF::Sfx(*reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("skyenemy")));
	m_deadSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("skyenemy_dead"));

	m_sizeW = (float)m_moveAnimation->m_frameWidth;
	m_sizeH = (float)m_moveAnimation->m_frameHeight;

	m_currentAnimation = m_moveAnimation;

	m_moveSFX->play(-1, -1);

	Pawn::init();
}

void GroundEnemy::update(float _deltaTime)
{
	if (m_beDestroyed)
	{
		if (!m_dead)
		{
			LCF::AudioManager::GetInstance().StopChannel(m_moveSFX->m_currentChannel);
			m_deadSFX->play(-1);
			m_colliderBox->SetEnabled(false);
			m_dead = true;
			m_currentAnimation = m_deadAnimation;
		}

		if (!LCF::AudioManager::GetInstance().PlayingChannel(m_deadSFX->m_currentChannel))
		{
			m_DestroyMe = true;
		}
	}

	if (!m_dead)
	{
		m_posX += (m_direction * m_movementSpeed * _deltaTime);
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