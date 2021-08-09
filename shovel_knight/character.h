#pragma once
#include "gameNode.h"

#define SPEED 5.0f									// 이동 속도
#define GRAVITY 0.8f								// 중력 값
#define JUMPPOWER 18.0f								// 점프 파워 값

enum state
{
	IDLE,				// 아이들
	RUN,				// 달리기
	JUMP,				// 점프
	ATTACK,				// 공격
	JUMPATTACK,			// 점프 공격
	JUMPBOTTOMATTACK,	// 점프 하단 공격
	HURT,				// 피격
	DEATH,				// 죽음
	HANG				// 사다리 타기
};

class object;
class mapCamera;

class character : public gameNode
{
private:
	image* _characterImg;							// 캐릭터 이미지
	RECT _imgRect;									// 캐릭터의 이미지 렉트
	RECT _collisionRect;							// 캐릭터의 충돌 렉트(모든 충돌은 요놈으로)
	state _state;									// 캐릭터의 상태 값

	mapCamera* _mapCamera;							// 맵 카메라 클래스
	object* _object;								// 오브젝트 클래스

	float _x, _y;									// 캐릭터의 중점 X, Y 값
	float _speed;									// 캐릭터 이동속도 값
	float _jumpPower;								// 점프력 값
	float _gravity;									// 중력 값

	bool _direction;								// 캐릭터가 바라보고 있는 방향 0 == 오른쪽 방향, 1 == 왼쪽 방향 바라봄
	bool _isPixelCollision;							// 캐릭터가 픽셀 충돌 중인가?

	int _damage;									// 캐릭터 데미지
	int _currentHP, _maxHP;							// 캐릭터 현재, 맥스 체력
	int _currentFrame;								// 프레임 이미지 인덱스
	int _count;										// 프레임 이미지 인터벌
	int _hangCount;									// 사다리 카운트로 이 카운트에 따라 hang 이미지 갱신

	int _rcNum;										// 현재 어떤 장애물에 충돌했는지 기록
	int _hangRcNum;									// 현재 어떤 사다리에 충돌했는지 기록

public:
	character();
	~character();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void controll();															// 캐릭터 컨트롤키 처리
	void imgSetting();															// 상태에 따라 이미지 처리
	void imgFrameSetting();														// 캐릭터 이미지 프레임 처리
	void gravity();																// 캐릭터 중력 처리
	void hang();																// 캐릭터 사다리 타기 처리
	void collision();															// 캐릭터 충돌 처리
	void attack();																// 캐릭터 공격 처리
	void hitDamage(float damage);												// 캐릭터 피격 시 처리
	void death();																// 캐릭터 죽음 처리

	float getCharacterX() { return _x; }										// 캐릭터 X값 반환
	float getCharacterY() { return _y; }										// 캐릭터 Y값 반환
	float getSpeed() { return _speed; }											// 캐릭터 스피드값 반환
	float getJumpPower() { return _jumpPower; }									// 캐릭터 점프 값 반환
	float getGravity() { return _gravity; }										// 캐릭터 중력 값 반환
	bool getDirection() { return _direction; }									// 캐릭터 방향 반환
	int getCurrentFrame() { return _currentFrame; }								// 캐릭터 현재 프레임 반환
	state getState() { return _state; }											// 캐릭터 상태 반환
	RECT getCharacterRect() { return _collisionRect; }							// 캐릭터 충돌 렉트 반환
	int getCurrentHp() { return _currentHP; }									// 캐릭터 현재 체력 반환
	int getMaxHp() { return _maxHP; }											// 캐릭터 맥스 체력 반환

	void setCharacterX(float x) { _x = x; }										// 캐릭터 X값 설정
	void setCharacterY(float y) { _y = y; }										// 캐릭터 Y값 설정
	void setCharacterDirection(bool direction) { _direction = direction; }		// 캐릭터 방향 설정
	void setState(state state) { _state = state; }								// 캐릭터의 상태 설정
	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }				// 캐릭터의 상태 설정
	void setSpeed(float speed) { _speed = speed; }								// 캐릭터의 상태 설정

	void setMapCameraMemoryAddressLink(mapCamera* mapCamera) { _mapCamera = mapCamera; } // 맵 카매라 클라스 링크 
	void setObjectMemoryAddressLink(object* object) { _object = object; }		// 오브젝트 클라스 링크 
	//void setEnemyMemoryAddressLink(enemyManager* eM) { _eM = eM; }			// 이너미매니저 클래스 링크

};

