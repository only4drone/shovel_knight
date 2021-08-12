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
	_enemyManager = new enemyManager;
	
	_character->setMapCameraMemoryAddressLink(_mapCamera);
	_character->setObjectMemoryAddressLink(_object);
	_character->setUIMemoryAddressLink(_ui);
	_character->setEnemyMemoryAddressLink(_enemyManager);

	_mapCamera->setCharacterAddressLink(_character);
	_mapCamera->setObjectMemoryAddressLink(_object);
	_mapCamera->setEnemyMemoryAddressLink(_enemyManager);

	_object->setcharacterMemoryAddressLink(_character);
	_object->setMapCameraMemoryAddressLink(_mapCamera);

	_enemyManager->setCharacterMemoryAddressLink(_character);
	_enemyManager->setMapCameraMemoryAddressLink(_mapCamera);

	_character->init();
	_ui->init();
	_mapCamera->init();
	_object->init();
	_enemyManager->init();
	_enemyManager->enemySetting();

	//_backGround = _mapCamera->getBackGround();

	return S_OK;
}

void inGameScene::release()
{
}

void inGameScene::update()
{
	_mapCamera->update();
	_enemyManager->update();
	_ui->update();
	_character->update();
	_object->update();

	SCENEMANAGER->nowHP(_character->getCurrentHp());
	//ĳ������ ���� ����ġ�Ǹ� ���Ŵ����� ����

}

void inGameScene::render()
{

	//_backGround->render(getMemDC(), 0, 0);
	_mapCamera->render();
	_enemyManager->render();
	_object->render();
	_character->render();

	_ui->render();
	
}
