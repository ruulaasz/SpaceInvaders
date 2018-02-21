#pragma once

class SideWeapon : public LCF::Actor
{
public:
	SideWeapon();
	~SideWeapon();

	/**
	* Virtual: Initialize the content of the Actor
	*
	*/
	virtual void init();

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

	void shootMainWeapon(int _posX, int _posY, int _direction);

public:
	bool m_weaponSelected;

	LCF::Texture* m_weaponReadyTexture;
};

