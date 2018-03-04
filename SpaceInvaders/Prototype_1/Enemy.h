#pragma once

class Enemy : public Pawn
{
public:
	Enemy();
	virtual ~Enemy();

	/**
	* Virtual: Initialize the content of the Actor
	*
	*/
	virtual void init() {};

	/**
	* Virtual: Render the content of the Actor
	*
	* @param _renderer
	* a SDL renderer
	*
	*/
	virtual void render(bool _flip = false);

	/**
	* Virtual: Updates the content of the Actor
	*
	* @param _deltaTime
	* the change of time
	*
	*/
	virtual void update(float /*_deltaTime*/) {};

	virtual void recieveDamage(int _damage);

	LCF::Animator* m_currentAnimation;
	int m_life;
	bool m_dead;
};