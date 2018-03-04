#pragma once

class Weapon : public Pawn
{
public:
	Weapon();
	~Weapon();

	/**
	* Virtual: Initialize the content of the Actor
	*
	*/
	virtual void init(Pawn* _Parent);

	/**
	* Virtual: Render the content of the Actor
	*
	* @param _renderer
	* a SDL renderer
	*
	*/
	virtual void render(bool _flip = false);

	/**
	* Virtual: Updates the content of the Actor
	*
	* @param _deltaTime
	* the change of time
	*
	*/
	virtual void update(float _deltaTime);

	virtual void collision(const Actor* /*_actor*/) {};

	virtual void shoot() {};

	virtual void recieveDamage(int _damage);

	void setType(WeaponType* _type);
	
public:
	bool m_weaponSelected;
	int m_direction;
	float m_rateTimer;
	bool m_canShoot;
	LCF::Sfx* m_changeWeaponSFX;
	Pawn* m_Parent;
	int m_life;
	bool m_dead;

	WeaponType* m_weaponType;
};