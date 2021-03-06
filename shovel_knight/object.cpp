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


void object::setSandBlock(int arrNum, bool isAlive) // 괄호안의 있는것들은 매개변수
{
	//샌드블록[arrNum-배열의 숫자].isAlive = 상단의 매개변수값으로 넣어준다.
	_sandBlock[arrNum].isAlive = isAlive;
}

void object::setBubble(int arrNum, bool isAlive)
{
	_bubble[arrNum].isAlive = isAlive;
}

void object::setJewel(int arrNum, bool isAlive)
{
	_jewel[arrNum].isAlive = isAlive;
}

void object::setFood(int arrNum, bool isAlive)
{
	_food[arrNum].isAlive = isAlive;
}

HRESULT object::init()
{
	//필요한것
	//1순위 움직이는 발판(좌우, 상하), 흙(큰, 작), 보석류(광석), 먹을것(사과, 치킨) - 체력회복
	//2순위 물방울(용이 쏘는것, 바닥에서 올라오는 것)
	//물방울은 - 최초에 밑에서 상승했다가 일정범위에 도달하면 좌우로 조금씩 움직이는?

	

	//_mapCamera->init();

	IMAGEMANAGER->addImage("플랫폼", "image/object/obj_platform.bmp", 190, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("큰흙더미", "image/object/obj_sandblock.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("물방울", "image/object/obj_bubble2.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보석", "image/object/obj_jewel2.bmp", 80, 61, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("동전", "image/object/obj_coin.bmp", 50, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("치느님", "image/object/obj_chicken2.bmp", 90, 60, true, RGB(255, 0, 255));

	platformSetting();
	potionSetting();
	jewelSetting();
	bubbleSetting();
	fireBallSetting();
	ladderSetting();
	npcSetting();
	sandBlockSetting();
	imgFrameSetting();
	foodSetting();

	


	
	return S_OK;
}

void object::release()
{
}

void object::update()
{
	objectMakeRect();

	gravity();
	collision();

	imgFrameSetting();

	objectMove();
	objectDeath();
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

	////발판의 불값을 처리해주는 for문
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

	for (int i = 0; i < 4; i++)
	{
		if (_bubble[i].topMax >= _bubble[i].y) 
		{
				_bubble[i].speed = 1;
				_bubble[i].y = _bubble[i].topMax;

				//버블의 좌우 움직임 불값 전환을 위한 문구
				if (_bubble[i].min > _bubble[i].x)
				{
					_bubble[i].isDirection = true;
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
		else
		{
			_bubble[i].speed = 2;
			_bubble[i].y -= _bubble[i].speed;
		}
		
	

		if (!_bubble[i].isAlive) // 버블이 터졌을때 초기값을 불러와야 함
		{
			_bubble[i].x = _bubble[i].startX;
			_bubble[i].y = _bubble[i].startY;
			_bubble[i].speed = 2;
			_bubble[i].isAlive = true;
		}
	}

	for (int i = 0; i < BUBBLEMAX; i++)
	{
		_bubble[i].min = _bubble[i].startX - 5;
		_bubble[i].max = _bubble[i].startX + 5;
	}

}

void object::platformSetting()
{
	//발판의 x, y값 설정 - 좌표값

	//-7650, -1470
	_platform[0].x = 8050;
	_platform[0].y = 1750;
	_platform[0].min = _platform[0].x - 200;
	_platform[0].max = _platform[0].x + 200;
	
	//-8800, -1470
	_platform[1].x = 9400;
	_platform[1].y = 2050;
	_platform[1].min = _platform[1].x - 200;
	_platform[1].max = _platform[1].x + 200;
	//
	// 13920, 2920 
	_platform[2].x = 14550;
	_platform[2].y = 3300;
	_platform[2].min = _platform[2].x - 200;
	_platform[2].max = _platform[2].x + 200;
	//
	////상하
	// 13920, 2920 
	_platform[3].x = 14050;
	_platform[3].y = 3350;
	_platform[3].min = _platform[3].y - 80;
	_platform[3].max = _platform[3].y + 80;
	
	// 16480, 1460 
	_platform[4].x = 17060;
	_platform[4].y = 1870;
	_platform[4].min = _platform[4].y - 200;
	_platform[4].max = _platform[4].y + 200;
	

	
		

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
		
	}

	//움직이는 발판 상하 2개 - 3, 4
	for (int i = 3; i < 5; i++)
	{
		_platform[i].isDirection = false;
		_platform[i].type = 1;
		_platform[i].index = 2;
		_platform[i].speed = SPEED;
		_mapCamera->MakeObject(_platform[i].rc, _platform[i].x, _platform[i].y, 190, 50);
		
	}

}

void object::sandBlockSetting()
{
	//발판처럼 느낌 비슷하게 가면 될거같다~
	

	// 큰 흙더미의 각 좌표

	// 초입부 3단 흙더미
	_sandBlock[0].x = 6200;
	_sandBlock[0].y = 2380;

	_sandBlock[1].x = 6200;
	_sandBlock[1].y = 2480;

	_sandBlock[2].x = 6200;
	_sandBlock[2].y = 2580;

	//사다리2개 맵 1층 흙더미 10080, 2930
	_sandBlock[3].x = 10500;
	_sandBlock[3].y = 3400;

	_sandBlock[4].x = 10600;
	_sandBlock[4].y = 3450;

	_sandBlock[5].x = 10700;
	_sandBlock[5].y = 3400;

	_sandBlock[6].x = 10800;
	_sandBlock[6].y = 3450;

	_sandBlock[7].x = 10900;
	_sandBlock[7].y = 3400;

	//사다리2개 맵 3층 흙더미 10080, 2930
	_sandBlock[8].x = 10700;
	_sandBlock[8].y = 3040;

	_sandBlock[9].x = 10800;
	_sandBlock[9].y = 2990;
	
	_sandBlock[10].x = 10900;
	_sandBlock[10].y = 3040;
	
	_sandBlock[11].x = 11000;
	_sandBlock[11].y = 2990;
	
	_sandBlock[12].x = 11100;
	_sandBlock[12].y = 3040;

	// 넓은 평지 - 졸라많이 뿌려야된다 이힣 신난다 12640, 3660
	//1층
	_sandBlock[14].x = 12880;
	_sandBlock[14].y = 4120;

	//_sandBlock[15].x = 12980;
	//_sandBlock[15].y = 4120;

	_sandBlock[16].x = 13080;
	_sandBlock[16].y = 4120;

	_sandBlock[17].x = 13180;
	_sandBlock[17].y = 4120;

	_sandBlock[18].x = 13280;
	_sandBlock[18].y = 4120;

	_sandBlock[19].x = 13380;
	_sandBlock[19].y = 4120;

	_sandBlock[20].x = 13480;
	_sandBlock[20].y = 4120;

	_sandBlock[21].x = 13580;
	_sandBlock[21].y = 4120;

	//2층

	_sandBlock[22].x = 12980;
	_sandBlock[22].y = 4020;

	//_sandBlock[23].x = 13080;
	//_sandBlock[23].y = 4020;

	_sandBlock[24].x = 13180;
	_sandBlock[24].y = 4020;

	_sandBlock[25].x = 13280;
	_sandBlock[25].y = 4020;

	//_sandBlock[26].x = 13380;
	//_sandBlock[26].y = 4020;

	_sandBlock[27].x = 13480;
	_sandBlock[27].y = 4020;

	//3층
	_sandBlock[28].x = 13080;
	_sandBlock[28].y = 3920;

	_sandBlock[29].x = 13180;
	_sandBlock[29].y = 3920;

	_sandBlock[30].x = 13280;
	_sandBlock[30].y = 3920;

	//용앞 17760, 1470
	_sandBlock[31].x = 17905;
	_sandBlock[31].y = 1750;

	_sandBlock[32].x = 18007;
	_sandBlock[32].y = 1750;

	//흙더미 대량생산 19040, 720

	//3층
	_sandBlock[33].x = 19755;
	_sandBlock[33].y = 990;

	_sandBlock[34].x = 19855;
	_sandBlock[34].y = 990;

	_sandBlock[35].x = 19955;
	_sandBlock[35].y = 990;

	//2층
	_sandBlock[36].x = 19755;
	_sandBlock[36].y = 1090;
	
	_sandBlock[37].x = 19855;
	_sandBlock[37].y = 1090;
	
	_sandBlock[38].x = 19955;
	_sandBlock[38].y = 1090;
	
	//1층
	_sandBlock[39].x = 19755;
	_sandBlock[39].y = 1190;
	
	_sandBlock[40].x = 19855;
	_sandBlock[40].y = 1190;
	
	_sandBlock[41].x = 19955;
	_sandBlock[41].y = 1190;

	// 작은 흙더미의 각 좌표

	for (int i = 0; i < SANDBLOCKMAX; i++) //
	{
		_sandBlock[i].isAlive = true;
		_sandBlock[i].type = 1;
		_sandBlock[i].index = 10;
		_mapCamera->MakeObject(_sandBlock[i].rc, _sandBlock[i].x, _sandBlock[i].y, 100, 100);
		//_sandBlock[i].rc = RectMakeCenter(_sandBlock[i].x, _sandBlock[i].y, 100, 100);
	}


}

void object::potionSetting()
{
}

void object::jewelSetting()
{
	_jewel[0].x = 1500;
	_jewel[0].y = 2400;
	_jewel[0].index = 12;

	_jewel[1].x = 2000;
	_jewel[1].y = 2700;
	_jewel[1].index = 13;

	_jewel[2].x = 2200;
	_jewel[2].y = 2700;
	_jewel[2].index = 13;

	_jewel[3].x = 3100;
	_jewel[3].y = 2600;
	_jewel[3].index = 13;

	_jewel[4].x = 3200;
	_jewel[4].y = 2600;
	_jewel[4].index = 13;

	_jewel[5].x = 3325;
	_jewel[5].y = 2400;
	_jewel[5].index = 12;

	_jewel[6].x = 3500;
	_jewel[6].y = 2600;
	_jewel[6].index = 13;

	_jewel[7].x = 3600;
	_jewel[7].y = 2600;
	_jewel[7].index = 13;

	//첫 방울 위
	_jewel[8].x = 8100;
	_jewel[8].y = 2400;
	_jewel[8].index = 12;

	_jewel[9].x = 10700;
	_jewel[9].y = 3200;
	_jewel[9].index = 12;

	_jewel[10].x = 10800;
	_jewel[10].y = 3200;
	_jewel[10].index = 12;

	_jewel[11].x = 10900;
	_jewel[11].y = 3200;
	_jewel[11].index = 12;

	//8800, 3670 좌측 방
	_jewel[12].x = 9000;
	_jewel[12].y = 4100;
	_jewel[12].index = 12;

	_jewel[13].x = 9300;
	_jewel[13].y = 4100;
	_jewel[13].index = 12;

	_jewel[14].x = 8900;
	_jewel[14].y = 4150;
	_jewel[14].index = 13;

	_jewel[15].x = 8900;
	_jewel[15].y = 4050;
	_jewel[15].index = 13;

	_jewel[16].x = 8900;
	_jewel[16].y = 3950;
	_jewel[16].index = 13;

	//흙더미 많은 곳

	_jewel[17].x = 12990;
	_jewel[17].y = 4120;
	_jewel[17].index = 12;

	_jewel[18].x = 13090;
	_jewel[18].y = 4020;
	_jewel[18].index = 12;

	for (int i = 0; i < JEWELMAX; i++) //
	{

		_jewel[i].type = 2;
		_jewel[i].isAlive = true;
		if (_jewel[i].index == 12) // 빨간 다이아
		{
			_mapCamera->MakeObject(_jewel[i].rc, _jewel[i].x, _jewel[i].y, 80, 61);
		}

		if (_jewel[i].index == 13) // 동전
		{
			_mapCamera->MakeObject(_jewel[i].rc, _jewel[i].x, _jewel[i].y, 50, 38);
		}
		// void MakeObject(RECT& rect, int left, int right, int top, int bottom); 복붙해온거
		//                (생성할 렉트,    중점,     중점,     가로,    세로   )
	}


}

void object::bubbleSetting()
{
	//버블의 시작 좌표값

	//_bubble[0].startX; //시작좌표 X
	//_bubble[0].startY; //시작좌표 Y
	//_bubble[0].topMax; //최대상승 높이

	//7500, 2200
	_bubble[0].startX = 8100;
	_bubble[0].startY = 2900;
	_bubble[0].topMax = _bubble[0].startY - 300;;

	//13920, 3670
	_bubble[1].startX = 14450;
	_bubble[1].startY = 4200;
	_bubble[1].topMax = _bubble[1].startY - 100;

	//19040, 1420
	
	_bubble[2].startX = 19900;
	_bubble[2].startY = 2200;
	_bubble[2].topMax = _bubble[2].startY - 200;

	_bubble[3].startX = 20100;
	_bubble[3].startY = 2200;
	_bubble[3].topMax = _bubble[3].startY - 200;
	

	for (int i = 0; i < BUBBLEMAX; i++) //11개
	{
		_bubble[i].isAlive = true;
		_bubble[i].type = 3;
		_bubble[i].index = 1;
		_bubble[i].speed = 2; // 테스트 해보면서 수정
		_mapCamera->MakeObject(_bubble[i].rc, _bubble[i].startX, _bubble[i].startY, 100, 100);
		_bubble[i].x = _bubble[i].startX;
		_bubble[i].y = _bubble[i].startY;
	}

	
}

void object::fireBallSetting()
{

}

void object::ladderSetting()
{
	// 0,-2200을 항상 더해준다고 생각하고 좌표를 설정하라
	// 사다리의 각 좌표

	//camy - 2200 -> 위치 도달
	_ladder[0].x = 8450;
	_ladder[0].y = 2000;
	_ladder[0].height = 600;


	//camy - 1495 -> 위치 도달
	_ladder[1].x = 7625;
	_ladder[1].y = 1400;
	_ladder[1].height = 700;

	//10080, 1475 큰용 옆
	_ladder[2].x = 11160;
	_ladder[2].y = 2000;
	_ladder[2].height = 400;

	//10080, 2200
	_ladder[3].x = 10345;
	_ladder[3].y = 2800;
	_ladder[3].height = 300;

	//10080, 2925 사다리 2개맵 아래사다리
	_ladder[4].x = 11010;
	_ladder[4].y = 3350;
	_ladder[4].height = 230;

	//10080, 2925 사다리 2개맵 윗사다리
	_ladder[5].x = 10600;
	_ladder[5].y = 3100;
	_ladder[5].height = 230;
	
	//13960, 3670
	_ladder[6].x = 15045;
	_ladder[6].y = 3500;
	_ladder[6].height = 600;

	//13920, 2920 
	_ladder[7].x = 13910;
	_ladder[7].y = 2740;
	_ladder[7].height = 560;
	
	//13920, 2190
	_ladder[8].x = 14225;
	_ladder[8].y = 2050;
	_ladder[8].height = 350;
	
	//19040, 1470
	_ladder[9].x = 20210;
	_ladder[9].y = 900;
	_ladder[9].height = 1000;
	
	//19040, 710 마지막 사다리
	_ladder[10].x = 19440;
	_ladder[10].y = 350;
	_ladder[10].height = 700;
	

	


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


	


	
}

void object::npcSetting()
{
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

	for (int i = 0; i < NPCMAX; i++)
	{
		_npc[i].type = 4;
		_mapCamera->MakeObject(_npc[i].rc, _npc[i].x, _npc[i].y, _npc[i].width, _npc[i].height);
	}

	
}

void object::foodSetting()
{
	_food[0].x =  13390;
	_food[0].y =  4060;

	_food[1].x = 19630;
	_food[1].y = 1000;

	for (int i = 0; i < FOODMAX; i++) //
	{

		_food[i].type = 2;
		_food[i].index = 2;
		_food[i].isAlive = true;
		_mapCamera->MakeObject(_food[i].rc, _food[i].x, _food[i].y, 90, 60);
	}
}

void object::objectMakeRect()
{
	for (int i = 0; i < BUBBLEMAX; i++)
	{
		_mapCamera->MakeObject(_bubble[i].rc, _bubble[i].x, _bubble[i].y, 100, 100);
	}

	for (int i = 0; i < NPCMAX; i++)
	{
		_mapCamera->MakeObject(_npc[i].rc, _npc[i].x, _npc[i].y, _npc[i].width, _npc[i].height);
	}


	for (int i = 0; i < LADDERMAX; i++) //11개
	{
		// 기준점이 50,0 이 된거다
		_mapCamera->MakeObject(_ladder[i].rc, _ladder[i].x, _ladder[i].y, 50, _ladder[i].height);
	}

	for (int i = 0; i < SANDBLOCKMAX; i++) //
	{
		_mapCamera->MakeObject(_sandBlock[i].rc, _sandBlock[i].x, _sandBlock[i].y, 100, 100);
	}

	for (int i = 0; i < PLATFORMMAX; i++)
	{
		_mapCamera->MakeObject(_platform[i].rc, _platform[i].x, _platform[i].y, 190, 50);
	}

	for (int i = 0; i < JEWELMAX; i++)
	{
		_mapCamera->MakeObject(_jewel[i].rc, _jewel[i].x, _jewel[i].y, 80, 61);
	}

	for (int i = 0; i < FOODMAX; i++)
	{
		_mapCamera->MakeObject(_food[i].rc, _food[i].x, _food[i].y, 90, 60);
	}
}

void object::objectDeath()
{
	for (int i = 0; i < SANDBLOCKMAX; i++)
	{
		if (_sandBlock[i].isAlive == false)
		{
			_mapCamera->MakeObject(_sandBlock[i].rc, _sandBlock[i].x, _sandBlock[i].y, 0, 0);
		}
	}

	for (int i = 0; i < BUBBLEMAX; i++)
	{
		if (_bubble[i].isAlive == false)
		{
			_mapCamera->MakeObject(_bubble[i].rc, _bubble[i].x, _bubble[i].y, 0, 0);
		}
	}

	for (int i = 0; i < JEWELMAX; i++)
	{
		if (_jewel[i].isAlive == false)
		{

			_mapCamera->MakeObject(_jewel[i].rc, _jewel[i].x, _jewel[i].y, 0, 0);

		}
	}

	for (int i = 0; i < FOODMAX; i++)
	{
		if (_food[i].isAlive == false)
		{

			_mapCamera->MakeObject(_food[i].rc, _food[i].x, _food[i].y, 0, 0);

		}
	}
}



void object::render()
{
	char str[128];

	sprintf_s(str, "ladder.x : %d", _ladder[0].rc.left);
	TextOut(getMemDC(), 10, 120, str, strlen(str));

	sprintf_s(str, "ladder.y : %d", _ladder[0].rc.top);
	TextOut(getMemDC(), 10, 140, str, strlen(str));

	
	for (int i = 0; i < PLATFORMMAX; i++)
	{
		IMAGEMANAGER->findImage("플랫폼")->render(getMemDC(), _platform[i].rc.left, _platform[i].rc.top);
	}

	for (int i = 0; i < SANDBLOCKMAX; i++)
	{
		if (!_sandBlock[i].isAlive) continue;
		IMAGEMANAGER->findImage("큰흙더미")->render(getMemDC(), _sandBlock[i].rc.left, _sandBlock[i].rc.top);
	}

	for (int i = 0; i < BUBBLEMAX; i++)
	{
		if (!_bubble[i].isAlive) continue;
		IMAGEMANAGER->findImage("물방울")->render(getMemDC(), _bubble[i].rc.left, _bubble[i].rc.top);
	}


	for (int i = 0; i < JEWELMAX; i++)
	{
		if (!_jewel[i].isAlive) continue;
		if (_jewel[i].index == 12)
		{
			IMAGEMANAGER->findImage("보석")->render(getMemDC(), _jewel[i].rc.left, _jewel[i].rc.top);
		}
		if (_jewel[i].index == 13)
		{
			IMAGEMANAGER->findImage("동전")->render(getMemDC(), _jewel[i].rc.left, _jewel[i].rc.top);
		}
	}

	for (int i = 0; i < FOODMAX; i++)
	{
		if (!_food[i].isAlive) continue;
		IMAGEMANAGER->findImage("치느님")->render(getMemDC(), _food[i].rc.left, _food[i].rc.top);
	}

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

		for (int i = 0; i < BUBBLEMAX; i++) // 물방울
		{
			Rectangle(getMemDC(), _bubble[i].rc);
		}

		for (int i = 0; i < JEWELMAX; i++) // 물방울
		{
			Rectangle(getMemDC(), _jewel[i].rc);
		}

		for (int i = 0; i < FOODMAX; i++) // 물방울
		{
			Rectangle(getMemDC(), _food[i].rc);
		}
	}	
}
