#pragma once
#include "SDL_Manager.h"
#include "Sprite.h"

namespace LCF
{
	class Animator
	{
	public:
		Animator();
		virtual ~Animator();

		/**
		* Update the content of the Sprite
		*
		* @param _deltaTime
		* the change of time
		*
		*/
		void update(float _deltaTime);

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


	public:
		unsigned int m_maxJumps;
		unsigned int m_currentJump;
		unsigned int m_frameWidth;
		unsigned int m_frameHeight;
		float m_animSpeed;
		float m_timer;

		Sprite* m_sprite;
	};
}