#pragma once
#include "Texture.h"

class Sprite : public Texture
{
public:
	Sprite();
	~Sprite();

	void render(int _x, int _y, SDL_Renderer* _renderer);
	void update(float _deltaTime);

public:
	unsigned int m_maxJumps;
	unsigned int m_currentJump;
	unsigned int m_frameWidth;
	unsigned int m_frameHeight;
	float m_animSpeed;
	float m_timer;
};