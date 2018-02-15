#pragma once
struct testStruct
{

	testStruct(int _value) { value = _value; }
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

