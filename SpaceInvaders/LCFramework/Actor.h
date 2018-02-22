#pragma once
#include "SDL_Manager.h"
#include "Texture.h"
#include "ColliderBox.h"
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

		/**
		* Virtual: Render the content of the Actor
		*
		* @param _renderer
		* a SDL renderer
		*
		*/
		virtual void render(SDL_Renderer* _renderer) = 0;

		/**
		* Virtual: Updates the content of the Actor
		*
		* @param _deltaTime
		* the change of time
		*
		*/
		virtual void update(float _deltaTime) = 0;

		virtual void collision(const Actor* _actor) = 0;

	public:
		int m_id;
		float m_posX;
		float m_posY;
		
		Texture* m_texture;
	};
}