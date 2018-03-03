#include "stdafx.h"

SkyEnemy::SkyEnemy()
{
	m_shootTimer = 0.f;
	m_shootTime = 6.5f;
}

SkyEnemy::~SkyEnemy()
{
	
}

void SkyEnemy::init()
{
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("MainWeapon"));

	float resizeW = (float)(m_type->m_moveAnimation->m_frameWidth / 4);
	float resizeH = (float)(m_type->m_moveAnimation->m_frameHeight / 4);

	m_sizeW = (float)m_type->m_moveAnimation->m_frameWidth;
	m_sizeH = (float)m_type->m_moveAnimation->m_frameHeight;
	
	m_currentAnimation = m_type->m_moveAnimation;

	//m_type->m_moveSFX->play(-1, -1);

	m_weapon->init(this);
	m_weapon->m_weaponSelected = true;

	Pawn::init();

	m_colliderBox->SetSize(m_posX, m_posY, m_sizeW - resizeW, m_sizeH - resizeH);
	m_colliderBox->SetOffset(resizeW / 2, resizeH / 2);
}

void SkyEnemy::update(float _deltaTime)
{
	if (m_posY > SCREEN_HEIGHT)
	{
		if (!m_dead)
		{
			LCF::World::GetInstance().deleteActorByID(m_id);
		}
	}

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
		m_posY += (m_type->m_movementSpeed * _deltaTime);

		m_weapon->update(_deltaTime);
		
		m_shootTimer += _deltaTime;

		if (m_shootTimer >= m_shootTime)
		{
			m_weapon->shoot();
			m_shootTimer = 0;
		}
	}

	m_currentAnimation->update(_deltaTime);
}

void SkyEnemy::render(SDL_Renderer * _renderer, bool _flip)
{
	Enemy::render(_renderer);

	if (!m_dead)
	{
		m_weapon->render(_renderer);
	}
}

void SkyEnemy::collision(const Actor * _actor)
{
	if (const MainBullet* temp = dynamic_cast<const MainBullet*>(_actor))
	{
		if (!temp->m_type->m_enemy)
		{
			recieveDamage(temp->m_type->m_damage);
			LCF::World::GetInstance().deleteActorByID(temp->m_id);
		}
	}

	if (const SubBullet* temp = dynamic_cast<const SubBullet*>(_actor))
	{
		if (!temp->m_type->m_enemy)
		{
			recieveDamage(temp->m_type->m_damage);
			LCF::World::GetInstance().deleteActorByID(temp->m_id);
		}
	}
}

void SkyEnemy::setType(EnemyType * _type)
{
	m_type = _type;
	m_life = _type->m_life;
}

void SkyEnemy::recieveDamage(int _damage)
{
	Enemy::recieveDamage(_damage);

	m_type->m_damageSFX->play(-1);
}