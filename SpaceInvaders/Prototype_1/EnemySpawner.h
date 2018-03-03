#pragma once

class EnemySpawner : public Spawner
{
public:
	EnemySpawner();
	~EnemySpawner();

	virtual void create(int _unitType, float _posX, float _posY, int _direction = DIRECTION_STOP);
	virtual void init();
};