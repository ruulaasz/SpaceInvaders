#include "stdafx.h"


PlayerVehicle::PlayerVehicle()
{
	m_movementSpeed = 800.f;

	m_lifeMax = 100;
	m_life = m_lifeMax;

	m_energyRegenerationRate = 10;
	m_energyMax = 100;
	m_energy = m_energyMax;

	m_collisionDectected = false;
}

PlayerVehicle::~PlayerVehicle()
{
	
}

void PlayerVehicle::init()
{
	m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("MainWeapon"));
	m_moveSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("moving"));

	m_weapons[MAIN_WEAPON]->init(this);
	m_weapons[MAIN_WEAPON]->m_weaponSelected = true;
	m_activeWeapon = MAIN_WEAPON;

	m_weapons[RIGHT_WEAPON]->init(this);
	m_weapons[RIGHT_WEAPON]->m_direction = DIRECTION_RIGHT;

	m_weapons[LEFT_WEAPON]->init(this);
	m_weapons[LEFT_WEAPON]->m_direction = DIRECTION_LEFT;

	//m_moveSFX->play(-1);
	//LCF::AudioManager::GetInstance().PauseChannel(m_moveSFX->m_currentChannel);

	m_sizeW = (float)m_texture->getWidth();
	m_sizeH = (float)m_texture->getHeight();

	Pawn::init();

	m_colliderBox->SetSize(m_posX, m_posY, (float)m_texture->getWidth() + (float)m_weapons[LEFT_WEAPON]->m_weaponType->m_weaponTexture->getWidth() + (float)m_weapons[RIGHT_WEAPON]->m_weaponType->m_weaponTexture->getWidth(), (float)m_texture->getHeight());
	m_colliderBox->SetOffset((float)-m_weapons[LEFT_WEAPON]->m_weaponType->m_weaponTexture->getWidth(), 0);

	m_coreCollider = new PlayerVehicleBox();
	m_coreCollider->SetActor(this);
	m_coreCollider->SetFunction(&PlayerVehicle::coreColision);
	m_coreCollider->SetSize(m_posX, m_posY, (float)m_texture->getWidth() -10, (float)m_texture->getHeight() - 10);
	LCF::ColliderManager::GetInstance().RegistrerCollider(m_coreCollider);
	m_coreCollider->SetOffset(5, 5);

	m_coreLifeText = new spiText();
	m_coreLifeText->m_posX = 0;
	m_coreLifeText->m_posY = 0;

	SDL_Color c;
	c.r = 0;
	c.g = 255;
	c.b = 0;

	m_coreLifeText->m_color = c;

	TextManager::GetInstance().m_fallingText.push_back(m_coreLifeText);

	m_leftShieldText = new spiText();

	m_leftShieldText->m_posX = 0;
	m_leftShieldText->m_posY = 25;

	c.r = 100;
	c.g = 100;
	c.b = 100;

	m_leftShieldText->m_color = c;

	TextManager::GetInstance().m_fallingText.push_back(m_leftShieldText);

	m_rightShieldText = new spiText();
	m_rightShieldText->m_posX = 0;
	m_rightShieldText->m_posY = 50;

	m_rightShieldText->m_color = c;

	TextManager::GetInstance().m_fallingText.push_back(m_rightShieldText);

	m_energyText = new spiText();
	m_energyText->m_posX = 0;
	m_energyText->m_posY = 100;

	c.r = 0;
	c.g = 0;
	c.b = 255;

	m_energyText->m_color = c;

	TextManager::GetInstance().m_fallingText.push_back(m_energyText);
}

void PlayerVehicle::render(SDL_Renderer * _renderer, bool _flip)
{
	m_texture->render((int)m_posX, (int)m_posY, _renderer);
	
	for (size_t i = 0; i < NUMBEROF_PLAYERWEAPONS; i++)
	{
		m_weapons[i]->render(_renderer, _flip);
	}
}

void PlayerVehicle::update(float _deltaTime)
{
	if (m_beDestroyed)
	{
		m_DestroyMe = true;
	}

	for (size_t i = 0; i < NUMBEROF_PLAYERWEAPONS; i++)
	{
		m_weapons[i]->update(_deltaTime);
	}

	if (m_energy < m_energyMax)
	{
		m_energy += m_energyRegenerationRate*_deltaTime;
	}
	else
	{
		m_energy = m_energyMax;
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

	m_energyText->m_String = "Energy: " + std::to_string(m_energy);
	m_leftShieldText->m_String = "Left Shield: " + std::to_string(m_weapons[LEFT_WEAPON]->m_life);
	m_rightShieldText->m_String = "Right Shield: " + std::to_string(m_weapons[RIGHT_WEAPON]->m_life);
	m_coreLifeText->m_String = "Core Life: " + std::to_string(m_life);
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

		//LCF::AudioManager::GetInstance().PauseChannel(m_moveSFX->m_currentChannel);
		return;
	}

	m_currentDirection = _info.direction;

	//if (m_currentDirection != DIRECTION_STOP)
	//{
	//	if (!LCF::AudioManager::GetInstance().PlayingChannel(m_moveSFX->m_currentChannel))
	//	{
	//		m_moveSFX->play(-1);
	//		LCF::AudioManager::GetInstance().PauseChannel(m_moveSFX->m_currentChannel);
	//	}

	//	if (LCF::AudioManager::GetInstance().PausedChannel(m_moveSFX->m_currentChannel))
	//	{
	//		LCF::AudioManager::GetInstance().ResumeChannel(m_moveSFX->m_currentChannel);
	//	}
	//}
	//else
	//{
	//	LCF::AudioManager::GetInstance().PauseChannel(m_moveSFX->m_currentChannel);
	//}
}

