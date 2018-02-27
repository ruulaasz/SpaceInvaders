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

	virtual void collision(const Actor* _actor);

	virtual void shoot();

public:
	bool m_isShooting;
	float m_burstTimer;
	int m_bulletsFired;
};