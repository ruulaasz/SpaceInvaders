#pragma once

class BulletType
{
public:
	BulletType();
	BulletType(const BulletType &_type);
	virtual ~BulletType();

	float m_movementSpeed;
	unsigned int m_damage;
	LCF::Animator* m_travelAnimation;
	LCF::Animator* m_deadAnimation;
	bool m_enemy;

	void init(std::string _info);
};