#include "pch.h"
#include "bugDragon.h"

bugDragon::bugDragon()
{
}

bugDragon::~bugDragon()
{
}

void bugDragon::move()
{
	_moveCount++;

	//�ð��� ���� bugDragon ������ ��ȭ
	if (_moveCount <= 200)	//��
	{
		_enemyDirection = E_LEFT;
		_x -= 1;
	}
	if (_moveCount > 200  && _moveCount <= 400)	//��
	{
		_enemyDirection = E_RIGHT;
		_x += 1;
	}
	if (_moveCount > 400 )
	{
		_moveCount = 0;
	}
}

void bugDragon::attack()
{
}

void bugDragon::enemyAI()
{
	enemy::enemyAI();

	RECT temp;
	
	if (_hitCount < 12)
	{
		if (IntersectRect(&temp, &_characterRC, &_proveRC))
		{
			_attackCount++;

			if (_attackCount <= 200)
			{
				_enemyState = E_MOVE;
			}
			if (_attackCount > 200 && _attackCount <= 250)
			{
				_enemyState = E_ATTACK;
			}
			if (_attackCount == 250)
			{
				_attackCount = 0;
			}
		}
	}

	if (_hitCount == 12)
	{
		_enemyState = E_DIE;
	}
}