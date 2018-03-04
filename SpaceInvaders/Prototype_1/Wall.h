#pragma once

class Wall : public Pawn
{
public:
	Wall();
	~Wall();

	virtual void render(bool _flip = false) {};
	virtual void update(float /*_deltaTime*/) {};
	virtual void init();
	void collision(const Actor* /*_actor*/) {};
};