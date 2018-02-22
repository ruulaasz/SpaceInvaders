#pragma once

class MainBullet : public Bullet
{
public:
	MainBullet();
	MainBullet(int _posX, int _posY);
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
	LCF::Sfx* m_afterShootSFX;
	float m_timer;
	bool m_casketDroped;

	LCF::Animator* m_travelAnimation;
};

