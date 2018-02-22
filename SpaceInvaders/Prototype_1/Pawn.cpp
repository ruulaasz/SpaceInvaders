#include "stdafx.h"

Pawn::Pawn()
{

}

Pawn::~Pawn()
{

}

void Pawn::init()
{
	m_colliderBox = new LCF::ColliderBox<Actor>();

	m_colliderBox->SetFunction(&Actor::collision);
	m_colliderBox->SetActor(this, false);
	
	m_colliderBox->SetSize(m_posX, m_posY, m_texture->getWidth(), m_texture->getHeight());

	LCF::ColliderManager::GetInstance().RegistrerCollider(m_colliderBox);
}