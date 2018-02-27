#include "stdafx.h"

Bullet::Bullet()
{
	m_travelAnimation = new LCF::Animator();
	m_deadAnimation = new LCF::Animator();
}

Bullet::~Bullet()
{

}

void Bullet::render(SDL_Renderer * _renderer)
{
	m_texture->render((int)m_posX, (int)m_posY, _renderer);
}