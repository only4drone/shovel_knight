#include "pch.h"
#include "uiManager.h"
#include "character.h"

uiManager::uiManager()
{
}

uiManager::~uiManager()
{
}

HRESULT uiManager::init()
{

	IMAGEMANAGER->addImage("UIframe", "image/UI/UI_def.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp0", "image/UI/UI_hp0.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp1", "image/UI/UI_hp1.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp2", "image/UI/UI_hp2.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp3", "image/UI/UI_hp3.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp4", "image/UI/UI_hp4.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp5", "image/UI/UI_hp5.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp6", "image/UI/UI_hp6.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp7", "image/UI/UI_hp7.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp8", "image/UI/UI_hp8.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fireUI", "image/UI/UI_fire.bmp", 1280, 720, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("boss0", "image/UI/UI_boss0.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss1", "image/UI/UI_boss1.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss2", "image/UI/UI_boss2.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss3", "image/UI/UI_boss3.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss4", "image/UI/UI_boss4.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss5", "image/UI/UI_boss5.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss6", "image/UI/UI_boss6.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss7", "image/UI/UI_boss7.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss8", "image/UI/UI_boss8.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss9", "image/UI/UI_boss9.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss10", "image/UI/UI_boss10.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss11", "image/UI/UI_boss11.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss12", "image/UI/UI_boss12.bmp", 1280, 720, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("talkframe", "image/UI/UI_dial.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("t1", "image/UI/UI_dial_1.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("t2", "image/UI/UI_dial_2.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("t3", "image/UI/UI_dial_3.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("t4", "image/UI/UI_dial_4.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("t5", "image/UI/UI_dial_5.bmp", 1280, 720, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("goatshop1", "image/UI/goat_1.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("goatshop2", "image/UI/goat_2.bmp", 1280, 720, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("fireshop1", "image/UI/fire_1.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fireshop2", "image/UI/fire_2.bmp", 1280, 720, true, RGB(255, 0, 255));

	return S_OK;
}

void uiManager::release()
{

}

void uiManager::update()
{
	goatshop();

	fireshop();

	talklingMan();
	//게임 신에서 ui-> goatShopOn() 과 ui->goatShopoOff 로 상점 불러내기/없애기 관리해주세요.
}

void uiManager::render()
{
	IMAGEMANAGER->findImage("UIframe")->render(getMemDC());

	if (SCENEMANAGER->hp == 8) IMAGEMANAGER->findImage("hp8")->render(getMemDC());
	if (SCENEMANAGER->hp == 7) IMAGEMANAGER->findImage("hp7")->render(getMemDC());
	if (SCENEMANAGER->hp == 6) IMAGEMANAGER->findImage("hp6")->render(getMemDC());
	if (SCENEMANAGER->hp == 5) IMAGEMANAGER->findImage("hp5")->render(getMemDC());
	if (SCENEMANAGER->hp == 4) IMAGEMANAGER->findImage("hp4")->render(getMemDC());
	if (SCENEMANAGER->hp == 3) IMAGEMANAGER->findImage("hp3")->render(getMemDC());
	if (SCENEMANAGER->hp == 2) IMAGEMANAGER->findImage("hp2")->render(getMemDC());
	if (SCENEMANAGER->hp == 1) IMAGEMANAGER->findImage("hp1")->render(getMemDC());
	if (SCENEMANAGER->hp == 0) IMAGEMANAGER->findImage("hp0")->render(getMemDC());

	if (SCENEMANAGER->bossHp == 12) IMAGEMANAGER->findImage("boss12")->render(getMemDC());
	if (SCENEMANAGER->bossHp == 11) IMAGEMANAGER->findImage("boss11")->render(getMemDC());
	if (SCENEMANAGER->bossHp == 10) IMAGEMANAGER->findImage("boss10")->render(getMemDC());
	if (SCENEMANAGER->bossHp == 9) IMAGEMANAGER->findImage("boss9")->render(getMemDC());
	if (SCENEMANAGER->bossHp == 8) IMAGEMANAGER->findImage("boss8")->render(getMemDC());
	if (SCENEMANAGER->bossHp == 7) IMAGEMANAGER->findImage("boss7")->render(getMemDC());
	if (SCENEMANAGER->bossHp == 6) IMAGEMANAGER->findImage("boss6")->render(getMemDC());
	if (SCENEMANAGER->bossHp == 5) IMAGEMANAGER->findImage("boss5")->render(getMemDC());
	if (SCENEMANAGER->bossHp == 4) IMAGEMANAGER->findImage("boss4")->render(getMemDC());
	if (SCENEMANAGER->bossHp == 3) IMAGEMANAGER->findImage("boss3")->render(getMemDC());
	if (SCENEMANAGER->bossHp == 2) IMAGEMANAGER->findImage("boss2")->render(getMemDC());
	if (SCENEMANAGER->bossHp == 1) IMAGEMANAGER->findImage("boss1")->render(getMemDC());
	if (SCENEMANAGER->bossHp == 0) IMAGEMANAGER->findImage("boss0")->render(getMemDC());

	if(SCENEMANAGER->checkFire()) IMAGEMANAGER->findImage("fireUI")->render(getMemDC());

	if (goatShopOpen) {
		if (goatCnt == 1) IMAGEMANAGER->findImage("goatshop1")->render(getMemDC());
		if (goatCnt == 2) IMAGEMANAGER->findImage("goatshop2")->render(getMemDC());
	}

	if (fireShopOpen) {
		if (fireCnt == 1) IMAGEMANAGER->findImage("fireshop1")->render(getMemDC());
		if (fireCnt == 2) IMAGEMANAGER->findImage("fireshop2")->render(getMemDC());
	}
	

	///  말하는부분은 이미지로 처리해서 렌더에 처박음

	if (talkOpen) {
		IMAGEMANAGER->findImage("talkframe")->render(getMemDC());

		vibcnt++;
		if (vibcnt >= 7) {
			vibcnt = 0;
		}

		talkCnt++;
		if (talkCnt >= 5)
		{
			IMAGEMANAGER->findImage("t1")->render(getMemDC());
			if (talkCnt >= 30)
			{
				IMAGEMANAGER->findImage("t2")->render(getMemDC());
				if (talkCnt >= 110)
				{
					IMAGEMANAGER->findImage("t3")->render(getMemDC());
					if (talkCnt >= 240)
					{
						SOUNDMANAGER->pause("bgm");
						IMAGEMANAGER->findImage("t4")->render(getMemDC(),vibcnt, vibcnt/2);
						SOUNDMANAGER->play("laugh", 0.3f);
						if (talkCnt >= 360)
						{
							IMAGEMANAGER->findImage("t5")->render(getMemDC());
							if (talkCnt >= 500)
							{
								SOUNDMANAGER->resume("bgm");
								talkCnt = 0;
								talklingManOff();
							}
						}
					}

				}
			}
		}


	}




	char str[128];


	SetTextColor(getMemDC(), RGB(255, 255, 255));

	HFONT font2 = CreateFont(32, 0, 0, 0, 700, false, false, false,
		DEFAULT_CHARSET, OUT_STROKE_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));

	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);

	sprintf_s(str, "%d", SCENEMANAGER->getGold());
	TextOut(getMemDC(), 60, 26, str, strlen(str));

	SetTextColor(getMemDC(), RGB(0, 170, 255));

	sprintf_s(str, "%d", SCENEMANAGER->getMana());
	TextOut(getMemDC(), 305, 26, str, strlen(str));

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);





}



/// 아래부터 <불의 유물 상점과 고트(염소상점) 체력회복 상점 구동부>
///  상점 함수
/////게임 신에서 ui-> goatShopOn() 과 ui->goatShopoOff 같은 방법으로 상점 불러내기/없애기 관리해주세요.
void uiManager::goatshop()
{
	//염소상점 구동
	//
	if (goatShopOpen) {
		if (KEYMANAGER->isOnceKeyDown('S') && goatCnt < 2) {
			goatCnt += 1;
			SOUNDMANAGER->play("cursor", 1.0f);
		}
		if (KEYMANAGER->isOnceKeyDown('W') && goatCnt > 1) {
			goatCnt -= 1;
			SOUNDMANAGER->play("cursor",1.0f);
		}
	}
	if (goatShopOpen) {
		switch (goatCnt)
		{
		case 1:
			if (KEYMANAGER->isOnceKeyDown('J')) {
				if (SCENEMANAGER->getGold() >= 100) {
					SOUNDMANAGER->play("ok", 1.0f);
					SCENEMANAGER->setGold((SCENEMANAGER->getGold() - 100));
					//체력상승
					_character->setCurrentHP(8);

				}else SOUNDMANAGER->play("cancle", 1.0f);
			}
		case 2:
			if (KEYMANAGER->isOnceKeyDown('J')) {
				SOUNDMANAGER->play("ok", 1.0f);
				goatshopOff();
			}
		}
	}
}

void uiManager::goatshopOn()
{
	goatShopOpen = true;
}

void uiManager::goatshopOff()
{
	goatShopOpen = false;
}

void uiManager::fireshop()
{
	//파이어볼 유물상점 구동
	//
	if (fireShopOpen) {
		if (KEYMANAGER->isOnceKeyDown('S') && fireCnt < 2) {
			fireCnt += 1;
			SOUNDMANAGER->play("cursor", 1.0f);
		}
		if (KEYMANAGER->isOnceKeyDown('W') && fireCnt > 1) {
			fireCnt -= 1;
			SOUNDMANAGER->play("cursor", 1.0f);
		}
	}
	if (fireShopOpen) {
		switch (fireCnt)
		{
		case 1:
			if (KEYMANAGER->isOnceKeyDown('J')) {
				if (SCENEMANAGER->checkFire()) {
					SOUNDMANAGER->play("cancle", 1.0f); 
					return;
				}
				if (SCENEMANAGER->getGold() >= 1000) {
					SOUNDMANAGER->play("ok", 1.0f);
					SCENEMANAGER->getFire();
					SCENEMANAGER->setGold((SCENEMANAGER->getGold() - 1000));
				}
			}
		case 2:
			if (KEYMANAGER->isOnceKeyDown('J')) {
				SOUNDMANAGER->play("ok", 1.0f);
				fireshopOff();
			}
		}
	}
	// 씬메니저에 checkFIre함수로 파이어 구매했는지 아닌지 불값 반환
}

void uiManager::fireshopOn()
{
	fireShopOpen = true;
}

void uiManager::fireshopOff()
{
	fireShopOpen = false;
}

void uiManager::talklingMan()
{
	if (talkOpen) {

	}
}

void uiManager::talklingManOn()
{
	talkOpen = true;
}

void uiManager::talklingManOff()
{
	talkOpen = false;
}
