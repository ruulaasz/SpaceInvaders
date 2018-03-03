#pragma once
#include <ColliderBox.h>

class PlayerVehicle;
typedef LCF::ColliderBox<PlayerVehicle> PlayerVehicleBox;

struct MovementInfo
{
	MovementInfo(int _value) { direction = _value; }
	int direction;
};

class PlayerVehicle : public Pawn
{
public:
	PlayerVehicle();
	~PlayerVehicle();

	/**
	* Virtual: Initialize the content of the Actor
	*
	*/
	virtual void init();

	/**
	* Virtual: Render the content of the Actor
	*
	* @param _renderer
	* a SDL renderer
	*
	*/
	virtual void render(SDL_Renderer* _renderer, bool _flip = false);

	/**
	* Virtual: Updates the content of the Actor
	*
	* @param _deltaTime
	* the change of time
	*
	*/
	virtual void update(float _deltaTime);

	void move(MovementInfo _info);

	void shootMainWeapon(MovementInfo _info);
	void shootRightWeapon(MovementInfo _info);
	void shootLeftWeapon(MovementInfo _info);

	void recieveDamage(int _damage);
	void superShot(MovementInfo _info);

	virtual void collision(const Actor* _actor);
	void coreColision(const Actor* _actor);

public: 
	int m_currentDirection;
	float m_movementSpeed;
	bool m_collisionDectected;
	int m_activeWeapon;

	int m_life;
	int m_lifeMax;

	float m_energy;
	float m_energyRegenerationRate;
	float m_energyMax;

	Weapon* m_weapons[3];
	PlayerVehicleBox* m_coreCollider;

	LCF::Sfx* m_moveSFX;
	LCF::Sfx* m_coreDamageSFX;

	spiText* m_coreLifeText;
	spiText* m_leftShieldText;
	spiText* m_rightShieldText;

	spiText* m_energyText;
};