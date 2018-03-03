#pragma once

class Spawner
{
public:
	Spawner();
	virtual ~Spawner();

	LCF::Factory<SkyEnemy, EnemyType> m_skyEnemyFactory;
	LCF::Factory<GroundEnemy, EnemyType> m_groundEnemyFactory;
	LCF::Factory <MainWeapon, WeaponType> m_mainWeaponfactory;
	LCF::Factory <SideWeapon, WeaponType> m_sideWeaponfactory;
	LCF::Factory <MainBullet, BulletType> m_mainBulletFactory;
	LCF::Factory <SubBullet, BulletType> m_subBulletFactory;

	virtual void create(int _unitType, float _posX, float _posY, int _direction) = 0;
	virtual void init() = 0;
};