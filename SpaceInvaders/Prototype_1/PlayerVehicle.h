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
	virtual void init(int _screenW, int _screenH);

	/**
	* Virtual: Render the content of the Actor
	*
	* @param _renderer
	* a SDL renderer
	*
	*/
	virtual void render(SDL_Renderer* _renderer);

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

	virtual void collision(const Actor* _actor);
	void coreColision(const Actor* _actor);

public: 
	int m_currentDirection;
	float m_movementSpeed;
	bool m_collisionDectected;
	int m_life;

	Weapon* m_weapons[3];
	PlayerVehicleBox* m_coreCollider;
	LCF::Sfx* m_moveSFX;
};