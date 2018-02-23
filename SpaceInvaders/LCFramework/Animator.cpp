#include "Animator.h"

namespace LCF
{
	Animator::Animator()
	{
		m_timer = 0.0f;
		m_currentJump = 0;
		m_maxRepetitions = 0;
	}

	Animator::~Animator()
	{

	}

	void Animator::update(float _deltaTime)
	{
		if (!m_finished)
		{
			m_timer += _deltaTime;

			if (m_timer > m_animSpeed)
			{
				m_currentJump++;
				m_timer = 0.0f;

				if (m_currentJump > (m_numOfFrames - 1))
				{
					m_currentJump = 0;
					m_currentRepetitions++;
				}
			}

			if (m_maxRepetitions > 0)
			{
				if (m_currentRepetitions >= m_maxRepetitions)
				{
					m_finished = true;
					m_currentJump = 0;
				}
			}
		}
	}

	void Animator::render(int _x, int _y, SDL_Renderer * _renderer)
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

		m_sprite->render(dstRect, srcRect, _renderer);
	}
}