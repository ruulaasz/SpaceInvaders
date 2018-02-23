#include "stdafx.h"

Wall::Wall()
{

}

Wall::~Wall()
{

}

void Wall::render(SDL_Renderer * _renderer)
{

}

void Wall::init()
{
	m_sizeW = 20;
	m_sizeH = 50;
	m_posY = LCF::SDL_Manager::GetInstance().m_windowHeight - m_sizeH;
	Pawn::init();
}