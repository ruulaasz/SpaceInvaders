#pragma once
#include <ColliderBox.h>
struct MovementInfo
{
	MovementInfo(int _value) { direction = _value; }
	int direction;
};
class PlayerVehicle;
typedef LCF::ColliderBox<PlayerVehicle> PlayerVehicleBox;
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
	void shootSubWeaponA(MovementInfo _info);
	void shootSubWeaponB(MovementInfo _info);

	virtual void collision(const Actor* _actor);

	void SecondCollision(const Actor* _actor);
public: 
	int m_currentDirection;
	float m_movementSpeed;
	bool m_collisionDectected;

	MainWeapon m_mainWeapon;
	SideWeapon m_subWeaponA;
	SideWeaponB m_subWeaponB;
	PlayerVehicleBox* m_secondBox;
	LCF::Sfx* m_moveSFX;
};