/********************************************************************/
/**
* @LC	  2018/02/21
* @file   spiText.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2018/02/21
* @brief  This class help us to print text
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_ttf.lib")

/************************************************************************/
/* Includes												                */
/************************************************************************/
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

/************************************************************************/
/* Structures											                */
/************************************************************************/
struct FontData																									/*!< Data to init the font */
{
	char* _pathFontFile;
	int _fontSize;

	FontData()
	{
		_pathFontFile = "c:/windows/fonts/arialbd.ttf";
		_fontSize = 24;
	}
};

/************************************************************************/
/* spiText												                */
/************************************************************************/
class spiText
{
	/************************************************************************/
	/* Constructor and Destructor Definitions				                */
	/************************************************************************/
public:
	spiText();
	virtual ~spiText();

	/************************************************************************/
	/* Class functions										                */
	/************************************************************************/
public:
	bool Initialize(const FontData& _fontData);
	bool LoadFont(const char& _pathFontFile, int _fontSize);
	void RenderSolidText(std::string& _text, SDL_Color& _textColor, int _x,										/*!< Render a solid text */
		int _y, SDL_Renderer& _renderer);
	void RenderShadedText(std::string& _text, SDL_Color& _backgroundColor, SDL_Color& _textColor, int _x,		/*!< Render a shaded text */
		int _y, SDL_Renderer& _renderer);
	void RenderBlendedText(std::string& _text, SDL_Color& _textColor, int _x,									/*!< Render a blended text */
		int _y, SDL_Renderer& _renderer);
	void Destroy();

	virtual void update(float _deltaTime);
	virtual void render(SDL_Renderer* _renderer);

	/************************************************************************/
	/* Classs variables										                */
	/************************************************************************/
private:
	TTF_Font* m_font;																							/*!< Pointer to font data */
	SDL_Surface* m_surfaceMessage;																				/*!< Pointer to surface */
	SDL_Texture* m_message;																						/*!< Pointer to texture message */
	SDL_Rect m_messageRect;																						/*!< Rect of the texture message */

public:
	std::string m_String;
	SDL_Color m_color;
	bool m_enable;

	float m_posX;
	float m_posY;
};