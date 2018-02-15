#pragma once
#include "SDL_Manager.h"

class Actor
{
public:
	Actor();
	virtual ~Actor();

	int m_id;
	int m_posX;
	int m_posY;

	virtual void render(SDL_Renderer* _renderer)=0;
};