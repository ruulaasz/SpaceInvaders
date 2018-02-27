#pragma once

class Bullet : public Pawn
{
public:
	Bullet();
	~Bullet();

	/**
	* Virtual: Render the content of the Actor
	*
	* @param _renderer
	* a SDL renderer
	*
	*/
	virtual void render(SDL_Renderer* _renderer);

	float m_movementSpeed;
	int m_damage;
	LCF::Animator* m_travelAnimation;
	LCF::Animator* m_deadAnimation;
	LCF::Animator* m_currentAnimation;
	bool m_dead;
	bool m_outOfLimits;
	LCF::Sfx* m_impactSFX;
	bool m_enemy;
};