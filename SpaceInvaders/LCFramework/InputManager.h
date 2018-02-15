#pragma once
#include "SDL_Manager.h"

class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	void dispatchInput(SDL_Event _event);
};

