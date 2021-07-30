#include "pch.h"
#include "loadingScene.h"
#include "progressBar.h"

loadingScene::loadingScene()
	: _background(nullptr), 
	_loadingBar(nullptr),
	_currentCount(0)

{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_background = IMAGEMANAGER->addImage("���", "Ÿ�������ε�.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init(0, WINSIZEY - 50, WINSIZEX, 50);
	_loadingBar->setGauge(0, 0);

	CreateThread(
		NULL,				//������ ���ȼӼ�(�ڽ������� �����Ҷ�)
		NULL,				//�������� ����ũ��(0�̸� ���ξ����� ����)
		threadFunction,		//����� �Լ�
		this,				//������ �Ű�����(this �� ������ �� Ŭ����)
		NULL,				//������ Ư��
		NULL);				//������ ID

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loadingBar);
}

void loadingScene::update()
{
	_loadingBar->update();
	_loadingBar->setGauge(_currentCount, LOADINGMAX);

	if (_currentCount == LOADINGMAX)
	{
		//Ÿ���������Ӿ�
		SCENEMANAGER->changeScene("�ΰ��Ӿ�");
	}
}

void loadingScene::render()
{
	_background->render(getMemDC());
	_loadingBar->render();
}

DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	loadingScene* loadingHelper = (loadingScene*)lpParameter;

	//�������� �׳� ���⿡ ����Ͻ� �̹����� ���� �߰��� �ϸ�˴ϴ�

	while (loadingHelper->_currentCount != LOADINGMAX)
	{
		IMAGEMANAGER->addImage("����", "Ÿ����������.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

		//�̷��� ���ϸ� ���� �������� �ʾƿ�
		Sleep(1);

		loadingHelper->_currentCount++;
	}

	return 0;
}
