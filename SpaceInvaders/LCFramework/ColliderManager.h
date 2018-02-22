#pragma once
#include "message.h"
#include <vector>
#include "Module.h"
#include "SDL_Manager.h"
namespace LCF
{
	class BaseColliderBox;

	static std::vector<BaseColliderBox*> m_allColliders;

	class ColliderManager : public LCF::Module<ColliderManager>
	{
	protected:
		bool m_EnabledRender;
	public:
		void Init();

		void Update(float _deltaTime);

		void Render(SDL_Renderer* _renderer);

		void Destroy();

		MESSAGE_LOG RegistrerCollider(BaseColliderBox* _Collider);

		void SetEnabledRender(bool _value);

		bool GetEnabledRender();

	public:
		ColliderManager();
		virtual ~ColliderManager();
	};
}

