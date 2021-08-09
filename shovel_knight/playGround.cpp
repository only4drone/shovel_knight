#include "pch.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ���⿡�� �ض�!!!
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("���", "image/shovel_knight_map.bmp", 1280, 720, true, RGB(255, 0, 255));

	_backGround = IMAGEMANAGER->findImage("���");

	SCENEMANAGER->addScene("�ΰ��Ӿ�", new inGameScene);

	

	SCENEMANAGER->addScene("title", new openingScene);

	SCENEMANAGER->changeScene("title");




	return S_OK;
}

//�޸� ������ ����� �ض�!!!!
void playGround::release()
{
	gameNode::release();


}

//����ó���� ����ٰ�!
void playGround::update()
{
	gameNode::update();


	SCENEMANAGER->update();
	
}

//����� �׷����!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============������ ���� �ǵ帮�� ���� ============
	
	SCENEMANAGER->render();

	// ĳ���Ͷ� ��׶���� ���߿� �ΰ��ӿ��� ���� 
	//_backGround->render(getMemDC(), 0, 0);

	//_character->render();

	TIMEMANAGER->render(getMemDC());

	//=============== �ؿ��� �ǵ������� ================
	_backBuffer->render(getHDC(), 0, 0);

}

