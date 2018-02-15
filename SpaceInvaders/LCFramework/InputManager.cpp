#include "InputManager.h"
#include "Actor.h"

namespace LCF
{
	InputManager::InputManager()
	{
		
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::dispatchInput(SDL_Event _event)
	{
		if (_event.type == SDL_KEYDOWN)
		{
			for (size_t i = 0; i < m_allControllers.size(); i++)
			{
				m_allControllers[i]->checkInput(_event.key.keysym.sym);
			}
		}
	}
	MESSAGE_LOG InputManager::AddController(BaseController* _controller)
	{
		if (_controller == NULL)
			return MESSAGE_ERROR;

		m_allControllers.push_back(_controller);
		return MESSAGE_SUCCESS;
	}
	void InputManager::DestroyAllControllers()
	{
		/*for (size_t i = 0; i < m_allControllers.size(); i++)
		{
			delete m_allControllers[i];
		}*/
	//	m_allControllers.clear();
	}
}
