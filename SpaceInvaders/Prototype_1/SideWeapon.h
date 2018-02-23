#pragma once
#include <ColliderBox.h>

class SideWeapon;
typedef LCF::ColliderBox<SideWeapon> SideWeaponBox;

class SideWeapon : public Weapon
{
public:
	SideWeapon();
	~SideWeapon();

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

	void shieldColision(const Actor* _actor);

	SideWeaponBox* m_shieldCollider;
};