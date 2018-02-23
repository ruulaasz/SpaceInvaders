#include "TextManager.h"

TextManager::TextManager()
{

}

TextManager::~TextManager()
{

}

void TextManager::update(float _deltaTime)
{
	for (size_t i = 0; i < m_fallingText.size(); i++)
	{
		if (m_fallingText.at(i)->m_enable)
		{
			m_fallingText.at(i)->update(_deltaTime);
		}
		else
		{
			m_fallingText.erase(m_fallingText.begin() + i);
		}
	}
}

void TextManager::render(SDL_Renderer * _renderer)
{
	for (size_t i = 0; i < m_fallingText.size(); i++)
	{
		m_fallingText.at(i)->render(_renderer);
	}
}