#include "stdafx.h"

EnemySpawner::EnemySpawner()
{

}

EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::create(std::string _name, int _posX, int _posY)
{
	
}

void EnemySpawner::init()
{
	std::string route;

	/*route = "..\\resources\\units\\";
	route = route + "enemy\\skyenemy.txt";
	SkyEnemy* enemy = g_skyEnemyFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "bullet\\main_enemy_bullet.txt";
	bullet = g_mainBulletFactory.create(route);



	route = "..\\resources\\units\\";
	route = route + "weapon\\main_enemy_weapon.txt";
	g_skyEnemy->m_weapon = g_mainWeaponfactory.create(route);
	g_skyEnemy->m_weapon->m_bulletType = bullet->m_type;

	g_skyEnemy->m_posX = 775;
	g_skyEnemy->m_posY = 100;
	g_skyEnemy->init();
	LCF::World::GetInstance().registerActor(g_skyEnemy);*/
}