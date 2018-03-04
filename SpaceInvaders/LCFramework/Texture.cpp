#include "Texture.h"

namespace LCF
{
	Texture::Texture()
	{
		m_sdlTexture = nullptr;
		m_width = 0;
		m_height = 0;
	}

	Texture::Texture(SDL_Texture * _copy)
	{
		m_sdlTexture = _copy;
	}

	Texture::~Texture()
	{
		//free();
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
	void Texture::Destroy()
	{
		free();
	}
}