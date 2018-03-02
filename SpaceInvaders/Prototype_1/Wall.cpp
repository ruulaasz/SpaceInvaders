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
	m_posY = 700;
	Pawn::init();
}