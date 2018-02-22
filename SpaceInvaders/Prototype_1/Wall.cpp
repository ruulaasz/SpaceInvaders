#include "stdafx.h"

Wall::Wall()
{

}

Wall::~Wall()
{

}

void Wall::render(SDL_Renderer * _renderer)
{
	//m_texture->render(m_posX, m_posY, _renderer);
}

void Wall::init()
{
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("wall"));
	Pawn::init();
	m_colliderBox->w += WALL_THICC;
}