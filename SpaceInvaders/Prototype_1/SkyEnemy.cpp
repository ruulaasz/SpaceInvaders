#include "stdafx.h"

SkyEnemy::SkyEnemy()
{
	m_movementSpeed = 100.f;
	m_life = 100;
	m_damage = 10;
}

SkyEnemy::~SkyEnemy()
{
	
}

void SkyEnemy::init()
{
	m_moveAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("meteor"));
	m_moveAnimation->m_frameHeight = m_moveAnimation->m_sprite->getHeight();
	m_moveAnimation->m_numOfFrames = 5;
	m_moveAnimation->m_frameWidth = m_moveAnimation->m_sprite->getWidth() / m_moveAnimation->m_numOfFrames;
	m_moveAnimation->m_animSpeed = 0.1f;

	m_deadAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("meteor_dead"));
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

	m_weapon = new MainWeapon();
	m_weapon->init(this);
	m_weapon->m_direction = DIRECTION_STOP;
	m_weapon->m_weaponSelected = true;

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
			LCF::AudioManager::GetInstance().StopChannel(m_moveSFX->m_currentChannel);
			m_deadSFX->play(-1);
			m_colliderBox->SetEnabled(false);
			m_currentAnimation = m_deadAnimation;
			m_dead = true;
		}

		if (!LCF::AudioManager::GetInstance().PlayingChannel(m_deadSFX->m_currentChannel))
		{
			m_DestroyMe = true;
		}
	}

	if (!m_dead)
	{
		m_posY += (m_movementSpeed * _deltaTime);
		m_weapon->update(_deltaTime);
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