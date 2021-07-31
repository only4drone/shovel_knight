#pragma once
#include "gameNode.h"

#define SPEED 5.0f									// �̵� �ӵ�
#define GRAVITY 0.8f								// �߷� ��
#define JUMPPOWER 18.0f								// ���� �Ŀ� ��
#define RCMAX 4										// �׽�Ʈ�� ��Ʈ
#define HANGRCMAX 2									// �׽�Ʈ�� ��ٸ� ��Ʈ

enum state
{
	IDLE,				// ���̵�
	RUN,				// �޸���
	JUMP,				// ����
	ATTACK,				// ����
	JUMPATTACK,			// ���� ����
	JUMPBOTTOMATTACK,	// ���� �ϴ� ����
	HURT,				// �ǰ�
	DEATH,				// ����
	HANG				// ��ٸ� Ÿ��
};

class character : public gameNode
{
private:
	image* _characterImg;							// ĳ���� �̹���
	RECT _imgRect;									// ĳ������ �̹��� ��Ʈ
	RECT _collisionRect;							// ĳ������ �浹 ��Ʈ(��� �浹�� �������)
	state _state;									// ĳ������ ���� ��

	float _x, _y;									// ĳ������ ���� X, Y ��
	float _speed;									// ĳ���� �̵��ӵ� ��
	float _jumpPower;								// ������ ��
	float _gravity;									// �߷� ��

	bool _direction;								// ĳ���Ͱ� �ٶ󺸰� �ִ� ���� 0 == ������ ����, 1 == ���� ���� �ٶ�

	int _damage;									// ĳ���� ������
	int _currentHP, _maxHP;							// ĳ���� ����, �ƽ� ü��
	int _currentFrame;								// ������ �̹��� �ε���
	int _count;										// ������ �̹��� ���͹�
	int _hangCount;									// ��ٸ� ī��Ʈ�� �� ī��Ʈ�� ���� hang �̹��� ����

	// ----------------------------------------------------------------------
	RECT _rc[RCMAX];								// �׽�Ʈ�� ��Ʈ
	RECT _attackRc;									// �ǰ� �׽�Ʈ�� ��Ʈ
	RECT _hangRc[HANGRCMAX];						// ��ٸ� �׽�Ʈ�� ��Ʈ
	int _rcNum;										// ���� � ��ֹ��� �浹�ߴ��� ���
	int _hangRcNum;

public:
	character();
	~character();

	HRESULT init();
	void release();
	void update();
	void render();

	void controll();															// ĳ���� ��Ʈ��Ű ó��
	void imgSetting();															// ���¿� ���� �̹��� ó��
	void imgFrameSetting();														// ĳ���� �̹��� ������ ó��
	void gravity();																// ĳ���� �߷� ó��
	void hang();																// ĳ���� ��ٸ� Ÿ�� ó��
	void collision();															// ĳ���� �浹 ó��
	void attack();																// ĳ���� ���� ó��
	void hitDamage(float damage);												// ĳ���� �ǰ� �� ó��
	void death();																// ĳ���� ���� ó��

	float getCharacterX() { return _x; }										// ĳ���� X�� ��ȯ
	float getCharacterY() { return _y; }										// ĳ���� Y�� ��ȯ
	bool getDirection() { return _direction; }									// ĳ���� ���� ��ȯ
	int getCurrentFrame() { return _currentFrame; }								// ĳ���� ���� ������ ��ȯ
	state getState() { return _state; }											// ĳ���� ���� ��ȯ
	RECT getCharacterRect() { return _collisionRect; }							// ĳ���� �浹 ��Ʈ ��ȯ

	void setCharacterX(float x) { _x = x; }										// ĳ���� X�� ����
	void setCharacterY(float y) { _y = y; }										// ĳ���� Y�� ����
	void setCharacterDirection(bool direction) { _direction = direction; }		// ĳ���� ���� ����
	void setState(state state) { _state = state; }								// ĳ������ ���� ����
		
	//void setMapMemoryAddressLink(mapManager* mapM) { _mapM = mapM; }			// �ʸŴ��� Ŭ�� ��ũ 
	//void setEnemyMemoryAddressLink(enemyManager* eM) { _eM = eM; }			// �̳ʹ̸Ŵ��� Ŭ���� ��ũ

};

