#pragma once

class GroundEnemy : public Enemy
{
public:
	GroundEnemy();
	~GroundEnemy();

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
	virtual void render(SDL_Renderer* _renderer);

	virtual void collision(const Actor* _actor);

	void setType(EnemyType* _type);

	int m_direction;
	EnemyType* m_type;
	SideWeapon* m_weapon;
};