#include "stdafx.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::render(SDL_Renderer * _renderer, bool _flip)
{
	m_currentAnimation->render((int)m_transform.m_posX, (int)m_transform.m_posY, _renderer, _flip);
}