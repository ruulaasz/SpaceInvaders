#pragma once

class EnemyType
{
public:
	EnemyType();
	EnemyType(const EnemyType &_type);
	virtual ~EnemyType();

	LCF::Sfx* m_moveSFX;
	LCF::Sfx* m_deadSFX;
	float m_movementSpeed;
	LCF::Animator* m_moveAnimation;
	LCF::Animator* m_deadAnimation;
	int m_life;
	int m_damage;
	std::string m_weapon;
	LCF::Sfx* m_damageSFX;
	LCF::Sfx* m_spawnSFX;

	void init(std::string _info);
};