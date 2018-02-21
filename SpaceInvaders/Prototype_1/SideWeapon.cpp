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

	m_shootSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("shoot_subweapon"));
	m_changeWeaponSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("change_weapon"));

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
		SubBullet* b = new SubBullet(_posX, _posY, _direction);
		b->init();
		//hardcode incluir funcion en el mundo para eliminar la bala
		LCF::World::GetInstance().registerActor(b);

		m_shootSFX->play(SUBWEAPON_SHOOT_SFXCHANNEL);
	}
	else
	{
		m_weaponSelected = true;
		m_changeWeaponSFX->play(CHANGEWEAPON_SFXCHANNEL);
	}
}

void SideWeapon::collision(const Actor * _actor)
{
	
}