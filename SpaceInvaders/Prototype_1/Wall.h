#pragma once

class Wall : public LCF::Actor
{
public:
	Wall();
	~Wall();

	virtual void render(SDL_Renderer* _renderer);
	virtual void update(float _deltaTime);
	virtual void init();
	void collision(const Actor* _actor);
};

