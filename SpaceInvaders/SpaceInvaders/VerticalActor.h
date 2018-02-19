#pragma once

struct VerticalStruct
{
	VerticalStruct(int _value) { value = _value; }
	int value;
};

class VerticalActor : public LCF::Actor
{
public:
	VerticalActor();
	~VerticalActor();

	LCF::Texture* m_texture;

	virtual void render(SDL_Renderer* _renderer);
	void move(VerticalStruct _info);
	void update(float _deltaTime);
	void Init();
	void Collision(const Actor* _actor);
};