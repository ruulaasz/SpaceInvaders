#include "Actor.h"
#include "ColliderManager.h"
#include "ColliderBox.h"

namespace LCF
{
	Actor::Actor()
	{

	}

	Actor::~Actor()
	{

	}

	void Actor::init()
	{
		m_colliderBox = new LCF::ColliderBox<Actor>();

		m_colliderBox->SetFunction(&Actor::collision);
		m_colliderBox->SetActor(this, false);
		m_colliderBox->SetSize(m_posX, m_posY, m_texture->getWidth(), m_texture->getHeight());
		//harcode hacer que se pueda activar y desactivar el collider
		LCF::ColliderManager::GetInstance().RegistrerCollider(m_colliderBox);
	}
}