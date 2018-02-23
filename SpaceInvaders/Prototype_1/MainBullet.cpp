#include "stdafx.h"

MainBullet::MainBullet()
{
	
}

MainBullet::MainBullet(int _posX, int _posY)
{
	m_posX = _posX;
	m_posY = _posY;
	m_travelAnimation = new LCF::Animator();
	m_movementSpeed = 1800.f;
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

	m_sizeW = m_travelAnimation->m_frameWidth;
	m_sizeH = m_travelAnimation->m_frameHeight;

	m_currentAnimation = m_travelAnimation;

	Pawn::init();
}

void MainBullet::render(SDL_Renderer * _renderer)
{
	m_currentAnimation->render(m_posX, m_posY, _renderer);
}

void MainBullet::update(float _deltaTime)
{
	if (m_beDestroyed)
	{
		//animacion o cualquier cosa que se requiera
		//Usar esta bandera para que el manager lo elimine
		m_DestroyMe = true;
	}
	m_posY -= m_movementSpeed * _deltaTime;
	
	m_currentAnimation->update(_deltaTime);

	if (m_posY < -m_texture->getWidth())
	{
		LCF::World::GetInstance().deleteActorByID(m_id);
	}
}

void MainBullet::collision(const Actor * _actor)
{
	if (const SkyEnemy* temp = dynamic_cast<const SkyEnemy*>(_actor))
	{
		
	}
}