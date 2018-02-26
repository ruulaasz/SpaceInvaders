#pragma once

class SkyEnemy : public Pawn
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

	void recieveDamage(int _damage);

	virtual void collision(const Actor* _actor);

	LCF::Sfx* m_moveSFX;
	LCF::Sfx* m_deadSFX;
	float m_movementSpeed;
	LCF::Animator* m_animator;
	LCF::Animator* m_currentAnimation;
	int m_life;
	int m_damage;
	bool m_dead;
};