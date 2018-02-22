#pragma once
#include "Texture.h"

namespace LCF
{
	/**
	* A container class for an Sprite
	*/
	class Sprite : public LCF::Texture
	{
	public:
		Sprite();
		~Sprite();

		/**
		* Render the content of the Sprite
		*
		* @param _x
		* Position in the x axis of the screen.
		*
		* @param _y
		*  Position in the y axis of the screen.
		*
		* @param _renderer
		* a SDL renderer
		*
		*/
		void render(SDL_Rect _dstRect , SDL_Rect _srcRect , SDL_Renderer* _renderer);
	};
}