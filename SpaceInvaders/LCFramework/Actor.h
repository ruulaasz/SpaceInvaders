#pragma once

#include "SDL_Manager.h"
#include "Texture.h"
#include "ColliderBox.h"
#include "Transform.h"
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
		virtual void render(bool _flip = false) = 0;

		/**
		* Virtual: Updates the content of the Actor
		*
		* @param _deltaTime
		* the change of time
		*
		*/
		virtual void update(float _deltaTime) = 0;

		virtual void collision(const Actor* _actor) = 0;

		virtual void destroy() = 0;

	public:
		Transform m_transform;
		bool m_beDestroyed;
		bool m_DestroyMe;

		Texture* m_texture;
		Uint64 m_id;
		std::string m_name;

		static Uint64 autoID;
	};
}