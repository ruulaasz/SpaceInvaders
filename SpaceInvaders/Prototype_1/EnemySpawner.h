#pragma once

class EnemySpawner : public Spawner
{
public:
	EnemySpawner();
	~EnemySpawner();

	virtual void create(int _unitType, float _posX, float _posY);
	virtual void init();
};