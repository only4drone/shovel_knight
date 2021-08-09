#include "pch.h"
#include "object.h"
#include "character.h"
#include "mapCamera.h"

object::object()
{
}

object::~object()
{
}


HRESULT object::init()
{
	//�ʿ��Ѱ�
	//1���� �����̴� ����(�¿�, ����), ��(ū, ��), ������(����), ������(���, ġŲ) - ü��ȸ��
	//2���� �����(���� ��°�, �ٴڿ��� �ö���� ��), ���̾(����, ��),
	//������� - ���ʿ� �ؿ��� ����ߴٰ� ���������� �����ϸ� �¿�� ���ݾ� �����̴�?






	platformSetting();
	sandBlockSetting();
	potionSetting();
	jewelSetting();
	bubbleSetting();
	fireBallSetting();

	return S_OK;
}

void object::release()
{
}

void object::update()
{

	gravity();
	collision();
	imgFrameSetting();
	objectMove();
}

void object::collision()
{

}

void object::gravity()
{
}

void object::imgSetting()
{
}

void object::imgFrameSetting()
{
}

void object::objectMove()
{

	//������ �Ұ��� ó�����ִ� for��
	for (int i = 0; i < PLATFORMMAX; i++)
	{
		if (_platform[i].index == 1)
		{
			if (_platform[i].min > _platform[i].x)
			{
				_platform[i].isDirection = true;
			}
			else if (_platform[i].max < _platform[i].x)
			{
				_platform[i].isDirection = false;
			}
		}

		if (_platform[i].index == 2)
		{
			if (_platform[i].min > _platform[i].y)
			{
				_platform[i].isDirection = true;
			}
			else if (_platform[i].max < _platform[i].y)
			{
				_platform[i].isDirection = false;
			}
		}


	}


	for (int i = 0; i < PLATFORMMAX; i++)
	{
		//�¿������ �������� ó�����ִ� if��
		if (_platform[i].index == 1)
		{
			if (_platform[i].isDirection == true)
			{
				_platform[i].x += _platform[i].speed;
			}
			else
			{
				_platform[i].x -= _platform[i].speed;
			}
		}

		//���Ϲ����� �������� ó�����ִ� if��
		if (_platform[i].index == 2)
		{
			if (_platform[i].isDirection == true)
			{
				_platform[i].y += _platform[i].speed;
			}
			else
			{
				_platform[i].y -= _platform[i].speed;
			}
		}
	}



}

void object::platformSetting()
{
	//������ x, y�� ���� - ��ǥ��

	//�¿�
	_platform[0].x = 100;
	_platform[0].y = 100;
	_platform[0].min = 50;     //��ġ ������ ���Ŀ� üũ�ϸ鼭
	_platform[0].max = 150;

	_platform[1].x = 200;
	_platform[1].y = 200;
	_platform[1].min = 50;
	_platform[1].max = 150;

	_platform[2].x = 300;
	_platform[2].y = 300;
	_platform[2].min = 50;
	_platform[2].max = 150;

	//����
	_platform[3].x = 100;
	_platform[3].y = 100;

	_platform[4].x = 100;
	_platform[4].y = 100;

	//�����̴� ���� �¿� 3�� - 0, 1, 2
	for (int i = 0; i < 3; i++)
	{
		_platform[i].isDirection = false;
		_platform[i].type = 1;
		_platform[i].index = 1;
		_platform[i].speed = SPEED;
		_platform[i].rc = RectMakeCenter(_platform[i].x, _platform[i].y, 100, 50);
		//_platform[i].objectImage = IMAGEMANAGER->addImage("���", "image/life.bmp", 50, 50, true, RGB(255, 0, 255));
	}

	//�����̴� ���� ���� 2�� - 3, 4
	for (int i = 3; i < 5; i++)
	{
		_platform[i].isDirection = false;
		_platform[i].type = 1;
		_platform[i].index = 2;
		_platform[i].speed = SPEED;
		_platform[i].rc = RectMakeCenter(_platform[i].x, _platform[i].y, 100, 50);
		//_platform[i].objectImage = IMAGEMANAGER->addImage("���", "image/life.bmp", 50, 50, true, RGB(255, 0, 255));
	}

}

void object::sandBlockSetting()
{
	//����ó�� ���� ����ϰ� ���� �ɰŰ���~

}

void object::potionSetting()
{
}

void object::jewelSetting()
{
}

void object::bubbleSetting()
{
}

void object::fireBallSetting()
{
}

void object::render()
{
}
