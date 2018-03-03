#include "stdafx.h"

Pawn::Pawn()
{
	m_enabled = true;
}

Pawn::~Pawn()
{

}

void Pawn::init()
{
	m_colliderBox = new LCF::ColliderBox<Actor>();

	m_colliderBox->SetFunction(&Actor::collision);
	m_colliderBox->SetActor(this, false);
	
	m_colliderBox->SetSize(m_transform.m_posX, m_transform.m_posY, m_transform.m_sizeW, m_transform.m_sizeH);

	m_colliderBox->SetAutomaticOffset();

	LCF::ColliderManager::GetInstance().RegistrerCollider(m_colliderBox);

	//Asignacion de id
	m_id = autoID;
	autoID++;
}

void Pawn::destroy()
{
	LCF::ColliderManager::GetInstance().DestroyColliderbyID(m_colliderBox->GetID());
}