#pragma once
#include "gameNode.h"

//���� ���� �θ�Ŭ����

enum ENEMYSTATE		//���� ����
{
	//E == enemy
	E_IDLE,
	E_MOVE,
	E_ATTACK,
	E_DIE
};

enum ENEMYDIRECTION	//�� �¿� ����
{
	E_LEFT,
	E_RIGHT
};

class enemy : public gameNode
{
protected:
	ENEMYSTATE		_enemyState;
	ENEMYDIRECTION	_enemyDirection;
	image*			_imageName;			//���� ����� �̹��� �̸�
	RECT			_rc;

	int				_currentFrameX;		//�̹��� ������ ��ȣ�� ����� ����
	int				_currentFrameY;

	int				_count;				//�� �̹��� ������ ī��Ʈ ��
	char			_enemyName;			//init �Լ� ù�� ° �Ű������� �������� ���� ����
	
public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual HRESULT init(char imageName, POINT position, ENEMYDIRECTION enemyDirection);
	virtual void release();
	virtual void update();
	virtual void render();

	void draw();		//�׷��ִ� �Լ�
	void enemyFrame();	//���� ���¿� ���� �����ӵ����� �Լ�
	void move();		//������ �Լ�
	void attack();		//���� �Լ�
	void die();			//���� ó�� �Լ�
	void enemyAI();		//���� ���¸� �����ϴ� �Լ�
	

	//���ʹ� ��Ʈ�� ���� ������
	inline RECT getRect() { return _rc; }
};

