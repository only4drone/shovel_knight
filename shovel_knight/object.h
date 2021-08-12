#pragma once
#include "gameNode.h"


#define PLATFORMMAX 5
#define SANDBLOCKMAX 128
#define LADDERMAX 15
#define NPCMAX 3
#define BUBBLEMAX 20

class character;
class mapCamera;

struct tagPlatform //�����̴� ����
{
	image* objectImage;								//	������Ʈ�� �̹���
	RECT rc;										//	������Ʈ�� ��Ʈ
	float x, y;										//	������Ʈ�� ���� X, Y ��
	float speed;									//	������Ʈ �̵��ӵ� ��
	float min, max;									//	������Ʈ �̵������� �ּ�, �ִ밪

	int type;
	int index;

	bool isDirection;								//	������Ʈ�� ������ȯ�� ���� �Ұ�					
};

struct tagSandBlock //�����
{
	image* objectImage;								//	������Ʈ�� �̹���
	RECT rc;										//	������Ʈ�� ��Ʈ
	float x, y;										//	������Ʈ�� ���� X, Y ��

	int type;
	int index;
	int currentFrame;								// ������ �̹��� �ε���
};

struct tagLadder //��ٸ�
{
	RECT rc;										//	������Ʈ�� ��Ʈ
	float x, y;										//	������Ʈ�� ���� X, Y ��
	float height;									//  ������Ʈ�� ���� ����

	int type;
	int index;
};

struct tagNPC // npc
{
	image* npcImage;								//  npc�� �̹���
	RECT rc;										//	npc�� ��Ʈ
	float x, y;										//	npc�� ���� X, Y ��
	float width, height;							//  npc�� ����, ���� ����

	int type;
	int index;
};

struct tagBubble // ����� 
{
	image* objectImage;								//  ������Ʈ�� �̹���
	RECT rc;										//	������Ʈ�� ��Ʈ
	float x, y;										//	������Ʈ�� ���� X, Y ��
	float startX, startY;							//  ������Ʈ�� ���� X, Y ��
	float width, height;							//  ������Ʈ�� ����, ���� ����
	float min, max;									//	������Ʈ�� X�� �ּ�, �ִ밪
	float topMax;									//	������Ʈ�� Y�� �ִ밪
	float speed;									//	������Ʈ �̵��ӵ� ��

	int type;
	int index;
	bool isAlive;									//  ����� ���������� ���� ����
	bool isDirection;								//	������Ʈ�� ������ȯ�� ���� �Ұ�
};


class object : public gameNode
{
private:
	//���������� ����Ҹ��� �͵�

	int _count;		// ������ ī��Ʈ

	tagPlatform _platform[PLATFORMMAX];

	tagSandBlock _sandBlock[SANDBLOCKMAX];

	tagLadder _ladder[LADDERMAX];

	tagNPC _npc[NPCMAX];

	tagBubble _bubble[BUBBLEMAX];

	character* _character;

	mapCamera* _mapCamera;



	//1��Ÿ�� - ĳ���Ϳ� �浹������ ���θ� ���°͵� - ����, �����
	//2��Ÿ�� - ĳ���Ϳ� �浹������ ������°͵� - ü��ȸ�� ������Ʈ, ������
	//3��Ÿ�� - ĳ���Ϳ� �浹������ �������� �޴°͵� - �����, ���̾

	//1��Ÿ���� �ε��� �� ���� - 1.�¿� ����, 2.���� ����, 10.ū �����, 11.���� �����, 21. ��ٸ�

	//2��Ÿ���� �ε��� �� ���� - 1.���, 2.ġŲ, 10.ū���̾�, 11.����, 12. �����̾�

	//3��Ÿ���� �ε��� �� ���� - 1.�����, 2.���̾

public:
	object();
	~object();

	void collision();
	void gravity();
	void imgSetting();															// ���¿� ���� �̹��� ó��
	void imgFrameSetting();														// ĳ���� �̹��� ������ ó��
	void objectMove();															// ������Ʈ���� ������ ó��

	void platformSetting();														// ������Ʈ���� ��ġ�� ������ ���� �Լ�
	void sandBlockSetting();
	void potionSetting();
	void jewelSetting();
	void bubbleSetting();
	void fireBallSetting();
	void ladderSetting();
	void npcSetting();

	int getPlatformrMax() { return PLATFORMMAX; }
	int getLadderMax() { return LADDERMAX; }
	int getNPCMAX() { return NPCMAX; }
	int getSandBlockMAX() { return SANDBLOCKMAX; }
	int getBubbleMAx() { return BUBBLEMAX; }

	tagPlatform getPlatform(int arrNum) { return _platform[arrNum]; }
	tagLadder getLadder(int arrNum) {	return _ladder[arrNum];}
	tagNPC getNPC(int arrNum) { return _npc[arrNum]; }
	tagSandBlock getSandBlock(int arrNum) { return _sandBlock[arrNum]; }
	tagBubble getBUbble(int arrNum) { return _bubble[arrNum]; }


	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	void setMapCameraMemoryAddressLink(mapCamera* mapCamera) { _mapCamera = mapCamera; }			// �ʸŴ��� Ŭ�� ��ũ 
	
	void setcharacterMemoryAddressLink(character* character) { _character = character; }			// ĳ���� Ŭ�� ��ũ 

};
