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
	//2���� �����(���� ��°�, �ٴڿ��� �ö���� ��)
	//������� - ���ʿ� �ؿ��� ����ߴٰ� ���������� �����ϸ� �¿�� ���ݾ� �����̴�?






	//platformSetting();
	//sandBlockSetting();
	//potionSetting();
	//jewelSetting();
	//bubbleSetting();
	//fireBallSetting();
	//ladderSetting();

	return S_OK;
}

void object::release()
{
}

void object::update()
{
	platformSetting();
	ladderSetting();
	npcSetting();
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
	//_platform[0].x = 100;
	//_platform[0].y = 100;
	//_platform[0].min = 50;     //��ġ ������ ���Ŀ� üũ�ϸ鼭
	//_platform[0].max = 150;
	//
	//_platform[1].x = 200;
	//_platform[1].y = 200;
	//_platform[1].min = 50;
	//_platform[1].max = 150;
	//
	//_platform[2].x = 300;
	//_platform[2].y = 300;
	//_platform[2].min = 50;
	//_platform[2].max = 150;
	//
	////����
	//_platform[3].x = 100;
	//_platform[3].y = 100;
	//
	//_platform[4].x = 100;
	//_platform[4].y = 100;

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
	
	for (int i = 0; i < SANDBLOCKMAX; i++) //
	{
		_sandBlock[i].type = 1;
		_sandBlock[i].index = 10;
		_sandBlock[i].rc = RectMakeCenter(_sandBlock[i].x, _sandBlock[i].y, 100, 100);

	}

	// ū ������� �� ��ǥ

	
	// ���� ������� �� ��ǥ

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

void object::ladderSetting()
{
	for (int i = 0; i < LADDERMAX; i++) //11��
	{

		_ladder[i].type = 1;
		_ladder[i].index = 21;

		// �������� 50,0 �� �ȰŴ�
		_mapCamera->MakeObject(_ladder[i].rc, _ladder[i].x, _ladder[i].y, 50, _ladder[i].height);

		
		//_ladder[i].x + _mapCamera->getCamX(), _ladder[i].y + _mapCamera->getCamY(), 50, 250
		// void MakeObject(RECT& rect, int left, int right, int top, int bottom); �����ؿ°�
		//                (������ ��Ʈ,    ����,     ����,     ����,    ����   )
	}


	// 0,-2200�� �׻� �����شٰ� �����ϰ� ��ǥ�� �����϶�
	// ��ٸ��� �� ��ǥ

	//camy - 2200 -> ��ġ ����
	_ladder[0].x = 8450;
	_ladder[0].y = 2000;
	_ladder[0].height = 500;


	//camy - 1495 -> ��ġ ����
	_ladder[1].x = 7625;
	_ladder[1].y = 1400;
	_ladder[1].height = 700;
	
	_ladder[2].x = 8100;
	_ladder[2].y = 2600;
	_ladder[2].height = 600;

	//_ladder[3].x = 100;
	//_ladder[3].y = 100;
	//
	//_ladder[4].x = 100;
	//_ladder[4].y = 100;
	//
	//_ladder[5].x = 100;
	//_ladder[5].y = 100;
	//
	//_ladder[6].x = 100;
	//_ladder[6].y = 100;
	//
	//_ladder[7].x = 100;
	//_ladder[7].y = 100;
	//
	//_ladder[8].x = 100;
	//_ladder[8].y = 100;
	//
	//_ladder[9].x = 100;
	//_ladder[9].y = 100;
	//
	//_ladder[10].x = 100;
	//_ladder[10].y = 100;
	//
	//_ladder[11].x = 100;
	//_ladder[11].y = 100;

	


	
}

void object::npcSetting()
{
	for (int i = 0; i < NPCMAX; i++)
	{
		_npc[i].type = 4;
		_mapCamera->MakeObject(_npc[i].rc, _npc[i].x, _npc[i].y, _npc[i].width, _npc[i].height);
	}

	_npc[0].x = 310;
	_npc[0].y = 2470;
	_npc[0].width = 120;
	_npc[0].height = 150;

	_npc[1].x = 950;
	_npc[1].y = 2470;
	_npc[1].width = 120;
	_npc[1].height = 150;

	_npc[2].x = 430;
	_npc[2].y = 2690;
	_npc[2].width = 120;
	_npc[2].height = 150;
}

void object::render()
{
	char str[128];

	sprintf_s(str, "ladder.x : %d", _ladder[0].rc.left);
	TextOut(getMemDC(), 10, 120, str, strlen(str));

	sprintf_s(str, "ladder.y : %d", _ladder[0].rc.top);
	TextOut(getMemDC(), 10, 140, str, strlen(str));



	if (KEYMANAGER->isToggleKey(VK_TAB))
	{


		for (int i = 0; i < LADDERMAX; i++) // ��ٸ� 11��
		{
			Rectangle(getMemDC(), _ladder[i].rc);
			
		}

		for (int i = 0; i < PLATFORMMAX; i++) // �����̴� ���� 5��
		{
			Rectangle(getMemDC(), _platform[i].rc);
		}

		for (int i = 0; i < SANDBLOCKMAX; i++) // �����
		{
			Rectangle(getMemDC(), _sandBlock[i].rc);
		}

		for (int i = 0; i < NPCMAX; i++) // npc
		{
			Rectangle(getMemDC(), _npc[i].rc);
		}
	}	
}
