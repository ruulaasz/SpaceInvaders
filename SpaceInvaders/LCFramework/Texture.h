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
		* Render the texture in a given screen coordinate.
		*
		* @param _x
		* Position in the x axis of the screen.
		*
		* @param _y
		*  Position in the y axis of the screen.
		*
		* @param _renderer
		* Reference to a SDL_Renderer.
		*
		*/
		void render(int _x, int _y, SDL_Renderer* _renderer, bool _flip = false);

		/**
		* Render the given section of a texture in a given rect.
		*
		* @param _dstRect
		* The rect where will be rendered
		*
		* @param _srcRect
		* The section of the texture to render
		*
		* @param _renderer
		* Reference to a SDL_Renderer.
		*
		*/
		void render(SDL_Rect* _dstRect, SDL_Rect* _srcRect, SDL_Renderer* _renderer);

		/**
		* Render the given section of a texture in a given rect and rotates it.
		*
		* @param _dstRect
		* The rect where will be rendered
		*
		* @param _srcRect
		* The section of the texture to render
		*
		* @param _angle
		* A rotation angle
		*
		* @param _renderer
		* Reference to a SDL_Renderer.
		*
		*/
		void renderEx(SDL_Rect* _dstRect, SDL_Rect* _srcRect, double _angle, SDL_Renderer* _renderer, bool _flip = false);

		/**
		* Render the texture in a given screen coordinate with a given rotation.
		*
		* @param _x
		* Position in the x axis of the screen.
		*
		* @param _y
		* Position in the y axis of the screen.
		*
		*
		* @param _w
		* The width scale of the texture.
		*
		* @param _h
		* The height scale of the texture.
		*
		* @param _angle
		* A rotation angle
		*
		* @param _renderer
		* Reference to a SDL_Renderer.
		*
		*/
		void renderEx(int _x, int _y, float _w, float _h, double _angle, SDL_Renderer* _renderer);

		/**
		* Free the texture from the memory.
		*
		*/
		void free();

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

	private:
		int m_width;
		int m_height;
	};
}