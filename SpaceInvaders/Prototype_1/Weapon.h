#pragma once

class Weapon : public Pawn
{
public:
	Weapon();
	~Weapon();

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

	virtual void collision(const Actor* _actor);

	virtual void shoot() {};

public:
	bool m_weaponSelected;
	bool m_collisionDetected;
	int m_direction;

	LCF::Texture* m_weaponReadyTexture;
	LCF::Sfx* m_shootSFX;
	LCF::Sfx* m_changeWeaponSFX;

	Pawn* m_Parent;
};