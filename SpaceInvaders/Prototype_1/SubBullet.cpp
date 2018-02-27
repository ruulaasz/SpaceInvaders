#include "stdafx.h"

SubBullet::SubBullet()
{

}

SubBullet::SubBullet(float _posX, float _posY, int _direction)
{
	m_movementSpeed = 1800.f;
	m_posX = _posX;
	m_posY = _posY;
	m_direction = _direction;
	m_damage = 5;
}

SubBullet::~SubBullet()
{

}

void SubBullet::init()
{
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("sub_bullet_base"));

	m_travelAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("main_bullet"));
	m_travelAnimation->m_frameHeight = 10;
	m_travelAnimation->m_frameWidth = 10;
	m_travelAnimation->m_animSpeed = 0.2f;
	m_travelAnimation->m_numOfFrames = 1;

	m_deadAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("main_bullet_dead"));
	m_deadAnimation->m_frameHeight = 40;
	m_deadAnimation->m_frameWidth = 51;
	m_deadAnimation->m_animSpeed = 0.0175f;
	m_deadAnimation->m_numOfFrames = 7;
	m_deadAnimation->m_maxRepetitions = 1;

	m_impactSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("mainbullet_impact"));

	m_sizeW = (float)m_texture->getWidth();
	m_sizeH = (float)m_texture->getHeight();

	m_currentAnimation = m_travelAnimation;

	Pawn::init();
}

void SubBullet::update(float _deltaTime)
{
	if (m_beDestroyed)
	{
		if (!m_dead)
		{
			m_colliderBox->SetEnabled(false);
			m_currentAnimation = m_deadAnimation;

			if (!m_outOfLimits)
			{
				m_impactSFX->play(-1);
			}

			m_dead = true;
		}

		if (m_deadAnimation->m_finished)
		{
			m_DestroyMe = true;
		}
	}

	if (!m_dead)
	{
		m_posX += m_movementSpeed * _deltaTime * m_direction;

		if (m_posX < -100)
		{
			m_beDestroyed = true;
			m_outOfLimits = true;
		}

		if (m_posX > SCREEN_WIDTH)
		{
			m_beDestroyed = true;
			m_outOfLimits = true;
		}
	}

	m_currentAnimation->update(_deltaTime);
}

void SubBullet::render(SDL_Renderer * _renderer)
{
	m_currentAnimation->render((int)m_posX, (int)m_posY, _renderer);
}
