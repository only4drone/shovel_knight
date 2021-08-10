#pragma once
#include "gameNode.h"
#include "inGameScene.h"
#include "loadingScene.h"
#include "character.h"
#include "object.h"
#include "mapCamera.h"
#include "openingScene.h"
#include "enemyManager.h"

class playGround : public gameNode
{
private:
	
	character* _character;
	image* _backGround;

	object* _object;

	mapCamera* _mapCamera;

	enemyManager* _enemyManager;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�

	
};

