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
		//hay error en la logica del tamaño de la imagen con el collider checar las balas
		m_colliderBox->SetSize(m_posX, m_posY, m_texture->getWidth(), m_texture->getHeight());
		//harcode hacer que se pueda activar y desactivar el collider
		LCF::ColliderManager::GetInstance().RegistrerCollider(m_colliderBox);
	}
}