#pragma once

class SideWeaponB :public Weapon
{
public:
	SideWeaponB();
	~SideWeaponB();

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
	bool m_canShoot;
	bool m_isShooting;
	float m_burstTimer;
	int m_bulletsFired;
};