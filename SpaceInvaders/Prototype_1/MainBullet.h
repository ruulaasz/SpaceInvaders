#pragma once

class MainBullet : public LCF::Actor
{
public:
	MainBullet() {};
	MainBullet(int _posX, int _posY, int _direction);
	virtual ~MainBullet();

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

	virtual void collision(const Actor* _actor);

public:
	float m_movementSpeed;
	int m_direction;
	LCF::Sfx* m_afterShootSFX;
	float m_timer;
	bool m_casketDroped;
};

