#pragma once

class Wall : public Pawn
{
public:
	Wall();
	~Wall();

	virtual void render(SDL_Renderer* _renderer);
	virtual void update(float /*_deltaTime*/ = 0) {};
	virtual void init();
	void collision(const Actor* /*_actor*/) {};
};