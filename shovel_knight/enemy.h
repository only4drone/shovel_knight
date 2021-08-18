#pragma once
#include "gameNode.h"

//적을 찍어내는 부모클래스

enum ENEMYSTATE		//적의 상태 구분
{
	//E == enemy
	E_IDLE,
	E_MOVE,
	E_ATTACK,
	E_DIE,
	E_SMOKE
};

enum ENEMYDIRECTION	//적 좌우 구분
{
	E_LEFT,
	E_RIGHT
};

enum ENEMYTYPE //적 타입
{
	E_NORMAL,
	E_BOSS
};

class enemy : public gameNode
{
protected:
	ENEMYSTATE		_enemyState;		
	ENEMYDIRECTION	_enemyDirection;
	ENEMYTYPE		_enemyType;

	image*			_imageName;			//적이 사용할 이미지 이름
	image*			_lazer;				//레이저 이미지
	RECT			_rc;				//적 렉트
	RECT			_proveRC;			//적이 플레이어를 감지하는 렉트
	RECT			_bodyRC;			//드레곤 몸통 렉트
	RECT			_imageRC;			//드레곤 이미지 렉트
	RECT			_lazerRC;			//레이저 렉트

	//이미지 프레임 번호로 사용할 변수
	int				_currentFrameX;
	int				_currentFrameY;

	//적 렉트 left,top
	float _x; 
	float _y;

	//캐릭터 좌표
	float _characterX;
	float _characterY;
	//캐릭터 감지렉트
	RECT _characterRC;


	int				_imageCount;				//적 이미지 프레임 카운트 용
	
	//이미지 이름을 조합하기 위한 문자열 변수
	string			_enemyName;				
	string			_str;
	string			_strSum;

	//적 패턴을 카운트별로 나누기 위한 변수
	int _randCount;
	int _moveCount;

	int _attackCount;

	int _hitCount;	//플레이어에게 맞은 횟수 카운트

	bool _isDefense;	//플레이어에게 맞은 상태일 때 피격되지 않게 하는 변수
	int _defenseCount;	//카운트가 지나면 다시 _is_isDefense를 false로 바꿀 변수
	int _smokeCount;
	int _dieCount;

	//적 죽었을 때 모션에 필요한 변수
	float _jumpPower;
	float _gravity;

	bool _isDelete;		//true면 삭제
	bool _isSmoke;		//ture면 적 상태가 E_SMOKE로 변함

	 int _initCount;
public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position, ENEMYDIRECTION enemyDirection);
	virtual void release();
	virtual void update();
	virtual void update(int x, int y, float characterX, float characterY);		//맵 카메라를 업데이트하기 위한 함수, x == 맵 카메라X, y == 맵 카메라Y
	virtual void render();

	virtual void draw();		//적을 그려주는 함수
	virtual void enemyFrame();	//적의 상태와 방향에 따라 프레임돌리는 함수
	virtual void move();		//움직임 상태일 때 실행하는 함수
	virtual void attack();		//공격 상태일 때 실행하는 함수
	virtual void die();			//적이 죽었을 때 실행하는 함수

	virtual void enemyAI();		//적의 상태를 정의하는 함수



	//접근자와 설정자

	inline float getX() { return _x; }
	inline float getY() { return _y; }
	
	inline RECT getRect() { return _rc; }					//적 렉트에 대한 접근자
	inline RECT getproveRect() { return _proveRC; }			//적 감지렉트에 대한 접근자
	inline RECT getbodyRect() { return _bodyRC; }			//적 바디렉트에 대한 접근자
	inline RECT getLazerRect() { return _lazerRC; }			//적 레이저렉트에 대한 접근자
	inline string getEnemyName() { return _enemyName; }		//적 이름에 대한 접근자 (혹시 몰라서 만들어둠)
	
	inline bool getDefense() { return _isDefense; }			// true일 때 플레이어와 충돌 되지 않게 하는 접근자
	inline void setDefense(bool x) { _isDefense = x; }		// _isDefense에 대한 설정자
	
	inline int getAttackCount() { return _attackCount; }
	inline void setAttackCount(int count) { _attackCount = count; }

	inline ENEMYSTATE getEnemyState() { return _enemyState; }	//적 상태에 대한 접근자
	inline ENEMYDIRECTION getEnemyDirction() { return _enemyDirection; }	//적 방향에 대한 접근자
	inline void setEnemyState(ENEMYSTATE x) { _enemyState = x; }
	
	inline int getHit()	{ return _hitCount; }
	inline void setHit(int i) { _hitCount += i; }			//플레이어와 충돌 시 카운트 증가 시킬 설정자

	inline bool getDelete() { return _isDelete; }		// _isDelete에 대한 설정자

	inline bool getHead() { return _isSmoke; }
	inline void setHead(bool x) { _isSmoke = x; }

	inline void setFrameX(int x) { _currentFrameX = x; }
};

