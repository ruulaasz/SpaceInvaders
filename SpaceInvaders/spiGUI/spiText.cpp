#include "spiText.h"
#include <iostream>

spiText::spiText()
{
	FontData data;
	data._fontSize = 20;
	data._pathFontFile = "c:/windows/fonts/arialbd.ttf";
	Initialize(data);

	SDL_Color c;
	c.r = 255;
	c.g = 255;
	c.b = 255;

	m_color = c;

	m_enable = true;
}

spiText::~spiText()
{

}

bool spiText::LoadFont(const char & _pathFontFile, int _fontSize)
{
	m_font = TTF_OpenFont(&_pathFontFile, _fontSize);

	if (m_font == NULL) {
		TTF_SetError("Loading failed :( (code: %d)", 142);
		std::cout << "Error: " << TTF_GetError() << std::endl;
		return false;
	}
	return true;
}

void spiText::RenderSolidText(std::string& _text, SDL_Color& _textColor, int _x,
	int _y, SDL_Renderer& _renderer)
{
	//Get rid of preexisting texture
	SDL_DestroyTexture(m_message);

	SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, _text.c_str(), _textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		m_message = SDL_CreateTextureFromSurface(&_renderer, textSurface);
		if (m_message == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_messageRect.x = _x;
			m_messageRect.y = _y;
			m_messageRect.w = textSurface->w;
			m_messageRect.h = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Draw to the screen
	SDL_RenderCopy(&_renderer, m_message, NULL, &m_messageRect);
}

void spiText::RenderShadedText(std::string& _text, SDL_Color& _backgroundColor, SDL_Color& _textColor, int _x,
	int _y, SDL_Renderer& _renderer)
{
	//Get rid of preexisting texture
	SDL_DestroyTexture(m_message);

	SDL_Surface* textSurface = TTF_RenderText_Shaded(m_font, _text.c_str(), _textColor, _backgroundColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		m_message = SDL_CreateTextureFromSurface(&_renderer, textSurface);
		if (m_message == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_messageRect.x = _x;
			m_messageRect.y = _y;
			m_messageRect.w = textSurface->w;
			m_messageRect.h = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Draw to the screen
	SDL_RenderCopy(&_renderer, m_message, NULL, &m_messageRect);
}

void spiText::RenderBlendedText(std::string& _text, SDL_Color& _textColor, int _x,
	int _y, SDL_Renderer& _renderer)
{
	//Get rid of preexisting texture
	SDL_DestroyTexture(m_message);

	SDL_Surface* textSurface = TTF_RenderText_Blended(m_font, _text.c_str(), _textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		m_message = SDL_CreateTextureFromSurface(&_renderer, textSurface);
		if (m_message == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_messageRect.x = _x;
			m_messageRect.y = _y;
			m_messageRect.w = textSurface->w;
			m_messageRect.h = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Draw to the screen
	SDL_RenderCopy(&_renderer, m_message, NULL, &m_messageRect);
}

bool spiText::Initialize(const FontData& _fontData)
{
	if (TTF_Init() < 0) {
		printf("Can´t init SDL Font system");
		return false;
	}

	if (!LoadFont(*_fontData._pathFontFile, _fontData._fontSize))
	{
		printf("Can´t load font");
		return false;
	}
	return true;
}

void spiText::Destroy()
{
	delete m_surfaceMessage;
	m_surfaceMessage = nullptr;
	m_message = nullptr;
	TTF_CloseFont(m_font);
	TTF_Quit();
}

void spiText::update(float /*_deltaTime*/)
{

}

void spiText::render(SDL_Renderer * _renderer)
{
	RenderSolidText(m_String, m_color, (int)m_posX, (int)m_posY, *_renderer);
}