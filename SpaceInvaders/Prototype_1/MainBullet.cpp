#include "stdafx.h"
#include "MainBullet.h"

MainBullet::MainBullet(int _posX, int _posY, int _direction)
{
	m_movementSpeed = 800.f;
	m_posX = _posX;
	m_posY = _posY;
	m_direction = _direction;
}

MainBullet::~MainBullet()
{

}

void MainBullet::init()
{
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("main_bullet_base"));
	Actor::init();
}

void MainBullet::render(SDL_Renderer * _renderer)
{
	m_texture->render(m_posX, m_posY, _renderer);
}

void MainBullet::update(float _deltaTime)
{
	if (m_direction == 0)
	{
		m_posY -= m_movementSpeed * _deltaTime;
	}
	else
	{
		m_posX += m_movementSpeed * _deltaTime * m_direction;
	}
}

void MainBullet::collision(const Actor * _actor)
{

}