#pragma once
#include "enemy.h"

class bugDragon : public enemy
{
public:
	bugDragon();
	~bugDragon();

	//에너미 클래스에 있는  함수 오버라이딩
	
	

	virtual void move();
	virtual void attack();
	virtual void enemyAI();
};


