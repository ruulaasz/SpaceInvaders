#pragma once
#include "Module.h"
#include <vector>
#include "FallingText.h"

class TextManager : public Module<TextManager>
{
public:
	TextManager();
	~TextManager();

	virtual void update(float _deltaTime);
	virtual void render(SDL_Renderer* _renderer);

	std::vector<spiText*> m_fallingText;
};

