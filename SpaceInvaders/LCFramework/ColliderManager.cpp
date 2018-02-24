#include "ColliderManager.h"
#include "ColliderBox.h"

namespace LCF
{
	Uint64 ColliderManager::autoID = 0;
	void ColliderManager::Init()
	{

	}

	void ColliderManager::Update(float _deltaTime)
	{
		for (size_t i = 0; i < m_allColliders.size(); i++)
		{
			if (m_allColliders[i]->GetEnabled())
			{
				m_allColliders[i]->Update(_deltaTime);
				for (size_t j = 0; j < m_allColliders.size(); j++)
				{
					if (j != i && m_allColliders[j]->GetEnabled())
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
		if (m_EnabledRender)
		{
			for (size_t i = 0; i < m_allColliders.size(); i++)
			{
				if (m_allColliders[i]->GetEnabled())
				{
					SDL_Rect renderQuad = { (int)m_allColliders[i]->GetX(), (int)m_allColliders[i]->GetY(), (int)m_allColliders[i]->GetW(), (int)m_allColliders[i]->GetH() };
					SDL_RenderDrawRect(_renderer, &renderQuad);
				}
			}
		}
#endif
	}

	void ColliderManager::Destroy()
	{
		for (size_t i = 0; i < m_allColliders.size(); i++)
		{
			delete m_allColliders[i];
		}

		m_allColliders.clear();
	}

	MESSAGE_LOG ColliderManager::DestroyColliderbyID(Uint64 _id)
	{
		for (size_t i = 0; i < m_allColliders.size(); i++)
		{
			if (m_allColliders[i]->GetID() == _id)
			{
				BaseColliderBox* destroyCollider = m_allColliders[i];
				destroyCollider->Destroy();
				delete destroyCollider;
				m_allColliders.erase(m_allColliders.begin() + i);
				return MESSAGE_SUCCESS("The collider is delete");
			}
		}
		return MESSAGE_WARNING("Cant find the ID");
	}

	MESSAGE_LOG ColliderManager::RegistrerCollider(BaseColliderBox * _Collider)
	{
		if (_Collider == NULL)
			return MESSAGE_WARNING("The collider is null");

		_Collider->SetId(autoID);
		autoID++;
		m_allColliders.push_back(_Collider);
	
		return MESSAGE_SUCCESS("Succes to add");
	}

	void ColliderManager::SetEnabledRender(bool _value)
	{
		m_EnabledRender = _value;
	}

	bool ColliderManager::GetEnabledRender()
	{
		return m_EnabledRender;
	}

	ColliderManager::ColliderManager()
	{

	}

	ColliderManager::~ColliderManager()
	{

	}
}