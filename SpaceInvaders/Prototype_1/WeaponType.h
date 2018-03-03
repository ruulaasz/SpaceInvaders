#pragma once

class WeaponType
{
public:
	WeaponType();
	WeaponType(const WeaponType &_type);
	virtual ~WeaponType();

	float m_rateOfFire;
	LCF::Texture* m_weaponTexture;
	LCF::Texture* m_weaponReadyTexture;
	LCF::Animator* m_shootAnimation;
	LCF::Sfx* m_shootSFX;
	std::string m_bulletType;
	int m_life;
	bool m_enemy;

	void init(std::string _info);
};