#pragma once
#include "SDL_Manager.h"

namespace LCF
{
	/**
	* A container class for an Actor
	*/
	class Actor
	{
	public:
		Actor();
		virtual ~Actor();

		int m_id;
		int m_posX;
		int m_posY;

		/**
		* Virtual: Render the content of the Actor
		*
		* @param _renderer
		* a SDL renderer
		*
		*/
		virtual void render(SDL_Renderer* _renderer) = 0;
	};
}