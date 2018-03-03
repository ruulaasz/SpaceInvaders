#pragma once

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

	/**
	* Virtual: Render the content of the Actor
	*
	* @param _renderer
	* a SDL renderer
	*
	*/
	virtual void render(SDL_Renderer* _renderer, bool _flip = false);

	virtual void collision(const Actor* _actor);

	virtual void shoot();

	virtual void recieveDamage(int _damage);

	BulletType* m_bulletType;

	LCF::Sfx* m_shieldDamageSFX;
};