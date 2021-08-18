#include "pch.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char* imageName, POINT position, ENEMYDIRECTION enemyDirection)
{
	_enemyState = E_IDLE;
	_enemyDirection = enemyDirection;
	_currentFrameX = _currentFrameY = 0;
	_imageCount  = 0;
	
	_enemyName = imageName;
	_lazer = IMAGEMANAGER->findImage("lazer");
	_str = " and idle";
	_strSum = _enemyName + _str;

	_imageName = IMAGEMANAGER->findImage(_strSum);

	_x = position.x;
	_y = position.y;

	_randCount = RND->getFromIntTo(0, 200);
	_moveCount = 0;
	_attackCount = 0;
	_hitCount = 0;
	_smokeCount = 0;
	_dieCount = 0;
	_initCount = 0;

	_jumpPower = 5.0f;
	_gravity = 0.25f;

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
}


void enemy::update(int x, int y, float characterX, float characterY)
{
	enemyAI();
	enemyFrame();
	
	_characterX = characterX;
	_characterY = characterY;

	_characterRC = RectMakeCenter(characterX, characterY, 100, 100);

	if (_enemyName != "dragon" && _enemyName != "bugDragon")
	{
		_rc = RectMake(x + _x, 2200 + y + _y - _imageName->getFrameHeight(),
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
	}

	if (_enemyName == "steed")
	{
		_proveRC = RectMake(_rc.left - 100, _rc.top,
			_imageName->getFrameWidth() + 200, _imageName->getFrameHeight());
	}
	if (_enemyName == "dragon" || _enemyName == "bugDragon")
	{
		_rc = RectMake(x + _x + 100, 2200 + y + _y - 100,
			120, 90);
		
		_bodyRC = RectMake(x + _x + 220, 2200 + y + _y - _imageName->getFrameHeight() + 50,
			_imageName->getFrameWidth() -220, _imageName->getFrameHeight() - 50);

		_imageRC = RectMake(x + _x, 2200 + y + _y - _imageName->getFrameHeight(),
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
		
		_proveRC = RectMake(_imageRC.left - 300, _imageRC.top - 200,
			_imageName->getFrameWidth() + 600, _imageName->getFrameHeight() + 200);
		
		if (_enemyState == E_ATTACK)
		{
			_lazerRC = RectMake(_rc.left - _lazer->getFrameWidth(), _rc.top - 40, _lazer->getFrameWidth() - 30, _lazer->getFrameHeight());
		}
		else
		{
			_lazerRC = RectMake(_rc.left - _lazer->getFrameWidth(), _rc.top - 40, 0, 0);
		}
	}
}

void enemy::render()
{
	draw();

	//TAB키 눌렀을 때 적렉트 확인
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _proveRC);
		Rectangle(getMemDC(), _bodyRC);
		//Rectangle(getMemDC(), _characterRC);
		Rectangle(getMemDC(), _rc);
		Rectangle(getMemDC(), _lazerRC);
	}
}

void enemy::draw()
{
	if (_enemyName != "dragon" && _enemyName != "bugDragon")
	{
		_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	if ( _enemyName == "dragon" || _enemyName == "bugDragon")
	{
		
		
		_imageName->frameRender(getMemDC(), _imageRC.left, _imageRC.top, _currentFrameX, _currentFrameY);
		if (_enemyState == E_ATTACK)
		{
			_lazer->frameRender(getMemDC(), _rc.left - _lazer->getFrameWidth(), _rc.top - 40, _currentFrameX, _currentFrameY);
		}
	}
}

void enemy::enemyFrame()
{
	_imageCount++;

	//연기 상태일 때
	if (_enemyState == E_SMOKE)
	{
		_initCount++;
		if (_initCount == 1)
		{
			_currentFrameX = 0;
		}

		if (_imageCount % 4 == 0)
		{
			if (_currentFrameX >= _imageName->getMaxFrameX()) _isDelete = true;

			//_imageName->setFrameX(_currentFrameX);
			_currentFrameX++;
			_currentFrameY = 0;
		}
	}
	else
	{
		if (_imageCount % 10 == 0)
		{
			if (_enemyDirection == E_RIGHT)
			{
				if (_imageName->getMaxFrameX() > 2)
				{
					if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;

					//_imageName->setFrameX(_currentFrameX);
					_currentFrameX++;
					_currentFrameY = 0;
				}
				if (_imageName->getMaxFrameX() == 1)
				{
					//_imageName->setFrameX(_currentFrameX);
					_currentFrameY = 0;

					_currentFrameX == 0 ? _currentFrameX = 1 : _currentFrameX = 0;
				}
				if (_imageName->getMaxFrameX() == 0)
				{
					_currentFrameX = 0;
					_currentFrameY = 0;
				}
			}
			if (_enemyDirection == E_LEFT)
			{
				if (_imageName->getMaxFrameX() > 2)
				{
					if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();

					//_imageName->setFrameX(_currentFrameX);
					_currentFrameX--;

					if (_enemyName == "dragon" || _enemyName == "bugDragon")
					{
						_currentFrameY = 0;
					}
					else
					{
						_currentFrameY = 1;
					}
				}
				if (_imageName->getMaxFrameX() == 1)
				{
					//_imageName->setFrameX(_currentFrameX);
					_currentFrameY = 1;

					_currentFrameX == 0 ? _currentFrameX = 1 : _currentFrameX = 0;

				}
				if (_imageName->getMaxFrameX() == 0)
				{
					_currentFrameX = 0;
					if (_enemyName == "dragon" || _enemyName == "bugDragon")
					{
						_currentFrameY = 0;
					}
					else
					{
						_currentFrameY = 1;
					}
				}
			}
		}
	}

	switch (_enemyState)
	{
	case E_IDLE:
		_str = " and idle";
		_strSum = _enemyName + _str;
		_imageName = IMAGEMANAGER->findImage(_strSum);
		if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
		break;
	case E_MOVE:
		_str = " and move";
		_strSum = _enemyName + _str;
		_imageName = IMAGEMANAGER->findImage(_strSum);
		if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
		move();
		break;
	case E_ATTACK:
		_str = " and attack";
		_strSum = _enemyName + _str;
		_imageName = IMAGEMANAGER->findImage(_strSum);
		if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
		attack();
		break;
	case E_DIE:
		_str = " and die";
		_strSum = _enemyName + _str;
		_imageName = IMAGEMANAGER->findImage(_strSum);
		if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
		die();
		break;
	case E_SMOKE:
		_imageName = IMAGEMANAGER->findImage("smoke");
		
		break;
	}
}

void enemy::move()
{
}

void enemy::attack()
{
}

void enemy::die()
{
	if (_enemyName != "dragon" && _enemyName != "bugDragon")
	{
		if (_characterX > _rc.left)
		{
			_enemyDirection = E_RIGHT;
			_x -= 5;
			_y -= _jumpPower;
			_jumpPower -= _gravity;
		}

		if (_characterX < _rc.left)
		{
			_enemyDirection = E_LEFT;
			_x += 5;
			_y -= _jumpPower;
			_jumpPower -= _gravity;
		}
	}
	if (_enemyName == "dragon" || _enemyName == "bugDragon")
	{
		_dieCount++;

		if (_dieCount >= 100)	_isDelete = true;
	}
}

void enemy::enemyAI()
{
	if(_isDefense == false) _defenseCount = 0;

	if (_isDefense == true)
	{
		_defenseCount++;
		if (_defenseCount == 15)
		{
			_isDefense = false;
		}
	}
}