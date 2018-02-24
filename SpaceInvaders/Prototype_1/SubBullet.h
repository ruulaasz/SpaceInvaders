#pragma once
#include "MainBullet.h"

class SubBullet : public Bullet
{
public:
	SubBullet();
	SubBullet(float _posX, float _posY, int _direction);
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

	virtual void collision(const Actor* /*_actor*/) {};

	int m_direction;
};