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

	virtual void collision(const Actor* _actor);

	int m_direction;

	EnemyType* m_type;
};