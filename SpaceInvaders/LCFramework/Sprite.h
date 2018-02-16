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
		void render(int _x, int _y, SDL_Renderer* _renderer);

		/**
		* Update the content of the Sprite
		*
		* @param _deltaTime
		* the change of time
		*
		*/
		void update(float _deltaTime);

	public:
		unsigned int m_maxJumps;
		unsigned int m_currentJump;
		unsigned int m_frameWidth;
		unsigned int m_frameHeight;
		float m_animSpeed;
		float m_timer;
	};
}