#pragma once

class MainWeapon :public Weapon
{
public:
	MainWeapon();
	~MainWeapon();

	/**
	* Virtual: Initialize the content of the Actor
	*
	*/
	virtual void init(Pawn* _Parent);

	/**
	* Virtual: Updates the content of the Actor
	*
	* @param _deltaTime
	* the change of time
	*
	*/
	virtual void update(float _deltaTime);

	virtual void shoot();

	float m_rateOfFire;
	float m_timer;
	bool m_shooting;
	bool m_canShoot;
};