#pragma once
#include "enemy.h"

class bugDragon : public enemy
{
public:
	bugDragon();
	~bugDragon();

	//���ʹ� Ŭ������ �ִ�  �Լ� �������̵�
	
	

	virtual void move();
	virtual void attack();
	virtual void enemyAI();
};


