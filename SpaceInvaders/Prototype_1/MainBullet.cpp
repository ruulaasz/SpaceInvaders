#include "stdafx.h"

MainBullet::MainBullet()
{
	
}

MainBullet::MainBullet(float _posX, float _posY)
{
	m_posX = _posX;
	m_posY = _posY;
	
	m_movementSpeed = 150.f;
	m_damage = 25;
}

MainBullet::~MainBullet()
{

}

void MainBullet::init()
{
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("main_bullet_base"));

	m_travelAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("main_bullet"));
	m_travelAnimation->m_frameHeight = 30;
	m_travelAnimation->m_frameWidth = 28;
	m_travelAnimation->m_animSpeed = 0.2f;
	m_travelAnimation->m_numOfFrames = 5;

	m_deadAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("main_bullet_dead"));
	m_deadAnimation->m_frameHeight = 40;
	m_deadAnimation->m_frameWidth = 51;
	m_deadAnimation->m_animSpeed = 0.0175f;
	m_deadAnimation->m_numOfFrames = 7;
	m_deadAnimation->m_maxRepetitions = 1;

	m_impactSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("mainbullet_impact"));

	m_sizeW = (float)m_travelAnimation->m_frameWidth - 10;
	m_sizeH = (float)m_travelAnimation->m_frameHeight - 10;

	m_currentAnimation = m_travelAnimation;

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
		if (!m_enemy)
		{
			m_posY -= m_movementSpeed * _deltaTime;
		}
		else
		{
			m_posY += m_movementSpeed * _deltaTime;
		}

		if (m_posY < -m_texture->getWidth())
		{
			LCF::World::GetInstance().deleteActorByID(m_id);
			m_outOfLimits = true;
		}
	}

	m_currentAnimation->update(_deltaTime);
	
}

void MainBullet::collision(const Actor * _actor)
{
	if (const SkyEnemy* temp = dynamic_cast<const SkyEnemy*>(_actor))
	{

	}
}