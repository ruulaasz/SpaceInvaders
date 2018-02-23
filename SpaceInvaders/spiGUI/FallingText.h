#pragma once
#include "spiText.h"

class FallingText
{
public:
	FallingText();
	~FallingText();

	float m_posX;
	float m_posY;

	float m_originPosX;
	float m_originPosY;

	void update(float _deltaTime);
	void render(SDL_Renderer* _renderer);

	spiText m_Text;
	std::string m_String;
	SDL_Color m_color;
	bool m_enable;
};

