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
		LCF::ColliderBox<Actor>* newBox = new LCF::ColliderBox<Actor>();

		newBox->SetFunction(&Actor::collision);
		newBox->SetActor(this, false);
		newBox->SetSize(m_posX, m_posY, m_texture->getWidth(), m_texture->getHeight());
		//harcode hacer que se pueda activar y desactivar el collider
		LCF::ColliderManager::GetInstance().RegistrerCollider(newBox);
	}
}