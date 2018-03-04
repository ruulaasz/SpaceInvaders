#pragma once

#include "Asset.h"
#include "SDL_Manager.h"

namespace LCF
{
	/**
	* Container class for a SDL 2.0 texture.
	*/
	class Texture : public Asset
	{
	public:
		Texture();
		Texture(SDL_Texture* _copy);
		virtual ~Texture();

		/**
		* Loads a texture from a file.
		*
		* @param _path
		* String to the file direction.
		*
		* @param _renderer
		* Reference to a SDL_Renderer.
		*
		*/
		bool loadFromFile(std::string _path, SDL_Renderer* _renderer);

		/**
		* Free the texture from the memory.
		*
		*/
		void free();
		void Destroy();

		/**
		* Get the Width of the texture.
		*
		* @return m_width
		*
		*/
		int getWidth() { return m_width; };

		/**
		* Get the Height of the texture.
		*
		* @return m_height
		*
		*/
		int getHeight() { return m_height; };

	public:
		SDL_Texture* m_sdlTexture;

	protected:
		int m_width;
		int m_height;
	};
}