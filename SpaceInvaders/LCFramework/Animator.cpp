#include "Animator.h"

namespace LCF
{
	Animator::Animator()
	{
		m_timer = 0.0f;
		m_currentJump = 0;
		m_maxRepetitions = 0;
	}

	Animator::Animator(const Animator &_animator)
	{
		m_numOfFrames = _animator.m_numOfFrames;
		m_currentJump = _animator.m_currentJump;
		m_frameWidth = _animator.m_frameWidth;
		m_frameHeight = _animator.m_frameHeight;
		m_maxRepetitions = _animator.m_maxRepetitions;
		m_currentRepetitions = _animator.m_currentRepetitions;
		m_animSpeed = _animator.m_animSpeed;
		m_timer = _animator.m_timer;
		m_finished = _animator.m_finished;
		m_sprite = _animator.m_sprite;
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
				}
			}
		}
	}

	void Animator::render(int _x, int _y, SDL_Renderer * _renderer)
	{
		if (!m_finished)
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

	void Animator::resetAnimation()
	{
		m_currentJump = 0;
		m_currentRepetitions = 0;
		m_timer = 0;
		m_finished = false;
	}
}