#pragma once
class testActor: public Actor
{
public:
	testActor();
	~testActor();

	Texture* m_texture;

	virtual void render(SDL_Renderer* _renderer);
};

