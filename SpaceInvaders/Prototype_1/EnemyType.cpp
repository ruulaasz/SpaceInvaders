#include "stdafx.h"

EnemyType::EnemyType()
{
	m_moveAnimation = new LCF::Animator();
	m_deadAnimation = new LCF::Animator();
}

EnemyType::~EnemyType()
{

}