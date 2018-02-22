#include "stdafx.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::render(SDL_Renderer * _renderer)
{
	m_texture->render(m_posX, m_posY, _renderer);
}