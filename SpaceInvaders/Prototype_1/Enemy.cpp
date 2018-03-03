#include "stdafx.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::render(SDL_Renderer * _renderer, bool _flip)
{
	m_currentAnimation->render((int)m_transform.m_posX, (int)m_transform.m_posY, _renderer, _flip);
}

void Enemy::recieveDamage(int _damage)
{
	m_life -= _damage;

	if (m_life <= 0)
	{
		LCF::World::GetInstance().deleteActorByID(m_id);
		m_life = 0;
	}
	
	FallingText* fall = new FallingText();

	fall->m_String = std::to_string(_damage);
	fall->m_posX = m_transform.m_posX + m_transform.m_sizeW;
	fall->m_posY = m_transform.m_posY - (m_transform.m_sizeH / 2);
	fall->m_originPosX = fall->m_posX;
	fall->m_originPosY = fall->m_posY;

	SDL_Color c;
	c.r = 255;
	c.g = 0;
	c.b = 0;

	fall->m_color = c;

	TextManager::GetInstance().m_fallingText.push_back(fall);
}