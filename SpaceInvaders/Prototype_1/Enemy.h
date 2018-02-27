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
	virtual void render(SDL_Renderer* _renderer);

	/**
	* Virtual: Updates the content of the Actor
	*
	* @param _deltaTime
	* the change of time
	*
	*/
	virtual void update(float _deltaTime) {};

	void recieveDamage(int _damage);

	LCF::Sfx* m_moveSFX;
	LCF::Sfx* m_deadSFX;
	float m_movementSpeed;
	LCF::Animator* m_moveAnimation;
	LCF::Animator* m_deadAnimation;
	LCF::Animator* m_currentAnimation;
	int m_life;
	int m_damage;
	bool m_dead;
};