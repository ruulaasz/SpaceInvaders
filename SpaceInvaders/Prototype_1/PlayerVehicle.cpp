#include "stdafx.h"


PlayerVehicle::PlayerVehicle()
{
	m_movementSpeed = 800.f;
	m_life = 100;
}

PlayerVehicle::~PlayerVehicle()
{
	
}

void PlayerVehicle::init(int _screenW, int _screenH)
{
	m_collisionDectected = false;

	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("MainWeapon"));
	m_moveSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("moving"));

	m_posX = (_screenW / 2) - (m_texture->getWidth() / 2);
	m_posY = _screenH - m_texture->getHeight();

	m_weapons[MAIN_WEAPON] = new MainWeapon();
	m_weapons[MAIN_WEAPON]->init(this);
	m_weapons[MAIN_WEAPON]->m_direction = DIRECTION_STOP;
	m_weapons[MAIN_WEAPON]->m_weaponSelected = true;

	m_weapons[RIGHT_WEAPON] = new SideWeapon();
	m_weapons[RIGHT_WEAPON]->init(this);
	m_weapons[RIGHT_WEAPON]->m_direction = DIRECTION_RIGHT;

	m_weapons[LEFT_WEAPON] = new SideWeaponB();
	m_weapons[LEFT_WEAPON]->init(this);
	m_weapons[LEFT_WEAPON]->m_direction = DIRECTION_LEFT;

	m_moveSFX->play(-1);
	LCF::AudioManager::GetInstance().PauseChannel(m_moveSFX->m_currentChannel);

	m_sizeW = m_texture->getWidth() + m_weapons[LEFT_WEAPON]->m_texture->getWidth() + m_weapons[RIGHT_WEAPON]->m_texture->getWidth();
	m_sizeH = m_texture->getHeight();
	Pawn::init();
	m_colliderBox->SetOffset(-m_weapons[LEFT_WEAPON]->m_texture->getWidth(), 0);

	m_coreCollider = new PlayerVehicleBox();
	m_coreCollider->SetActor(this);
	m_coreCollider->SetFunction(&PlayerVehicle::coreColision);
	m_coreCollider->SetSize(m_posX, m_posY, m_texture->getWidth() -10, m_texture->getHeight() - 10);
	LCF::ColliderManager::GetInstance().RegistrerCollider(m_coreCollider);
	m_coreCollider->SetOffset(5, 5);
}

void PlayerVehicle::render(SDL_Renderer * _renderer)
{
	//m_texture->render(m_posX, m_posY, _renderer);
	
	for (size_t i = 0; i < NUMBEROF_PLAYERWEAPONS; i++)
	{
		m_weapons[i]->render(_renderer);
	}
}

void PlayerVehicle::update(float _deltaTime)
{
	if (m_beDestroyed)
	{
		//animacion o cualquier cosa que se requiera
		//Usar esta bandera para que el manager lo elimine
		m_DestroyMe = true;
	}

	for (size_t i = 0; i < NUMBEROF_PLAYERWEAPONS; i++)
	{
		m_weapons[i]->update(_deltaTime);
	}

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
		if (m_currentDirection == MAX_NUMBER_TO_THE_LEFT && _info.direction == DIRECTION_RIGHT)
		{
			m_currentDirection = _info.direction;
			m_collisionDectected = false;
			return;
		}
		else if (m_currentDirection == MAX_NUMBER_TO_THE_RIGHT && _info.direction == DIRECTION_LEFT)
		{
			m_currentDirection = _info.direction;
			m_collisionDectected = false;
			return;
		}

		LCF::AudioManager::GetInstance().PauseChannel(m_moveSFX->m_currentChannel);
		return;
	}

	m_currentDirection = _info.direction;

	if (m_currentDirection != DIRECTION_STOP)
	{
		if (!LCF::AudioManager::GetInstance().PlayingChannel(m_moveSFX->m_currentChannel))
		{
			m_moveSFX->play(-1);
			LCF::AudioManager::GetInstance().PauseChannel(m_moveSFX->m_currentChannel);
		}

		if (LCF::AudioManager::GetInstance().PausedChannel(m_moveSFX->m_currentChannel))
		{
			LCF::AudioManager::GetInstance().ResumeChannel(m_moveSFX->m_currentChannel);
		}
	}
	else
	{
		LCF::AudioManager::GetInstance().PauseChannel(m_moveSFX->m_currentChannel);
	}
}

void PlayerVehicle::shootMainWeapon(MovementInfo _info)
{
	m_weapons[LEFT_WEAPON]->m_weaponSelected = false;
	m_weapons[RIGHT_WEAPON]->m_weaponSelected = false;
	m_weapons[MAIN_WEAPON]->shoot();
}

void PlayerVehicle::shootRightWeapon(MovementInfo _info)
{
	m_weapons[MAIN_WEAPON]->m_weaponSelected = false;
	m_weapons[LEFT_WEAPON]->m_weaponSelected = false;
	m_weapons[RIGHT_WEAPON]->shoot();
}

void PlayerVehicle::shootLeftWeapon(MovementInfo _info)
{
	m_weapons[MAIN_WEAPON]->m_weaponSelected = false;
	m_weapons[RIGHT_WEAPON]->m_weaponSelected = false;
	m_weapons[LEFT_WEAPON]->shoot();
}

void PlayerVehicle::recieveDamage(int _damage)
{
	m_life -= _damage;
}

void PlayerVehicle::collision(const Actor * _actor)
{
	if (const SkyEnemy* temp = dynamic_cast<const SkyEnemy*>(_actor))
	{
		recieveDamage(temp->m_damage);
		m_weapons[RIGHT_WEAPON]->recieveDamage(temp->m_damage);
		m_weapons[LEFT_WEAPON]->recieveDamage(temp->m_damage);
		LCF::AudioManager::GetInstance().StopChannel(temp->m_moveSFX->m_currentChannel);
		LCF::World::GetInstance().deleteActorByID(temp->m_id);
	}

	if (const Wall* temp = dynamic_cast<const Wall*>(_actor))
	{
		if (m_currentDirection < DIRECTION_STOP)
		{
			m_posX = temp->m_posX + temp->m_colliderBox->GetW() + m_weapons[LEFT_WEAPON]->m_texture->getWidth();
			m_currentDirection = MAX_NUMBER_TO_THE_LEFT;
		}
		else
		{
			m_posX = temp->m_posX - m_colliderBox->GetW() + m_weapons[RIGHT_WEAPON]->m_texture->getWidth();
			m_currentDirection = MAX_NUMBER_TO_THE_RIGHT;
		}

		m_collisionDectected = true;
	}
}

void PlayerVehicle::coreColision(const Actor * _actor)
{

}