void PlayerVehicle::shootMainWeapon(MovementInfo /*_info*/)
{
	m_weapons[LEFT_WEAPON]->m_weaponSelected = false;
	m_weapons[RIGHT_WEAPON]->m_weaponSelected = false;
	m_activeWeapon = MAIN_WEAPON;
	m_weapons[MAIN_WEAPON]->shoot();
}

void PlayerVehicle::shootRightWeapon(MovementInfo /*_info*/)
{
	m_weapons[MAIN_WEAPON]->m_weaponSelected = false;
	m_weapons[LEFT_WEAPON]->m_weaponSelected = false;
	m_activeWeapon = RIGHT_WEAPON;
	m_weapons[RIGHT_WEAPON]->shoot();
}

void PlayerVehicle::shootLeftWeapon(MovementInfo /*_info*/)
{
	m_weapons[MAIN_WEAPON]->m_weaponSelected = false;
	m_weapons[RIGHT_WEAPON]->m_weaponSelected = false;
	m_activeWeapon = LEFT_WEAPON;
	m_weapons[LEFT_WEAPON]->shoot();
}

void PlayerVehicle::recieveDamage(int _damage)
{
	m_life -= _damage;

	FallingText* fall = new FallingText();

	fall->m_String = std::to_string(_damage);
	fall->m_posX = m_posX;
	fall->m_posY = m_posY - (m_sizeH / 2);
	fall->m_originPosX = fall->m_posX;
	fall->m_originPosY = fall->m_posY;

	SDL_Color c;
	c.r = 0;
	c.g = 0;
	c.b = 0;

	fall->m_color = c;

	TextManager::GetInstance().m_fallingText.push_back(fall);
}

void PlayerVehicle::superShot(MovementInfo /*_info*/)
{
	switch (m_activeWeapon)
	{
	default:
		break;

	case MAIN_WEAPON:
		m_energy -= 100;
		break;

	case RIGHT_WEAPON:
		m_energy -= 10;
		break;

	case LEFT_WEAPON:
		m_energy -= 10;
		break;
	}
}

void PlayerVehicle::collision(const Actor * _actor)
{
	if (const SkyEnemy* temp = dynamic_cast<const SkyEnemy*>(_actor))
	{
		recieveDamage(temp->m_type->m_damage);

		m_weapons[RIGHT_WEAPON]->recieveDamage((temp->m_type->m_damage)/4);
		m_weapons[LEFT_WEAPON]->recieveDamage((temp->m_type->m_damage)/4);

		LCF::AudioManager::GetInstance().StopChannel(temp->m_type->m_moveSFX->m_currentChannel);
		LCF::World::GetInstance().deleteActorByID(temp->m_id);
	}

	if (const GroundEnemy* temp = dynamic_cast<const GroundEnemy*>(_actor))
	{
		if (temp->m_direction < 0)
		{
			if (!m_weapons[RIGHT_WEAPON]->m_dead)
			{
				m_weapons[RIGHT_WEAPON]->recieveDamage(temp->m_type->m_damage);
			}
			else
			{
				recieveDamage(temp->m_type->m_damage);
			}
		}
		else
		{
			if (!m_weapons[LEFT_WEAPON]->m_dead)
			{
				m_weapons[LEFT_WEAPON]->recieveDamage(temp->m_type->m_damage);
			}
			else
			{
				recieveDamage(temp->m_type->m_damage);
			}
		}

		LCF::AudioManager::GetInstance().StopChannel(temp->m_type->m_moveSFX->m_currentChannel);
		LCF::World::GetInstance().deleteActorByID(temp->m_id);
	}

	if (const Wall* temp = dynamic_cast<const Wall*>(_actor))
	{
		if (m_currentDirection < DIRECTION_STOP)
		{
			m_posX = temp->m_posX + temp->m_colliderBox->GetW() + m_weapons[LEFT_WEAPON]->m_weaponType->m_weaponTexture->getWidth();
			m_currentDirection = MAX_NUMBER_TO_THE_LEFT;
		}
		else
		{
			m_posX = temp->m_posX - m_colliderBox->GetW() + m_weapons[RIGHT_WEAPON]->m_weaponType->m_weaponTexture->getWidth();
			m_currentDirection = MAX_NUMBER_TO_THE_RIGHT;
		}

		m_collisionDectected = true;
	}

	if (const MainBullet* temp = dynamic_cast<const MainBullet*>(_actor))
	{
		recieveDamage(temp->m_type->m_damage);

		m_weapons[RIGHT_WEAPON]->recieveDamage((temp->m_type->m_damage) / 4);
		m_weapons[LEFT_WEAPON]->recieveDamage((temp->m_type->m_damage) / 4);

		LCF::World::GetInstance().deleteActorByID(temp->m_id);
	}
}

void PlayerVehicle::coreColision(const Actor * _actor)
{
	if (const SubBullet* temp = dynamic_cast<const SubBullet*>(_actor))
	{
		if (temp->m_type->m_enemy)
		{
			recieveDamage(temp->m_type->m_damage);
			LCF::World::GetInstance().deleteActorByID(temp->m_id);
		}
	}
}