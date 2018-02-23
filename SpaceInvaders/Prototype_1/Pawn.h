#pragma once

typedef LCF::ColliderBox<LCF::Actor> ActorBox;

class Pawn : public LCF::Actor
{
public:
	Pawn();
	~Pawn();

	virtual void init();

	virtual void destroy();

	ActorBox* m_colliderBox;
	bool m_enabled;

	bool getEnabled() { return m_enabled; }
	void setEnabled(bool _enabled) { m_enabled = _enabled; };
};