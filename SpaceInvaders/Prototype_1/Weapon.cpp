#include "stdafx.h"

Weapon::Weapon()
{
	
}

Weapon::~Weapon()
{

}

void Weapon::render(SDL_Renderer * _renderer)
{
	if (m_weaponSelected)
	{
		m_weaponReadyTexture->render(m_posX, m_posY, _renderer);
	}
	else
	{
		m_texture->render(m_posX, m_posY, _renderer);
	}
}

void Weapon::update(float _deltaTime)
{
	if (m_direction > DIRECTION_STOP)
	{
		m_posX = m_Parent->m_posX + m_Parent->m_texture->getWidth();
	}
	
	if (m_direction < DIRECTION_STOP)
	{
		m_posX = m_Parent->m_posX - m_texture->getWidth();
	}
	
	if (m_direction == DIRECTION_STOP)
	{
		m_posX = m_Parent->m_posX;
	}
}

void Weapon::collision(const Actor * _actor)
{
	if (const Wall* temp = dynamic_cast<const Wall*>(_actor))
	{
		if (m_direction < DIRECTION_STOP)
		{
			m_Parent->m_posX = temp->m_posX + temp->m_colliderBox->w + m_colliderBox->w;
			reinterpret_cast<PlayerVehicle*>(m_Parent)->m_currentDirection = MAX_NUMBER_TO_THE_LEFT;
		}
		else
		{
			m_Parent->m_posX = temp->m_posX - m_Parent->m_colliderBox->w - m_colliderBox->w;
			reinterpret_cast<PlayerVehicle*>(m_Parent)->m_currentDirection = MAX_NUMBER_TO_THE_RIGHT;
		}

		reinterpret_cast<PlayerVehicle*>(m_Parent)->m_collisionDectected = true;
	}
}
