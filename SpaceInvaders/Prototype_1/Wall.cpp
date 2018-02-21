#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
{

}

Wall::~Wall()
{


}

void Wall::render(SDL_Renderer * _renderer)
{
	m_texture->render(m_posX, m_posY, _renderer);
}

void Wall::update(float _deltaTime)
{

}

void Wall::init()
{
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("wall"));

	Actor::init();
	m_posX = 0;
}

void Wall::collision(const Actor * _actor)
{

}