#pragma once
#include "gameNode.h"

#define GRAVITY 0.8f								// �߷� ��
#define JUMPPOWER 25.0f								// ���� �Ŀ� ��

// ���� ����
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
	HANG,				// ��ٸ� Ÿ��
	SKILL				// ���̾ �߻�
};

// ���� ����
class object;
class mapCamera;
class uiManager;
class enemyManager;

class character : public gameNode
{
private:
	image* _characterImg;							// ĳ���� �̹���
	RECT _imgRect;									// ĳ������ �̹��� ��Ʈ
	RECT _collisionRect;							// ĳ������ �浹 ��Ʈ(��� �浹�� �������)
	state _state;									// ĳ������ ���� ��

	uiManager* _ui;									// ui Ŭ����
	mapCamera* _mapCamera;							// �� ī�޶� Ŭ����
	object* _object;								// ������Ʈ Ŭ����
	enemyManager* _enemyManager;					// �̳ʹ� �Ŵ��� Ŭ����

	float _x, _y;									// ĳ������ ���� X, Y ��
	float _speed;									// ĳ���� �̵��ӵ� ��
	float _jumpPower;								// ������ ��
	float _gravity;									// �߷� ��

	bool _direction;								// ĳ���Ͱ� �ٶ󺸰� �ִ� ���� 0 == ������ ����, 1 == ���� ���� �ٶ�
	bool _isPixelCollision;							// ĳ���Ͱ� �ȼ� �浹 ���ΰ�?

	int _damage;									// ĳ���� ������
	int _currentHP, _maxHP;							// ĳ���� ����, �ƽ� ü��
	int _currentFrame;								// ������ �̹��� �ε���
	int _count;										// ������ �̹��� ���͹�
	int _hangFrameCount;							// ��ٸ� ī��Ʈ�� �� ī��Ʈ�� ���� hang �̹��� ����
	int _skillFrameCount;							// ��ų �ൿ�� ī��Ʈ�� �� ī��Ʈ�� ���� �̹��� ���ߴ� ���� ���

	int _rcNum;										// ���� � ��ֹ��� �浹�ߴ��� ���
	int _hangRcNum;									// ���� � ��ٸ��� �浹�ߴ��� ���

public:
	character();
	~character();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void controll();															// ĳ���� ��Ʈ��Ű ó��
	void imgSetting();															// ���¿� ���� �̹��� ó��
	void imgFrameSetting();														// ĳ���� �̹��� ������ ó��
	void gravity();																// ĳ���� �߷� ó��
	void hang();																// ĳ���� ��ٸ� Ÿ�� ó��
	void collision();															// ĳ���� �浹 ó��
	void attack();																// ĳ���� ���� ó��
	void skill();																// ĳ���� ��ų ó��
	void hitDamage(float damage);												// ĳ���� �ǰ� �� ó��
	void death();																// ĳ���� ���� ó��
	void shop(int arrNum);														// ĳ���� ���� �̿� ó��

	float getCharacterX() { return _x; }										// ĳ���� X�� ��ȯ
	float getCharacterY() { return _y; }										// ĳ���� Y�� ��ȯ
	float getSpeed() { return _speed; }											// ĳ���� ���ǵ尪 ��ȯ
	float getJumpPower() { return _jumpPower; }									// ĳ���� ���� �� ��ȯ
	float getGravity() { return _gravity; }										// ĳ���� �߷� �� ��ȯ
	bool getDirection() { return _direction; }									// ĳ���� ���� ��ȯ
	int getCurrentFrame() { return _currentFrame; }								// ĳ���� ���� ������ ��ȯ
	state getState() { return _state; }											// ĳ���� ���� ��ȯ
	RECT getCharacterRect() { return _collisionRect; }							// ĳ���� �浹 ��Ʈ ��ȯ
	int getCurrentHp() { return _currentHP; }									// ĳ���� ���� ü�� ��ȯ
	int getMaxHp() { return _maxHP; }											// ĳ���� �ƽ� ü�� ��ȯ

	void setCharacterX(float x) { _x = x; }										// ĳ���� X�� ����
	void setCharacterY(float y) { _y = y; }										// ĳ���� Y�� ����
	void setCharacterDirection(bool direction) { _direction = direction; }		// ĳ���� ���� ����
	void setState(state state) { _state = state; }								// ĳ������ ���� ����
	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }				// ĳ������ ���� ����
	void setSpeed(float speed) { _speed = speed; }								// ĳ������ ���� ����

	void setMapCameraMemoryAddressLink(mapCamera* mapCamera) { _mapCamera = mapCamera; }			// �� ī�Ŷ� Ŭ�� ��ũ 
	void setObjectMemoryAddressLink(object* object) { _object = object; }							// ������Ʈ Ŭ�� ��ũ 
	void setUIMemoryAddressLink(uiManager* uiManager) { _ui = uiManager; }							// ui Ŭ�� ��ũ 
	void setEnemyMemoryAddressLink(enemyManager* enemyManager) { _enemyManager = enemyManager; }	// �̳ʹ̸Ŵ��� Ŭ���� ��ũ

};

