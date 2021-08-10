#pragma once
#include "gameNode.h"


#define SPEED 5.0f									// �̵� �ӵ�
#define GRAVITY 0.8f								// �߷� ��
#define JUMPPOWER 18.0f								// ���� �Ŀ� ��
#define PLATFORMMAX 5
#define SANDBLOCKMAX 128

class character;
class mapCamera;

struct tagPlatform
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

struct tagSandBlock
{
	image* objectImage;								//	������Ʈ�� �̹���
	RECT rc;										//	������Ʈ�� ��Ʈ
	float x, y;										//	������Ʈ�� ���� X, Y ��

	int type;
	int index;
	int currentFrame;								// ������ �̹��� �ε���

};

class object : public gameNode
{
private:
	//���������� ����Ҹ��� �͵�

	int _count;		// ������ ī��Ʈ

	tagPlatform _platform[PLATFORMMAX];

	tagSandBlock _sandBlock[SANDBLOCKMAX];

	character* _character;

	mapCamera* _mapCamera;


	//1��Ÿ�� - ĳ���Ϳ� �浹������ ���θ� ���°͵� - ����, �����
	//2��Ÿ�� - ĳ���Ϳ� �浹������ ������°͵� - ü��ȸ�� ������Ʈ, ������
	//3��Ÿ�� - ĳ���Ϳ� �浹������ �������� �޴°͵� - �����, ���̾

	//1��Ÿ���� �ε��� �� ���� - 1.�¿� ����, 2.���� ����, 10.ū �����, 11.���� �����

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




	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	void setMapCameraMemoryAddressLink(mapCamera* mapCamera) { _mapCamera = mapCamera; }			// �ʸŴ��� Ŭ�� ��ũ 
	
	void setcharacterMemoryAddressLink(character* character) { _character = character; }			// ĳ���� Ŭ�� ��ũ 

};