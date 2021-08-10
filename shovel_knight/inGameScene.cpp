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

	_character = new character;
	_ui = new uiManager;
	_mapCamera = new mapCamera;
	_object = new object;

	_character->init();
	_ui->init();
	_mapCamera->init();
	_object->init();

	_character->setMapCameraMemoryAddressLink(_mapCamera);
	_character->setObjectMemoryAddressLink(_object);

	_mapCamera->setCharacterAddressLink(_character);
	_mapCamera->setObjectMemoryAddressLink(_object);

	_object->setcharacterMemoryAddressLink(_character);
	_object->setMapCameraMemoryAddressLink(_mapCamera);

	//_backGround = _mapCamera->getBackGround();


	return S_OK;
}

void inGameScene::release()
{
}

void inGameScene::update()
{
	_mapCamera->update();
	_character->update();
	
	SCENEMANAGER->nowHP(_character->getCurrentHp());
	//ĳ������ ���� ����ġ�Ǹ� ���Ŵ����� ����

}

void inGameScene::render()
{

	//_backGround->render(getMemDC(), 0, 0);
	_mapCamera->render();
	_character->render();

	_ui->render();
	
}
