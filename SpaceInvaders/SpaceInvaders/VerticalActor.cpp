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