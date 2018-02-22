#include "ColliderManager.h"
#include "ColliderBox.h"

namespace LCF
{
	void ColliderManager::Init()
	{

	}

	void ColliderManager::Update(float _deltaTime)
	{
		for (int i = 0; i < m_allColliders.size(); i++)
		{
			if (m_allColliders[i]->GetEnabled())
			{
				m_allColliders[i]->Update(_deltaTime);
				for (int j = 0; j < m_allColliders.size(); j++)
				{
					if (j != i)
					{
						m_allColliders[i]->CheckCollision(m_allColliders[j]);
					}
				}
			}
		}
	}

	void ColliderManager::Render(SDL_Renderer * _renderer)
	{
#ifdef _DEBUG
		for (size_t i = 0; i < m_allColliders.size(); i++)
		{
			if (m_allColliders[i]->GetEnabled())
			{
				SDL_Rect renderQuad = { m_allColliders[i]->GetX(), m_allColliders[i]->GetY(), m_allColliders[i]->GetW(), m_allColliders[i]->GetH() };
				SDL_RenderDrawRect(_renderer, &renderQuad);
			}
		}
#endif
	}

	void ColliderManager::Destroy()
	{
		for (int i = 0; i < m_allColliders.size(); i++)
		{
			delete m_allColliders[i];
		}

		m_allColliders.clear();
	}

	MESSAGE_LOG ColliderManager::RegistrerCollider(BaseColliderBox * _Collider)
	{
		if (_Collider == NULL)
			return MESSAGE_WARNING("The collider is null");

		m_allColliders.push_back(_Collider);
	
		return MESSAGE_SUCCESS("Succes to add");
	}

	ColliderManager::ColliderManager()
	{

	}

	ColliderManager::~ColliderManager()
	{

	}
}