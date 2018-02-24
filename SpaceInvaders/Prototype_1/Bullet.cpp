#include "stdafx.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::render(SDL_Renderer * _renderer)
{
	m_texture->render((int)m_posX, (int)m_posY, _renderer);
}