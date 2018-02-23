#include "Actor.h"
#include "ColliderManager.h"
#include "ColliderBox.h"

namespace LCF
{
	Uint64 Actor::autoID = 0;
	Actor::Actor()
	{
		m_beDestroyed = false;
		m_DestroyMe = false;
	}

	Actor::~Actor()
	{

	}
}