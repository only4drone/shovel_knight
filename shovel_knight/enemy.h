#pragma once
#include "gameNode.h"

//���� ���� �θ�Ŭ����

enum ENEMYSTATE		//���� ���� ����
{
	//E == enemy
	E_IDLE,
	E_MOVE,
	E_ATTACK,
	E_DIE,
	E_SMOKE
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
	RECT			_bodyRC;			//�巹�� ���� ��Ʈ
	RECT			_imageRC;			//�巹�� �̹��� ��Ʈ

	//�̹��� ������ ��ȣ�� ����� ����
	int				_currentFrameX;
	int				_currentFrameY;

	//�� ��Ʈ left,top
	float _x; 
	float _y;

	//ĳ���� ��ǥ
	float _characterX;
	float _characterY;
	//ĳ���� ������Ʈ
	RECT _characterRC;


	int				_imageCount;				//�� �̹��� ������ ī��Ʈ ��
	
	//�̹��� �̸��� �����ϱ� ���� ���ڿ� ����
	string			_enemyName;				
	string			_str;
	string			_strSum;

	//�� ������ ī��Ʈ���� ������ ���� ����
	int _randCount;
	int _moveCount;

	int _attackCount;

	int _hitCount;	//�÷��̾�� ���� Ƚ�� ī��Ʈ

	bool _isDefense;	//�÷��̾�� ���� ������ �� �ǰݵ��� �ʰ� �ϴ� ����
	int _defenseCount;	//ī��Ʈ�� ������ �ٽ� _is_isDefense�� false�� �ٲ� ����
	int _smokeCount;
	int _dieCount;

	//�� �׾��� �� ��ǿ� �ʿ��� ����
	float _jumpPower;
	float _gravity;

	bool _isDelete;		//true�� ����
	bool _isSmoke;		//ture�� �� ���°� E_SMOKE�� ����


public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position, ENEMYDIRECTION enemyDirection);
	virtual void release();
	virtual void update();
	virtual void update(int x, int y, float characterX, float characterY);		//�� ī�޶� ������Ʈ�ϱ� ���� �Լ�, x == �� ī�޶�X, y == �� ī�޶�Y
	virtual void render();

	virtual void draw();		//���� �׷��ִ� �Լ�
	virtual void enemyFrame();	//���� ���¿� ���⿡ ���� �����ӵ����� �Լ�
	virtual void move();		//������ ������ �� �����ϴ� �Լ�
	virtual void attack();		//���� ������ �� �����ϴ� �Լ�
	virtual void die();			//���� �׾��� �� �����ϴ� �Լ�

	virtual void enemyAI();		//���� ���¸� �����ϴ� �Լ�



	//�����ڿ� ������

	inline float getX() { return _x; }
	inline float getY() { return _y; }
	
	inline RECT getRect() { return _rc; }					//�� ��Ʈ�� ���� ������
	inline RECT getproveRect() { return _proveRC; }			//�� ������Ʈ�� ���� ������
	inline RECT getbodyRect() { return _bodyRC; }			//�� �ٵ�Ʈ�� ���� ������
	inline string getEnemyName() { return _enemyName; }		//�� �̸��� ���� ������ (Ȥ�� ���� ������)
	
	inline bool getDefense() { return _isDefense; }			// true�� �� �÷��̾�� �浹 ���� �ʰ� �ϴ� ������
	inline void setDefense(bool x) { _isDefense = x; }		// _isDefense�� ���� ������
	
	inline ENEMYSTATE getEnemyState() { return _enemyState; }	//�� ���¿� ���� ������
	inline void setEnemyState(ENEMYSTATE x) { _enemyState = x; }
	
	inline void setHit(int i) { _hitCount += i; }			//�÷��̾�� �浹 �� ī��Ʈ ���� ��ų ������

	inline bool getDelete() { return _isDelete; }		// _isDelete�� ���� ������

	inline bool getHead() { return _isSmoke; }
	inline void setHead(bool x) { _isSmoke = x; }

	inline void setFrameX(int x) { _currentFrameX = x; }
};

