#include "pch.h"
#include "uiManager.h"

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


	return S_OK;
}

void uiManager::release()
{

}

void uiManager::update()
{

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
}