#pragma once
struct testStruct
{
	int value;
};
class testActor: public Actor
{
public:
	testActor();
	~testActor();

	Texture* m_texture;

	virtual void render(SDL_Renderer* _renderer);

	void move(testStruct _info);
};

