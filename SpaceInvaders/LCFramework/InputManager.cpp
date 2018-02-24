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
		for (size_t i = 0; i < m_allControllers.size(); i++)
		{
			m_allControllers[i]->checkInput((char)_event.key.keysym.sym, _event.type);
		}
	}

	MESSAGE_LOG InputManager::AddController(BaseController* _controller)
	{
		if (_controller == NULL)
		{
			return MESSAGE_WARNING("The pointer of the controller is NULL");
		}

		m_allControllers.push_back(_controller);

		return MESSAGE_SUCCESS("The controller now is in the input Manager");
	}

	void InputManager::DestroyAllControllers()
	{
		//while (!m_allControllers.empty()) delete m_allControllers.back(), m_allControllers.pop_back();
	}

	int InputManager::GetControllerNumber()
	{
		return m_allControllers.size();
	}
}