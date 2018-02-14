#include "Sprite.h"

Sprite::Sprite()
{
	m_maxJumps = 4;
	m_frameHeight = 100;
	m_frameWidth = 100;
	m_animSpeed = 0.5f;

	m_timer = 0.0f;
	m_currentJump = 0;
}

Sprite::~Sprite()
{

}

void Sprite::render(int _x, int _y, SDL_Renderer* _renderer)
{
	SDL_Rect dstRect;
	dstRect.x = _x;
	dstRect.y = _y;
	dstRect.w = m_frameWidth;
	dstRect.h = m_frameHeight;

	SDL_Rect srcRect;
	srcRect.x = m_frameWidth * m_currentJump;
	srcRect.y = 0;
	srcRect.w = m_frameWidth;
	srcRect.h = m_frameHeight;

	renderEx(&dstRect, &srcRect, 0, _renderer);
}

void Sprite::update(float _deltaTime)
{
	m_timer += _deltaTime;

	if (m_timer > m_animSpeed)
	{
		m_currentJump++;
		m_timer = 0.0f;
	}

	if (m_currentJump > m_maxJumps)
	{
		m_currentJump = 0;
	}
}