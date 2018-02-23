#include "FallingText.h"

FallingText::FallingText()
{
	FontData data;
	data._fontSize = 16;
	data._pathFontFile = "c:/windows/fonts/arialbd.ttf";
	m_Text.Initialize(data);

	SDL_Color c;
	c.r = 255;
	c.g = 0;
	c.b = 0;

	m_color = c;

	m_enable = true;
}

FallingText::~FallingText()
{

}

void FallingText::update(float _deltaTime)
{
	if (m_posY < m_originPosY + 50)
	{
		m_posX += _deltaTime * 50;
		m_posY += _deltaTime * 100;
	}
	else
	{
		m_enable = false;
	}
}

void FallingText::render(SDL_Renderer * _renderer)
{
	if (m_enable)
	{
		m_Text.RenderSolidText(m_String, m_color, m_posX, m_posY, *_renderer);
	}
}