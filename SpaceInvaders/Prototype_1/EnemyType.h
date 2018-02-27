#pragma once

class EnemyType
{
public:
	EnemyType();
	virtual ~EnemyType();

	LCF::Sfx* m_moveSFX;
	LCF::Sfx* m_deadSFX;
	float m_movementSpeed;
	LCF::Animator* m_moveAnimation;
	LCF::Animator* m_deadAnimation;
	int m_life;
	int m_damage;

	void init(std::string _info);

	Weapon* m_weapon;
};