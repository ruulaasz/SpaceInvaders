#pragma once

typedef LCF::ColliderBox<LCF::Actor> ActorBox;

class Pawn : public LCF::Actor
{
public:
	Pawn();
	~Pawn();

	ActorBox* m_colliderBox;

	virtual void init();
};