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

	/**
	* Virtual: Render the content of the Actor
	*
	* @param _renderer
	* a SDL renderer
	*
	*/
	virtual void render(SDL_Renderer* _renderer);

	virtual void shoot();

	BulletType* m_bulletType;
};