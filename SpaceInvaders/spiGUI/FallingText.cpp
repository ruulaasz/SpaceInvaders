#include "FallingText.h"

FallingText::FallingText()
{
	
}

FallingText::~FallingText()
{

}

void FallingText::update(float _deltaTime)
{
	if (m_posY < m_originPosY + 75)
	{
		m_posX += _deltaTime * 50;
		m_posY += _deltaTime * 150;
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
		RenderSolidText(m_String, m_color, m_posX, m_posY, *_renderer);
	}
}