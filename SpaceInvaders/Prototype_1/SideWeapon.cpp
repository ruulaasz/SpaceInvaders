#include "stdafx.h"
#include "SideWeapon.h"

SideWeapon::SideWeapon()
{
	
}

SideWeapon::~SideWeapon()
{

}

void SideWeapon::init()
{
	m_weaponReadyTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("player_sidevehicle_selected"));
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("player_sidevehicle"));

	Actor::init();
}

void SideWeapon::render(SDL_Renderer * _renderer)
{
	if (m_weaponSelected)
	{
		m_weaponReadyTexture->render(m_posX, m_posY, _renderer);
	}
	else
	{
		m_texture->render(m_posX, m_posY, _renderer);
	}
}

void SideWeapon::update(float _deltaTime)
{
	
}

void SideWeapon::shootMainWeapon(int _posX, int _posY, int _direction)
{
	if (m_weaponSelected)
	{
		MainBullet* b = new MainBullet(_posX, _posY, _direction);
		b->init();
		//hardcode incluir funcion en el mundo para eliminar la bala
		LCF::World::GetInstance().registerActor(b);
	}
	else
	{
		m_weaponSelected = true;
	}
}