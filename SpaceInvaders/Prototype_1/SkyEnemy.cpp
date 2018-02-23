#include "stdafx.h"

SkyEnemy::SkyEnemy()
{
	m_movementSpeed = 100.f;
	m_animator = new LCF::Animator();
	m_life = 1000;
	m_damage = 10;
}

SkyEnemy::~SkyEnemy()
{
	
}

void SkyEnemy::init()
{
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("MainWeapon"));

	m_animator->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("meteor"));
	m_animator->m_frameHeight = m_animator->m_sprite->getHeight();
	m_animator->m_numOfFrames = 5;
	m_animator->m_frameWidth = m_animator->m_sprite->getWidth() / m_animator->m_numOfFrames;
	m_animator->m_animSpeed = 0.1f;
	m_animator->m_maxRepetitions = 0;

	m_moveSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("skyenemy"));

	m_posX = 500;
	m_posY = m_texture->getHeight();
	m_sizeW = m_animator->m_frameWidth;
	m_sizeH = m_animator->m_frameHeight;

	m_currentAnimation = m_animator;

	m_moveSFX->play(-1, -1);

	Pawn::init();
}

void SkyEnemy::render(SDL_Renderer * _renderer)
{
	m_currentAnimation->render(m_posX, m_posY, _renderer);

	renderDamage(_renderer);
}

void SkyEnemy::renderDamage(SDL_Renderer * _renderer)
{
	for (size_t i = 0; i < m_damageText.size(); i++)
	{
		m_damageText.at(i)->render(_renderer);
	}
}

void SkyEnemy::update(float _deltaTime)
{
	if (m_life <= 0)
	{
		LCF::AudioManager::GetInstance().StopChannel(m_moveSFX->m_currentChannel);
		LCF::World::GetInstance().deleteActorByID(m_id);
		return;
	}

	m_posY += (m_movementSpeed * _deltaTime);
	m_currentAnimation->update(_deltaTime);

	for (size_t i = 0; i < m_damageText.size(); i++)
	{
		if (m_damageText.at(i)->m_enable)
		{
			m_damageText.at(i)->update(_deltaTime);
		}
		else
		{
			m_damageText.erase(m_damageText.begin() + i);
		}
	}
}

void SkyEnemy::recieveDamage(int _damage)
{
	m_life -= _damage;
	m_damageRecieved = _damage;

	FallingText* fall = new FallingText();

	fall->m_String = std::to_string(m_damageRecieved);
	fall->m_posX = m_posX + m_sizeW;
	fall->m_posY = m_posY + (m_sizeH / 2);
	fall->m_originPosX = fall->m_posX;
	fall->m_originPosY = fall->m_posY;

	m_damageText.push_back(fall);
}

void SkyEnemy::collision(const Actor * _actor)
{
	if (const MainBullet* temp = dynamic_cast<const MainBullet*>(_actor))
	{
		recieveDamage(temp->m_damage);
		LCF::World::GetInstance().deleteActorByID(temp->m_id);
	}
}