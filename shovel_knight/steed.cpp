#include "pch.h"
#include "steed.h"

steed::steed()
{
}

steed::~steed()
{
}

void steed::move()
{
	if (_enemyDirection == E_LEFT)
	{
		_x -= 6;
	}
	if (_enemyDirection == E_RIGHT)
	{
		_x += 6;
	}
}

void steed::die()
{
}

void steed::enemyAI()
{
	//if (�÷��̾�� ������Ʈ �浹��)	_enemyState = E_MOVE;
	if (_hitCount == 1) _enemyState = E_DIE;
}
