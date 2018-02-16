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

	/**
	* Manager class for inputs
	*/
	class InputManager : public LFC::Module<InputManager>
	{
	public:
		InputManager();
		virtual ~InputManager();

		/**
		* Dispatch any kind of message
		*
		* @param _event
		* a SDL event
		*
		*/
		void dispatchInput(SDL_Event _event);

		/**
		* Add a new _controller
		*
		* @param _event
		* Pointer to a controller
		*
		*/
		MESSAGE_LOG AddController(BaseController* _controller);

		/**
		* Erase all controllers
		*
		*/
		void DestroyAllControllers();

		/**
		* Get the number of controllers
		*
		* @return int
		* Number of controllers
		*
		*/
		int GetControllerNumber();
	};
}
