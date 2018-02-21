#include "stdafx.h"

PlayerVehicle::PlayerVehicle()
{
	m_movementSpeed = 400.f;
}

PlayerVehicle::~PlayerVehicle()
{

}

void PlayerVehicle::init(int _screenW, int _screenH)
{
	m_weaponReadyTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("player_vehicle_selected"));
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("player_vehicle"));

	Actor::init();
	m_posX = (_screenW / 2) - (m_texture->getWidth() / 2);
	m_posY = _screenH - m_texture->getHeight();

	m_subWeaponA.init();

	m_subWeaponA.m_posY = m_posY;

	m_subWeaponB.init();

	m_subWeaponB.m_posY = m_posY;
}

void PlayerVehicle::render(SDL_Renderer * _renderer)
{
	if (m_weaponSelected)
	{
		m_weaponReadyTexture->render(m_posX, m_posY, _renderer);
	}
	else
	{
		m_texture->render(m_posX, m_posY, _renderer);
	}

	m_subWeaponA.render(_renderer);

	m_subWeaponB.render(_renderer);
}

void PlayerVehicle::update(float _deltaTime)
{
	m_posX += (m_currentDirection * m_movementSpeed * _deltaTime);

	m_subWeaponA.m_posX = m_posX + m_texture->getWidth();
	m_subWeaponB.m_posX = m_posX - m_texture->getWidth()/2;
}


void PlayerVehicle::move(MovementInfo _info)
{
	m_currentDirection = _info.direction;
}

void PlayerVehicle::shootMainWeapon(MovementInfo _info)
{
	if (m_weaponSelected)
	{
		MainBullet* b = new MainBullet(m_posX + m_texture->getWidth() / 2, m_posY - 20, 0);
		b->init();
		//hardcode incluir funcion en el mundo para eliminar la bala
		LCF::World::GetInstance().registerActor(b);
	}
	else
	{
		m_weaponSelected = true;
		m_subWeaponA.m_weaponSelected = false;
		m_subWeaponB.m_weaponSelected = false;
	}
}

void PlayerVehicle::shootSubWeaponA(MovementInfo _info)
{
	m_weaponSelected = false;
	m_subWeaponB.m_weaponSelected = false;
	m_subWeaponA.shootMainWeapon(m_posX + (m_texture->getWidth() + m_subWeaponA.m_texture->getWidth()), m_posY + m_subWeaponA.m_texture->getHeight()/2, 1);
}

void PlayerVehicle::shootSubWeaponB(MovementInfo _info)
{
	m_weaponSelected = false;
	m_subWeaponA.m_weaponSelected = false;
	m_subWeaponB.shootMainWeapon(m_posX - m_subWeaponB.m_texture->getWidth(), m_posY + m_subWeaponB.m_texture->getHeight() / 2, -1);
}

void PlayerVehicle::collision(const Actor * _actor)
{
	//if (Wall* temp = dynamic_cast<Wall*>(_actor))
	//hardcode necesito la info del collider contra el que choque y ver como evitar que vibre al chocar
	//m_posX = _actor->m_posX + (-100 * m_currentDirection); 

	//m_currentDirection = 0;
}