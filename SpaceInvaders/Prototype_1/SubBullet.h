#pragma once

class SubBullet : public Bullet
{
public:
	SubBullet();
	~SubBullet();

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

	void setType(BulletType* _type);

	int m_direction;
};