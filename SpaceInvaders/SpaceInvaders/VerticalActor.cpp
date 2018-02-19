#include "stdafx.h"

VerticalActor::VerticalActor()
{

}

VerticalActor::~VerticalActor()
{

}

void VerticalActor::render(SDL_Renderer * _renderer)
{
	m_texture->render(m_posX, m_posY, _renderer);
}

void VerticalActor::move(VerticalStruct _info)
{
	m_posY += _info.value;
}

void VerticalActor::update(float _deltaTime)
{

}

void VerticalActor::Init()
{
	LCF::ColliderBox<VerticalActor>* newBox = new LCF::ColliderBox<VerticalActor>();

	newBox->SetFunction(&VerticalActor::Collision);
	newBox->SetActor(this, false);
	newBox->SetSize(m_posX, m_posY, 50, 50);
	LCF::ColliderManager::GetInstance().RegistrerCollider(newBox);
}

void VerticalActor::Collision(const Actor * _actor)
{
	std::cout << "Collision.\n";
}
