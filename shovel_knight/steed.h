#pragma once
#include "enemy.h"

class steed : public enemy
{
public:
	steed();
	~steed();

	//���ʹ� Ŭ������ �ִ�  �Լ� �������̵�
	virtual void move();
	virtual void die();
	virtual void enemyAI();
};

