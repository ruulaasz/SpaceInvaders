#include "stdafx.h"

Wall::Wall()
{

}

Wall::~Wall()
{

}

void Wall::init()
{
	m_transform.m_sizeW = 20.f;
	m_transform.m_sizeH = 50.f;
	m_transform.m_posY = 700;
	Pawn::init();
}