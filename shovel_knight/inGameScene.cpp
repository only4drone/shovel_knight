#include "pch.h"
#include "inGameScene.h"


inGameScene::inGameScene()
{
}


inGameScene::~inGameScene()
{
}

HRESULT inGameScene::init()
{

	_backGround = IMAGEMANAGER->findImage("���");

	_character = new character;
	_ui = new uiManager;

	_character->init();
	_ui->init();

	return S_OK;
}

void inGameScene::release()
{
}

void inGameScene::update()
{
	_character->update();
	
	SCENEMANAGER->nowHP(_character->getCurrentHp());
	//ĳ������ ���� ����ġ�Ǹ� ���Ŵ����� ����

}

void inGameScene::render()
{
	IMAGEMANAGER->findImage("���")->render(getMemDC());

	_backGround->render(getMemDC(), 0, 0);

	_character->render();

	_ui->render();
	
}
