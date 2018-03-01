#pragma once

class EnemySpawner
{
public:
	EnemySpawner();
	~EnemySpawner();

	LCF::Factory<SkyEnemy, EnemyType> g_skyEnemyFactory;
	LCF::Factory<GroundEnemy, EnemyType> g_groundEnemyFactory;
	LCF::Factory <MainWeapon, WeaponType > g_mainWeaponfactory;
	LCF::Factory <SideWeapon, WeaponType > g_sideWeaponfactory;
	LCF::Factory <MainBullet, BulletType > g_mainBulletFactory;
	LCF::Factory <SubBullet, BulletType > g_subBulletFactory;

	void create(std::string _name, int _posX, int _posY);
	void init();
};