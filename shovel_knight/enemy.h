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
	RECT			_proveRC;			//���� �÷��̾ �����ϴ� ��Ʈ

	//�̹��� ������ ��ȣ�� ����� ����
	int				_currentFrameX;
	int				_currentFrameY;

	//�� ��Ʈ left,top
	float _x; 
	float _y;

	int				_imageCount;				//�� �̹��� ������ ī��Ʈ ��
	
	//�̹��� �̸��� �����ϱ� ���� ���ڿ� ����
	string			_enemyName;				
	string			_str;
	string			_strSum;

	//�� ������ ī��Ʈ���� ������ ���� ����
	int _randCount;
	int _moveCount;
	int _attackCount;
	int _dieCount;
	int _hitCount;	//�÷��̾�� ���� Ƚ�� ī��Ʈ

	bool _isDefense;	//�÷��̾�� ���� ������ �� �ǰݵ��� �ʰ� �ϴ� ����
	int _defenseCount;	//ī��Ʈ�� ������ �ٽ� _isHit�� false�� �ٲ� ����

	//�� �׾��� �� ��ǿ� �ʿ��� ����
	float _jumpPower;
	float _gravity;

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
	inline RECT getproveRect() { return _proveRC; }

	bool getDefense() { return _isDefense; }	// true�� �� �÷��̾�� �浹 ���� �ʰ� �ϴ� ������
	//int getHit() { return _hitCount; }
	
	//�÷��̾�� �浹 �� ī��Ʈ ���� ��ų ������
	void setHit(int i) { _hitCount += i; }
};

