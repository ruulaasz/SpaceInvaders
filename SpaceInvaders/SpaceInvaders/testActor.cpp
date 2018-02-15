#include "stdafx.h"

testActor::testActor()
{

}

testActor::~testActor()
{

}

void testActor::render(SDL_Renderer * _renderer)
{
	m_texture->render(m_posX, m_posY, _renderer);
}

void testActor::move(testStruct _info)
{
	m_posX += _info.value;
}
