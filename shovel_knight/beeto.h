#pragma once
#include "enemy.h"

class beeto : public enemy
{
public:
	beeto();
	~beeto();

	void move();		//���ʹ� Ŭ������ �ִ� ������ �Լ� �������̵�
	void enemyAI();
};

