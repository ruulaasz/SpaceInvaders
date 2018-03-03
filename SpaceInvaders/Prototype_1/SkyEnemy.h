#pragma once

class SkyEnemy : public Enemy
{
public:
	SkyEnemy();
	~SkyEnemy();

	/**
	* Virtual: Initialize the content of the Actor
	*
	*/
	virtual void init();

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

	void setType(EnemyType* _type);

	virtual void recieveDamage(int _damage);

	EnemyType* m_type;
	MainWeapon* m_weapon;

	float m_shootTimer;
	float m_shootTime;
};