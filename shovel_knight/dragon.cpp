#include "pch.h"
#include "dragon.h"

dragon::dragon()
{
}

dragon::~dragon()
{
}

void dragon::move()
{
	_moveCount++;

	//�ð��� ���� dragon ������ ��ȭ
	if (_randCount < _moveCount && _moveCount <= 200 + _randCount)	//��
	{
		_enemyDirection = E_LEFT;
		_x -= 1;
	}
	if (_moveCount > 200 + _randCount && _moveCount <= 400 + _randCount)	//��
	{
		_enemyDirection = E_RIGHT;
		_x += 1;
	}
	if (_moveCount > 400 + _randCount)
	{
		_moveCount = _randCount;
	}
}

void dragon::attack()
{
}

void dragon::enemyAI()
{
	RECT temp;
	if (IntersectRect(&temp, &_characterRC, &_proveRC))
	{
		_attackCount++;

		if (_attackCount < 100)
		{
			_enemyState = E_MOVE;
		}
	}
}
