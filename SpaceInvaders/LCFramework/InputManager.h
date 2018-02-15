#pragma once
#include "SDL_Manager.h"
#include "Module.h"
#include <vector>
#include "Controller.h"
#include "message.h"

namespace LCF
{
	//idk why this shit is working
	static std::vector<BaseController*> m_allControllers;
	class InputManager : public LFC::Module<InputManager>
	{
	protected:
		
	public:
		//Dispatch any kind of message
		void dispatchInput(SDL_Event _event);
		MESSAGE_LOG AddController(BaseController* _controller);
		void DestroyAllControllers();
	public:
		InputManager();
		virtual ~InputManager();
		
	};
}
