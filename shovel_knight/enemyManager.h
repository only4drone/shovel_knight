#pragma once
#include "gameNode.h"
#include "beeto.h"
#include "wizard.h"
#include "steed.h"
#include <vector>
#include "bullets.h"

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;

private:
	vEnemy		_vEnemy;
	viEnemy		_viEnemy;

	
	bullet* _bullet;

	
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void enemySetting();	//���� ����� �Լ�
	POINT enemyPosition(int i);	//�� ��ġ �Լ�

	void enemyBulletFire();

	void removeEnemy(int arrNum);

	void collision();

	void enemyImageStorage();		//�� �̹��� ���� �Լ�

	vector<enemy*> getVMinion() { return _vEnemy; }
	vector<enemy*>::iterator getVIMinion() { return _viEnemy; }
};

