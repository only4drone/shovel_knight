#include "pch.h"
#include "gameOver.h"

gameOver::gameOver()
{
}

gameOver::~gameOver()
{
}

HRESULT gameOver::init()
{
	cnt = 0;
	IMAGEMANAGER->addImage("gameover", "image/UI/gameover.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameover1", "image/UI/gameover1.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameover2", "image/UI/gameover2.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameover3", "image/UI/gameover3.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameover4", "image/UI/gameover4.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameover5", "image/UI/gameover5.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameover6", "image/UI/gameover6.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameover7", "image/UI/gameover7.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameover8", "image/UI/gameover8.bmp", 1280, 720, true, RGB(255, 0, 255));

	SCENEMANAGER->delFire();
	SCENEMANAGER->setGold(10000);
	SCENEMANAGER->setMana(100);
	return S_OK;
}

void gameOver::release()
{
}

void gameOver::update()
{
}

void gameOver::render()
{
	cnt++;
	SOUNDMANAGER->stop("bgm");
	//SOUNDMANAGER->addSound("laugh", "sounds/laugh.mp3", false, false);
	SOUNDMANAGER->play("laugh", 0.3f);
	if( cnt >= 0) IMAGEMANAGER->findImage("gameover")->render(getMemDC());
	if (cnt >= 15) IMAGEMANAGER->findImage("gameover1")->render(getMemDC());
	if (cnt >= 20) IMAGEMANAGER->findImage("gameover2")->render(getMemDC());
	if (cnt >= 25) IMAGEMANAGER->findImage("gameover3")->render(getMemDC());
	if (cnt >= 30) IMAGEMANAGER->findImage("gameover4")->render(getMemDC());
	if (cnt >= 35) IMAGEMANAGER->findImage("gameover5")->render(getMemDC());
	if (cnt >= 40) IMAGEMANAGER->findImage("gameover6")->render(getMemDC());
	if (cnt >= 45) IMAGEMANAGER->findImage("gameover7")->render(getMemDC());
	if (cnt >= 50) IMAGEMANAGER->findImage("gameover8")->render(getMemDC());

	if (cnt > 250) {
		SCENEMANAGER->changeScene("title");
	} 
	
}
