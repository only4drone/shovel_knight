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
	//필요한것
	//1순위 움직이는 발판(좌우, 상하), 흙(큰, 작), 보석류(광석), 먹을것(사과, 치킨) - 체력회복
	//2순위 물방울(용이 쏘는것, 바닥에서 올라오는 것)
	//물방울은 - 최초에 밑에서 상승했다가 일정범위에 도달하면 좌우로 조금씩 움직이는?






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

	//발판의 불값을 처리해주는 for문
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
		//좌우발판의 움직임을 처리해주는 if문
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

		//상하발판의 움직임을 처리해주는 if문
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

	//버블 움직임

	for (int i = 0; i < BUBBLEMAX; i++)
	{
		if (_bubble[i].topMax < _bubble[i].y)
		{
				_bubble[i].speed = 1;

				//버블의 좌우 움직임 불값 전환을 위한 문구
				if (_bubble[i].min > _bubble[i].x)
				{
					_platform[i].isDirection = true;
				}
				else if (_bubble[i].max < _bubble[i].x)
				{
					_bubble[i].isDirection = false;
				}

				// 버블의 디렉션이 트루값일때 문구
				if(_bubble[i].isDirection == true)
				{
					_bubble[i].x += _bubble[i].speed;
				}
				else
				{
					_bubble[i].x -= _bubble[i].speed;
				}
				
		}
		else 	_bubble[i].y -= _bubble[i].speed;

		if (!_bubble[i].isAlive) // 버블이 터졌을때 초기값을 불러와야 함
		{
			_bubble[i].x = _bubble[i].startX;
			_bubble[i].y = _bubble[i].startY;
			_bubble[i].topMax;
			_bubble[i].speed = 5;
			_bubble[i].isAlive = true;
		}
	}



}

void object::platformSetting()
{
	//발판의 x, y값 설정 - 좌표값

	//-7650, -1470
	_platform[0].x = 8050;
	_platform[0].y = 1750;
	_platform[0].min = 50;     //수치 수정은 추후에 체크하면서
	_platform[0].max = 150;
	
	//-8800, -1470
	_platform[1].x = 200;
	_platform[1].y = 200;
	_platform[1].min = 50;
	_platform[1].max = 150;
	//
	//_platform[2].x = 300;
	//_platform[2].y = 300;
	//_platform[2].min = 50;
	//_platform[2].max = 150;
	//
	////상하
	//_platform[3].x = 100;
	//_platform[3].y = 100;
	//
	//_platform[4].x = 100;
	//_platform[4].y = 100;

	//움직이는 발판 좌우 3개 - 0, 1, 2

	// void MakeObject(RECT& rect, int left, int right, int top, int bottom);
		//             (생성할 렉트,    중점,     중점,     가로,    세로   )

	for (int i = 0; i < 3; i++)
	{
		_platform[i].isDirection = false;
		_platform[i].type = 1;
		_platform[i].index = 1;
		_platform[i].speed = SPEED;
		_mapCamera->MakeObject(_platform[i].rc, _platform[i].x, _platform[i].y, 190, 50);
		//_platform[i].rc = RectMakeCenter(_platform[i].x, _platform[i].y, 100, 50);
		//_platform[i].objectImage = IMAGEMANAGER->addImage("목숨", "image/life.bmp", 50, 50, true, RGB(255, 0, 255));
	}

	//움직이는 발판 상하 2개 - 3, 4
	for (int i = 3; i < 5; i++)
	{
		_platform[i].isDirection = false;
		_platform[i].type = 1;
		_platform[i].index = 2;
		_platform[i].speed = SPEED;
		_mapCamera->MakeObject(_platform[i].rc, _platform[i].x, _platform[i].y, 190, 50);
		//_platform[i].rc = RectMakeCenter(_platform[i].x, _platform[i].y, 100, 50);
		//_platform[i].objectImage = IMAGEMANAGER->addImage("목숨", "image/life.bmp", 50, 50, true, RGB(255, 0, 255));
	}

}

void object::sandBlockSetting()
{
	//발판처럼 느낌 비슷하게 가면 될거같다~
	
	for (int i = 0; i < SANDBLOCKMAX; i++) //
	{
		_sandBlock[i].type = 1;
		_sandBlock[i].index = 10;
		_sandBlock[i].rc = RectMakeCenter(_sandBlock[i].x, _sandBlock[i].y, 100, 100);

	}

	// 큰 흙더미의 각 좌표

	
	// 작은 흙더미의 각 좌표

}

void object::potionSetting()
{
}

void object::jewelSetting()
{
}

void object::bubbleSetting()
{


	for (int i = 0; i < BUBBLEMAX; i++) //11개
	{
		_bubble[i].isAlive = true;
		_bubble[i].type = 3;
		_bubble[i].index = 1;
		_bubble[i].speed = 5; // 테스트 해보면서 수정
		_bubble[i].min = _bubble[i].startX - 5;
		_bubble[i].max = _bubble[i].startX + 5;
	}

	//버블의 시작 좌표값

	_bubble[0].startX;
	_bubble[0].startY;
	_bubble[0].topMax;


}

void object::fireBallSetting()
{

}

void object::ladderSetting()
{
	for (int i = 0; i < LADDERMAX; i++) //11개
	{

		_ladder[i].type = 1;
		_ladder[i].index = 21;

		// 기준점이 50,0 이 된거다
		_mapCamera->MakeObject(_ladder[i].rc, _ladder[i].x, _ladder[i].y, 50, _ladder[i].height);

		
		//_ladder[i].x + _mapCamera->getCamX(), _ladder[i].y + _mapCamera->getCamY(), 50, 250
		// void MakeObject(RECT& rect, int left, int right, int top, int bottom); 복붙해온거
		//                (생성할 렉트,    중점,     중점,     가로,    세로   )
	}


	// 0,-2200을 항상 더해준다고 생각하고 좌표를 설정하라
	// 사다리의 각 좌표

	//camy - 2200 -> 위치 도달
	_ladder[0].x = 8450;
	_ladder[0].y = 2000;
	_ladder[0].height = 500;


	//camy - 1495 -> 위치 도달
	_ladder[1].x = 7625;
	_ladder[1].y = 1400;
	_ladder[1].height = 700;
	
	//임시 사다리임 수정해야됨
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
	_npc[0].index = 1;

	_npc[1].x = 950;
	_npc[1].y = 2470;
	_npc[1].width = 120;
	_npc[1].height = 150;
	_npc[1].index = 2;

	_npc[2].x = 430;
	_npc[2].y = 2690;
	_npc[2].width = 120;
	_npc[2].height = 150;
	_npc[2].index = 3;
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


		for (int i = 0; i < LADDERMAX; i++) // 사다리 11개
		{
			Rectangle(getMemDC(), _ladder[i].rc);
			
		}

		for (int i = 0; i < PLATFORMMAX; i++) // 움직이는 발판 5개
		{
			Rectangle(getMemDC(), _platform[i].rc);
		}

		for (int i = 0; i < SANDBLOCKMAX; i++) // 흙더미
		{
			Rectangle(getMemDC(), _sandBlock[i].rc);
		}

		for (int i = 0; i < NPCMAX; i++) // npc
		{
			Rectangle(getMemDC(), _npc[i].rc);
		}
	}	
}
