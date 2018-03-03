#include "stdafx.h"

EnemySpawner::EnemySpawner()
{

}

EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::create(int _unitType, float _posX, float _posY, int _direction)
{
	std::string route = "..\\resources\\units\\";

	MainBullet* bullet = nullptr;
	SkyEnemy* skyEnemy = nullptr;
	SubBullet* sbullet = nullptr;
	GroundEnemy* groundEnemy = nullptr;

	switch (_unitType)
	{
	default:
		break;

	case SKY_ENEMY:
	
		route = route + "enemy\\skyenemy.txt";
		skyEnemy = m_skyEnemyFactory.create(route);
		skyEnemy->m_posX = _posX;
		skyEnemy->m_posY = _posY;

		route = route + "weapon\\";
		route = route + skyEnemy->m_type->m_weapon;
		route = route + ".txt";
		skyEnemy->m_weapon = m_mainWeaponfactory.create(route);

		route = route + "bullet\\";
		route = route + skyEnemy->m_weapon->m_weaponType->m_bulletType;
		route = route + ".txt";
		bullet = m_mainBulletFactory.create(route);
		skyEnemy->m_weapon->m_bulletType = bullet->m_type;

		skyEnemy->init();
		LCF::World::GetInstance().registerActor(skyEnemy);
		break;

	case GROUND_ENEMY:

		route = route + "enemy\\groundenemy.txt";
		groundEnemy = m_groundEnemyFactory.create(route);
		groundEnemy->m_direction = _direction;
		groundEnemy->m_posX = _posX;
		groundEnemy->m_posY = _posY;

		route = route + "weapon\\";
		route = route + groundEnemy->m_type->m_weapon;
		route = route + ".txt";
		groundEnemy->m_weapon = m_sideWeaponfactory.create(route);

		route = route + "bullet\\";
		route = route + groundEnemy->m_weapon->m_weaponType->m_bulletType;
		route = route + ".txt";
		sbullet = m_subBulletFactory.create(route);
		groundEnemy->m_weapon->m_bulletType = sbullet->m_type;

		groundEnemy->init();
		LCF::World::GetInstance().registerActor(groundEnemy);
		break;

	case GROUND_ENEMY_LARGE:

		route = route + "enemy\\groundenemy_large.txt";
		groundEnemy = m_groundEnemyFactory.create(route);
		groundEnemy->m_direction = _direction;
		groundEnemy->m_posX = _posX;
		groundEnemy->m_posY = _posY;

		route = route + "weapon\\";
		route = route + groundEnemy->m_type->m_weapon;
		route = route + ".txt";
		groundEnemy->m_weapon = m_sideWeaponfactory.create(route);

		route = route + "bullet\\";
		route = route + groundEnemy->m_weapon->m_weaponType->m_bulletType;
		route = route + ".txt";
		sbullet = m_subBulletFactory.create(route);
		groundEnemy->m_weapon->m_bulletType = sbullet->m_type;

		groundEnemy->init();
		LCF::World::GetInstance().registerActor(groundEnemy);
		break;
	}
}

void EnemySpawner::init()
{
	std::string route;

	//enemy
	route = "..\\resources\\units\\";
	route = route + "enemy\\skyenemy.txt";
	m_skyEnemyFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "enemy\\groundenemy.txt";
	m_groundEnemyFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "enemy\\groundenemy_large.txt";
	m_groundEnemyFactory.create(route);


	//bullet
	route = "..\\resources\\units\\";
	route = route + "bullet\\main_bullet.txt";
	m_mainBulletFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "bullet\\main_enemy_bullet.txt";
	m_mainBulletFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "bullet\\sub_bullet.txt";
	m_subBulletFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "bullet\\sub_enemy_bullet.txt";
	m_subBulletFactory.create(route);


	//weapon
	route = "..\\resources\\units\\";
	route = route + "weapon\\main_weapon.txt";
	m_mainWeaponfactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "weapon\\main_enemy_weapon.txt";
	m_mainWeaponfactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "weapon\\side_weapon.txt";
	m_sideWeaponfactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "weapon\\side_enemy_weapon.txt";
	m_sideWeaponfactory.create(route);
}