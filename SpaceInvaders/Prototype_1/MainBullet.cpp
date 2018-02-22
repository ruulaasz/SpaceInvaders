#include "stdafx.h"

MainBullet::MainBullet()
{
	
}

MainBullet::MainBullet(int _posX, int _posY)
{
	m_posX = _posX;
	m_posY = _posY;
	m_movementSpeed = 100.f;
	m_travelAnimation = new LCF::Animator();
}

MainBullet::~MainBullet()
{

}

void MainBullet::init()
{
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("main_bullet_base"));

	m_travelAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("main_bullet"));

	m_afterShootSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("after_shoot_subweapon"));


	m_sizeW = m_travelAnimation->m_sprite->getWidth() / m_travelAnimation->m_maxJumps;
	m_sizeH = m_travelAnimation->m_sprite->getHeight();

	Pawn::init();
}

void MainBullet::render(SDL_Renderer * _renderer)
{
	m_travelAnimation->render(m_posX, m_posY, _renderer);
}

void MainBullet::update(float _deltaTime)
{
	m_posY -= m_movementSpeed * _deltaTime;
	
	m_timer += _deltaTime;

	if (!m_casketDroped)
	{
		if (m_timer > 0.4f)
		{
			m_afterShootSFX->play(MAINWEAPON_CASKET_SFXCHANNEL);
			m_casketDroped = true;
		}
	}

	m_travelAnimation->update(_deltaTime);
}

void MainBullet::collision(const Actor * _actor)
{

}