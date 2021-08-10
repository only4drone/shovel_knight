#pragma once
#include "gameNode.h"

//���� ���� �θ�Ŭ����

enum ENEMYSTATE		//���� ���� ����
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
	RECT			_rc;				//�� ��Ʈ
	//�̹��� ������ ��ȣ�� ����� ����
	int				_currentFrameX;
	int				_currentFrameY;

	float _x;							//�� ��Ʈ�� left 
	float _y;							//�� ��Ʈ�� top 

	int				_imageCount;				//�� �̹��� ������ ī��Ʈ ��
	const char*		_enemyName;			//init �Լ� ù�� ° �Ű������� �������� ���� ����

	//�̹��� �̸��� �����ϱ� ���� ���ڿ� ����
	string			_cast;				
	string			_str;
	string			_strsum;

	//�� ������ ī��Ʈ���� ������ ���� ����
	int _randCount;
	int _moveCount;
	int _attackCount;
	int _diecount;
public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position, ENEMYDIRECTION enemyDirection);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void draw();		//�׷��ִ� �Լ�
	virtual void enemyFrame();	//���� ���¿� ���� �����ӵ����� �Լ�
	virtual void move();		//������ �Լ�
	virtual void attack();		//���� �Լ�
	virtual void die();			//���� ó�� �Լ�

	virtual void enemyAI();		//���� ���¸� �����ϴ� �Լ�

	//���ʹ� ��Ʈ�� ���� ������
	inline RECT getRect() { return _rc; }
};

