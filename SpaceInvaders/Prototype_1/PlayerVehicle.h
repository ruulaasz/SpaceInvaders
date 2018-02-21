#pragma once

struct MovementInfo
{
	MovementInfo(int _value) { direction = _value; }
	int direction;
};

class PlayerVehicle : public LCF::Actor
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

public: 
	int m_currentDirection;
	float m_movementSpeed;
	bool m_weaponSelected;

	LCF::Texture* m_weaponReadyTexture;
	SideWeapon m_subWeaponA;
	SideWeapon m_subWeaponB;

	LCF::Sfx* m_moveSFX;
	LCF::Sfx* m_shootSFX;
	LCF::Sfx* m_changeWeaponSFX;
};