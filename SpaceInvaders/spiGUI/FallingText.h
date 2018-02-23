#pragma once
#include "spiText.h"

class FallingText : public spiText
{
public:
	FallingText();
	~FallingText();

	float m_originPosX;
	float m_originPosY;

	virtual void update(float _deltaTime);
	virtual void render(SDL_Renderer* _renderer);
};