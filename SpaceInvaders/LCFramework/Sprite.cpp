#include "Sprite.h"

namespace LCF
{
	Sprite::Sprite()
	{

	}

	Sprite::~Sprite()
	{

	}

	void Sprite::render(SDL_Rect _dstRect, SDL_Rect _srcRect, bool _flip)
	{
		LCF::SDL_Manager::GetInstance().RenderAnimation(&LCF::Texture(m_sdlTexture), &_dstRect, &_srcRect, _flip);
	}
}