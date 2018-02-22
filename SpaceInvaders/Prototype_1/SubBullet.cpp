#include "stdafx.h"

SubBullet::SubBullet()
{

}

SubBullet::SubBullet(int _posX, int _posY, int _direction)
{
	m_movementSpeed = 1800.f;
	m_posX = _posX;
	m_posY = _posY;
	m_direction = _direction;
}

SubBullet::~SubBullet()
{

}

void SubBullet::init()
{
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("sub_bullet_base"));
	Pawn::init();
}

void SubBullet::update(float _deltaTime)
{
	m_posX += m_movementSpeed * _deltaTime * m_direction;
}