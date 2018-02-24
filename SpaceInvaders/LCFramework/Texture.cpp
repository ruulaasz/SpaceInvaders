#include "Texture.h"

namespace LCF
{
	Texture::Texture()
	{
		m_sdlTexture = nullptr;
		m_width = 0;
		m_height = 0;
	}

	Texture::~Texture()
	{
		free();
	}

	bool Texture::loadFromFile(std::string _path, SDL_Renderer* _renderer)
	{
		free();

		SDL_Texture* newTexture = nullptr;

		SDL_Surface* loadedSurface = IMG_Load(_path.c_str());

		if (loadedSurface == nullptr)
		{
			printf("Cannot load image %s SDL_image Error: %s\n", _path.c_str(), IMG_GetError());
		}
		else
		{
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
			if (newTexture == nullptr)
			{
				printf("Failed to create texture %s SDL Error: %s\n", _path.c_str(), SDL_GetError());
			}
			else
			{
				m_width = loadedSurface->w;
				m_height = loadedSurface->h;
			}

			SDL_FreeSurface(loadedSurface);
		}

		m_sdlTexture = newTexture;

		return m_sdlTexture != nullptr;
	}

	void Texture::renderEx(int _x, int _y, float _w, float _h, double _angle, SDL_Renderer * _renderer)
	{
		SDL_Rect renderQuad = { _x, _y, m_width * (int)_w, m_height * (int)_h };
		SDL_RenderCopyEx(_renderer, m_sdlTexture, nullptr, &renderQuad, _angle, nullptr, SDL_FLIP_NONE);
	}

	void Texture::free()
	{
		if (m_sdlTexture != nullptr)
		{
			SDL_DestroyTexture(m_sdlTexture);
			m_sdlTexture = nullptr;
			m_width = 0;
			m_height = 0;
		}
	}

	void Texture::render(int _x, int _y, SDL_Renderer* _renderer)
	{
		SDL_Rect renderQuad = { _x, _y, m_width, m_height };
		SDL_RenderCopy(_renderer, m_sdlTexture, nullptr, &renderQuad);
	}

	void Texture::render(SDL_Rect* _dstRect, SDL_Rect* _srcRect, SDL_Renderer* _renderer)
	{
		SDL_RenderCopy(_renderer, m_sdlTexture, _srcRect, _dstRect);
	}

	void Texture::renderEx(SDL_Rect * _dstRect, SDL_Rect * _srcRect, double _angle, SDL_Renderer * _renderer)
	{
		SDL_RenderCopyEx(_renderer, m_sdlTexture, _srcRect, _dstRect, _angle, nullptr, SDL_FLIP_NONE);
	}
}