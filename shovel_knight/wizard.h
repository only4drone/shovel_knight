#pragma once
#include "enemy.h"

class wizard : public enemy
{
public:
	wizard();
	~wizard();

	//���ʹ� Ŭ������ �ִ�  �Լ� �������̵�
	virtual void attack();
	virtual void die();
};

