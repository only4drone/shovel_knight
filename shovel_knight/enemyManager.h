#pragma once
#include "gameNode.h"
#include "beeto.h"
#include "wizard.h"
#include "steed.h"
#include "dragon.h"
#include "bugDragon.h"
#include <vector>
#include "bullets.h"

class mapCamera;
class character;


class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;

private:
	vEnemy		_vEnemy;
	viEnemy		_viEnemy;

	mHellFire* _bullet;

	mapCamera* _mapCamera;
	character* _character;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void enemySetting();	//���� ����� �Լ�

	void enemyBulletFire();

	void removeEnemy(int arrNum);

	void collision();

	void enemyImageStorage();		//�� �̹��� ���� �Լ�

	//��ũ
	void setMapCameraMemoryAddressLink(mapCamera* mapCamera) { _mapCamera = mapCamera; }
	void setCharacterMemoryAddressLink(character* character) { _character = character; }

	vector<enemy*> getVEnemy() { return _vEnemy; }
	vector<enemy*>::iterator getVIEnemy() { return _viEnemy; }
};

