#include "stdafx.h"

Wall::Wall()
{

}

Wall::~Wall()
{

}

void Wall::init()
{
	m_sizeW = 20.f;
	m_sizeH = 50.f;
	m_posY = LCF::SDL_Manager::GetInstance().m_windowHeight - m_sizeH;
	Pawn::init();
}