#include "Sprite.h"

namespace LCF
{
	Sprite::Sprite()
	{

	}

	Sprite::~Sprite()
	{

	}

	void Sprite::render(SDL_Rect _dstRect, SDL_Rect _srcRect, SDL_Renderer* _renderer, bool _flip)
	{
		renderEx(&_dstRect, &_srcRect, 0, _renderer, _flip);
	}
}