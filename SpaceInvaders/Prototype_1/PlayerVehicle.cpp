#include "stdafx.h"


PlayerVehicle::PlayerVehicle()
{
	m_movementSpeed = 400.f;
	m_collisionDectected = false;
}

PlayerVehicle::~PlayerVehicle()
{
	
}

void PlayerVehicle::init(int _screenW, int _screenH)
{
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("MainWeapon"));

	m_moveSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("moving"));
	
	
	m_posX = (_screenW / 2) - (m_texture->getWidth() / 2);
	m_posY = _screenH - m_texture->getHeight();
	m_sizeW = m_texture->getWidth();
	m_sizeH = m_texture->getHeight();

	m_mainWeapon.init(this);
	m_mainWeapon.m_direction = DIRECTION_STOP;
	m_mainWeapon.m_weaponSelected = true;

	m_subWeaponA.init(this);
	m_subWeaponA.m_direction = DIRECTION_RIGHT;

	m_subWeaponB.init(this);
	m_subWeaponB.m_direction = DIRECTION_LEFT;

	m_moveSFX->play(PLAYERMOVEMENT_SFXCHANNEL);
	LCF::AudioManager::GetInstance().PauseChannel(PLAYERMOVEMENT_SFXCHANNEL);
	Pawn::init();
}

void PlayerVehicle::render(SDL_Renderer * _renderer)
{
	//m_texture->render(m_posX, m_posY, _renderer);
	
	m_mainWeapon.render(_renderer);

	m_subWeaponA.render(_renderer);

	m_subWeaponB.render(_renderer);
}

void PlayerVehicle::update(float _deltaTime)
{
	m_mainWeapon.update(_deltaTime);
	m_subWeaponA.update(_deltaTime);
	m_subWeaponB.update(_deltaTime);

	if (m_currentDirection == MAX_NUMBER_TO_THE_LEFT)
	{
		return;
	}
	else if (m_currentDirection == MAX_NUMBER_TO_THE_RIGHT)
	{
		return;
	}

	m_posX += (m_currentDirection * m_movementSpeed * _deltaTime);
}

void PlayerVehicle::move(MovementInfo _info)
{
	if (m_collisionDectected)
	{
		if (_info.direction == DIRECTION_RIGHT)
		{
			m_currentDirection = _info.direction;
			m_collisionDectected = false;
		}
		else if ( _info.direction == DIRECTION_LEFT)
		{
			m_currentDirection = _info.direction;
			m_collisionDectected = false;
		}

		LCF::AudioManager::GetInstance().PauseChannel(PLAYERMOVEMENT_SFXCHANNEL);
	}

	m_currentDirection = _info.direction;

	if (m_currentDirection != DIRECTION_STOP)
	{
		if (!LCF::AudioManager::GetInstance().PlayingChannel(PLAYERMOVEMENT_SFXCHANNEL))
		{
			m_moveSFX->play(PLAYERMOVEMENT_SFXCHANNEL);
			LCF::AudioManager::GetInstance().PauseChannel(PLAYERMOVEMENT_SFXCHANNEL);
		}

		if (LCF::AudioManager::GetInstance().PausedChannel(PLAYERMOVEMENT_SFXCHANNEL))
		{
			LCF::AudioManager::GetInstance().ResumeChannel(PLAYERMOVEMENT_SFXCHANNEL);
		}
	}
	else
	{
		LCF::AudioManager::GetInstance().PauseChannel(PLAYERMOVEMENT_SFXCHANNEL);
	}
}

void PlayerVehicle::shootMainWeapon(MovementInfo _info)
{
	m_subWeaponA.m_weaponSelected = false;
	m_subWeaponB.m_weaponSelected = false;
	m_mainWeapon.shoot();
}

void PlayerVehicle::shootSubWeaponA(MovementInfo _info)
{
	m_mainWeapon.m_weaponSelected = false;
	m_subWeaponB.m_weaponSelected = false;
	m_subWeaponA.shoot();
}

void PlayerVehicle::shootSubWeaponB(MovementInfo _info)
{
	m_mainWeapon.m_weaponSelected = false;
	m_subWeaponA.m_weaponSelected = false;
	m_subWeaponB.shoot();
}

void PlayerVehicle::collision(const Actor * _actor)
{
	
}