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
	virtual void render(SDL_Renderer* _renderer, bool _flip = false);

	LCF::Animator* m_currentAnimation;

	BulletType* m_type;
	bool m_dead;
};