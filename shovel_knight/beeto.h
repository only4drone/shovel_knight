#pragma once
#include "enemy.h"

class beeto : public enemy
{
public:
	beeto();
	~beeto();


	//���ʹ� Ŭ������ �ִ�  �Լ� �������̵�
	
	virtual void move();
	virtual void die();
	virtual void enemyAI();
};

