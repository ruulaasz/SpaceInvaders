#include "stdafx.h"

EnemySpawner::EnemySpawner()
{

}

EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::create(int _unitType, float _posX, float _posY)
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
		
		route = route + "bullet\\main_enemy_bullet.txt";
		bullet = m_mainBulletFactory.create(route);

		route = route + "enemy\\skyenemy.txt";
		skyEnemy = m_skyEnemyFactory.create(route);
		skyEnemy->m_posX = _posX;
		skyEnemy->m_posY = _posY;

		route = route + "weapon\\main_enemy_weapon.txt";
		skyEnemy->m_weapon = m_mainWeaponfactory.create(route);
		skyEnemy->m_weapon->m_bulletType = bullet->m_type;

		skyEnemy->init();
		LCF::World::GetInstance().registerActor(skyEnemy);
		break;

	case GROUND_ENEMY_LEFT:

		route = route + "bullet\\sub_enemy_bullet.txt";
		sbullet = m_subBulletFactory.create(route);

		route = route + "enemy\\groundenemy.txt";
		groundEnemy = m_groundEnemyFactory.create(route);

		route = route + "weapon\\side_enemy_weapon.txt";
		groundEnemy->m_weapon = m_sideWeaponfactory.create(route);
		groundEnemy->m_weapon->m_bulletType = sbullet->m_type;

		groundEnemy->m_direction = DIRECTION_LEFT;
		groundEnemy->m_posX = _posX;
		groundEnemy->m_posY = _posY + groundEnemy->m_type->m_moveAnimation->m_frameHeight / 2;

		groundEnemy->init();
		LCF::World::GetInstance().registerActor(groundEnemy);
		break;

	case GROUND_ENEMY_RIGHT:

		route = route + "bullet\\sub_enemy_bullet.txt";
		sbullet = m_subBulletFactory.create(route);

		route = route + "enemy\\groundenemy.txt";
		groundEnemy = m_groundEnemyFactory.create(route);

		route = route + "weapon\\side_enemy_weapon.txt";
		groundEnemy->m_weapon = m_sideWeaponfactory.create(route);
		groundEnemy->m_weapon->m_bulletType = sbullet->m_type;

		groundEnemy->m_direction = DIRECTION_RIGHT;
		groundEnemy->init();
		groundEnemy->m_posX = _posX;
		groundEnemy->m_posY = _posY + groundEnemy->m_type->m_moveAnimation->m_frameHeight/2;
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