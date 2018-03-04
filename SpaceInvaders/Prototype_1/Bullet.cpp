#include "stdafx.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::render(bool _flip)
{
	m_currentAnimation->render((int)m_transform.m_posX, (int)m_transform.m_posY, _flip);
}