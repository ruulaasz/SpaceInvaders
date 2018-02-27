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
	virtual void render(SDL_Renderer* _renderer);

	/**
	* Virtual: Updates the content of the Actor
	*
	* @param _deltaTime
	* the change of time
	*
	*/
	virtual void update(float _deltaTime);

	virtual void collision(const Actor* _actor);

	virtual void shoot() {};

	void recieveDamage(int _damage);
	
public:
	bool m_weaponSelected;
	int m_direction;
	float m_rateOfFire;
	float m_rateTimer;
	bool m_canShoot;
	int m_life;

	LCF::Texture* m_weaponReadyTexture;
	LCF::Sfx* m_shootSFX;
	LCF::Sfx* m_changeWeaponSFX;
	LCF::Animator* m_shootAnimation;

	Pawn* m_Parent;
};