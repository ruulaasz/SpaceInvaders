#pragma once

class WeaponType
{
public:
	WeaponType();
	virtual ~WeaponType();

	float m_rateOfFire;

	LCF::Texture* m_weaponTexture;
	LCF::Texture* m_weaponReadyTexture;
	LCF::Sfx* m_shootSFX;
	LCF::Animator* m_shootAnimation;
};