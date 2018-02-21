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
		
	public:
		void Init();
		void Update(float _deltaTime);
		void Render(SDL_Renderer* _renderer);
		void Destroy();
		MESSAGE_LOG RegistrerCollider(BaseColliderBox* _Collider);
	public:
		ColliderManager();
		virtual ~ColliderManager();
	};
}

