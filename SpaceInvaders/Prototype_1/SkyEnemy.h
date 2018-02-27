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

	virtual void collision(const Actor* _actor);

	EnemyType* m_type;
};