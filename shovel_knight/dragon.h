#pragma once
#include "enemy.h"

class dragon : public enemy
{
public:
	dragon();
	~dragon();

	//���ʹ� Ŭ������ �ִ�  �Լ� �������̵�
	virtual void move();
	virtual void attack();
	virtual void enemyAI();
};

