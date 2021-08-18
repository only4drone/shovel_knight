#include "pch.h"
#include "character.h"
#include "mapCamera.h"
#include "object.h"
#include "uiManager.h"
#include "enemyManager.h"

character::character()
{
}

character::~character()
{
}

HRESULT character::init() // 인잇
{
    IMAGEMANAGER->addFrameImage("캐릭터_아이들", "image/shovel_character_idle.bmp", 1224, 192, 12, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐릭터_달리기", "image/shovel_character_run.bmp", 720, 210, 6, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐릭터_점프1", "image/shovel_character_jump1.bmp", 93, 204, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐릭터_점프2", "image/shovel_character_jump2.bmp", 99, 204, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐릭터_공격", "image/shovel_character_attack.bmp", 900, 210, 4, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐릭터_점프공격", "image/shovel_character_jumpattack.bmp", 900, 210, 4, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐릭터_점프하단공격", "image/shovel_character_jumpbottomattack.bmp", 72, 216, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐릭터_피격", "image/shovel_character_hurt.bmp", 105, 234, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐릭터_죽음", "image/shovel_character_death.bmp", 333, 204, 3, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐릭터_사다리", "image/shovel_character_hang.bmp", 150, 96, 2, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐릭터_스킬", "image/shovel_character_skill.bmp", 252, 192, 2, 2, true, RGB(255, 0, 255));

    _characterImg = IMAGEMANAGER->findImage("캐릭터_아이들");
    _x = 200;
    _y = 380;
    _state = IDLE;
    _direction = 0;
    _isPixelCollision = true;
    _isPlatformCollision = false;
    _isSandBlockCollision = false;
    _isDeath = _isGod = _bossAttack = false;
    _speed = _gravity = _jumpPower = 0;
    _currentHP = _maxHP = 8;
    _currentFrame = _count = _noHitCount = 0;
    _damage = 1;
    _hangFrameCount = _platformNum = _sandBlockNum = _deathFrameCount = 0;

    _imgRect = RectMakeCenter(_x, _y, _characterImg->getFrameWidth(), _characterImg->getFrameHeight());
    _collisionRect = RectMakeCenter(_x, _y, 56, 96);

    _bullet = new hellFire;
    _bullet->init(100, 1000);

    return S_OK;
}

void character::release()
{
}

void character::update() // 업데이트
{
    _bullet->update(); // 파이어볼 업데이트

    gravity();
    controll();
    attackRectMake();
    collision();
    imgFrameSetting();

    // 렉트 갱신
    _imgRect = RectMakeCenter(_x, _y, _characterImg->getFrameWidth(), _characterImg->getFrameHeight());
    _collisionRect = RectMakeCenter(_x, _y, 56, 96);
}

void character::gravity() // 캐릭터 중력 처리
{
    // 캐릭터가 중력받아서 내려가기 시작할 때 이미지 갱신
    if (_jumpPower < 0 && _state == JUMP)
        _characterImg = IMAGEMANAGER->findImage("캐릭터_점프2");

    // 중력 값 적용
    if (_state == JUMP || _state == JUMPATTACK || _state == JUMPBOTTOMATTACK || _state == HURT || _state == SKILL) // 점프 상태, 피격 상태일 때
    {
        _jumpPower -= _gravity;
        if (_jumpPower < -18.0f) _jumpPower = -18.0f;
        _y -= _jumpPower;
    }

    // 피격 상태일 때 바라본 방향의 뒤로 밀림
    if (_state == HURT)
    {
        if (_direction == 0) _x -= _mapCamera->getSpeed();
        else _x += _mapCamera->getSpeed();
    }
}

void character::controll() // 캐릭터 컨트롤키 처리
{
    if (_state != ATTACK && _state != SKILL && _state != HURT && _state != DEATH) // 공격 상태, 피격 상태, 죽음 상태가 아닐 때
    {
        // 달리기
        if (KEYMANAGER->isStayKeyDown('A'))
        {
            run(1);
        }
        if (KEYMANAGER->isStayKeyDown('D'))
        {
            run(0);
        }

        // 아이들
        if (KEYMANAGER->isOnceKeyUp('A'))
        {
            idle(1);
        }
        if (KEYMANAGER->isOnceKeyUp('D'))
        {
            idle(0);
        }

        // 상점 이용
        for (int i = 0; i < _object->getNPCMAX(); i++)
        {
            RECT temp;
            RECT npc = _object->getNPC(i).rc; // 상점 npc 렉트 받아옴
            if (IntersectRect(&temp, &_collisionRect, &npc))
            {
                int npcIndex = i + 1;
                if (KEYMANAGER->isOnceKeyDown('J'))
                {
                    shop(npcIndex); // 충돌된 npc의 상점 이용
                }
            }
        }

        // 상점 이용 안 할 때 공격
        for (int i = 0; i < _object->getNPCMAX(); i++)
        {
            RECT temp;
            RECT npc = _object->getNPC(i).rc; // 상점 npc 렉트 받아옴
            if (KEYMANAGER->isOnceKeyDown('J') && !IntersectRect(&temp, &_collisionRect, &npc)) // 아무 npc랑 충돌되지 않았을 땐 공격
            {
                attack();
            }
        }

        // 점프
        if (KEYMANAGER->isOnceKeyDown('K') || KEYMANAGER->isOnceKeyDown(VK_SPACE))
        {
            if (_state != JUMP && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK && _state != HANG)
            {
                jump();
            }
        }

        // 점프 하단 공격
        if (_state == JUMP) // 점프 상태
        {
            if (KEYMANAGER->isStayKeyDown('S'))
            {
                jumpBottomAttack();
            }
        }

        // 스킬 사용
        if (KEYMANAGER->isOnceKeyDown('U'))
        {
            skill();
        }

        // 사다리 타기
        for (int i = 0; i < _object->getLadderMax(); i++)
        {
            RECT temp;
            RECT ladder = _object->getLadder(i).rc;

            if (IntersectRect(&temp, &_collisionRect, &ladder)) // 사다리랑 충돌된 상태에서~
            {
                if (KEYMANAGER->isStayKeyDown('A') && _state == HANG) // 사다리를 붙잡은 상태에서 좌로 벗어나려고 할 때
                {
                    hangOut();
                }

                if (KEYMANAGER->isStayKeyDown('D') && _state == HANG) // 사다리를 붙잡은 상태에서 우로 벗어나려고 할 때
                {
                    hangOut();
                }
                if (KEYMANAGER->isStayKeyDown('W')) // 사다리 붙잡기 && 상단 이동 
                {
                    _x = (ladder.left + ladder.right) / 2;
                    _y -= _mapCamera->getSpeed() / 1.5;
                    hang();
                }
                if (KEYMANAGER->isStayKeyDown('S')) // 사다리 붙잡기 && 하단 이동 
                {
                    _x = (ladder.left + ladder.right) / 2;
                    _y += _mapCamera->getSpeed() / 1.5;
                    hang();
                }
            }

            // 캐릭터 하단에 사다리가 있을 경우 밑으로 내려갈 수 있도록 처리
            POINT check;
            check.x = _x;
            check.y = _collisionRect.bottom + 10;
            if (PtInRect(&ladder, check))
            {
                if (KEYMANAGER->isStayKeyDown('S') && !IntersectRect(&temp, &_collisionRect, &ladder))
                {
                    _x = (ladder.left + ladder.right) / 2;
                    _y += _mapCamera->getSpeed() / 1.5;
                    hang();
                }
            }
        }
    }
}

void character::attackRectMake() // 캐릭터 공격 렉트 처리
{
    // 공격, 점프 공격 시 렉트 생성
    if (_state == ATTACK || _state == JUMPATTACK)
    {
        if (_direction == 0) _attackCollisionRect = RectMakeCenter(_collisionRect.right + 13, _y + 16, 140, 60); // 변경
        if (_direction == 1) _attackCollisionRect = RectMakeCenter(_collisionRect.left - 13, _y + 16, 140, 60); // 변경
    }

    // 점프 하단 공격 렉트 생성
    if (_state == JUMPBOTTOMATTACK)
    {
        _attackCollisionRect = RectMakeCenter(_x, _y + 24, 56, 48);
    }

    // 공격, 점프 공격, 점프 하단 공격 상태가 아니면 공격 렉트 초기화
    if (_state != ATTACK && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK)
    {
        _attackCollisionRect = RectMakeCenter(0, 0, 0, 0);
    }
}

void character::collision() // 충돌 처리 묶음
{
    bulletCollision();
    pixelCollision();
    platformCollision();
    sandBlockCollision();
    hangCollision();
    bubbleCollision();
    enemyCollision();
    jewelCollision();
    foodCollision();
    npcCollisionOut();
}

void character::pixelCollision() // 캐릭터 픽셀 충돌 처리
{
    // 걸어다닐 때 바닥에 픽셀 충돌 안 되면 바닥으로 떨어진다
    if (_state == IDLE || _state == RUN || _state == SKILL)
    {
        int proveYBottom = _collisionRect.bottom - _mapCamera->getCamY(); // 캐릭터 바닥을 검사하기 위한 변수
        int collisionCount = 0;                                           // 캐릭터 충돌 렉트의 좌우측이 모두 충돌되지 않는지 체크

        for (int i = proveYBottom; i < proveYBottom + 1; i++)
        {
            if (_isPlatformCollision == true) break; // 렉트 충돌 중일 때는 픽셀 충돌 필요 없으니 브레이크
            if (_isSandBlockCollision == true) break;

            // 캐릭터 충돌 렉트의 오른쪽 값, proveYBottom 좌표 값에 마젠타가 없으면 체크
            if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), _collisionRect.left - _mapCamera->getCamX(), i) != RGB(255, 0, 255))
            {
                collisionCount++;
            }
            // 캐릭터 충돌 렉트의 오른쪽 값, proveYBottom 좌표 값에 마젠타가 없으면 체크
            if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), _collisionRect.right - _mapCamera->getCamX(), i) != RGB(255, 0, 255))
            {
                collisionCount++;
            }
            if (collisionCount >= 2) // 충돌 렉트의 좌우측이 모두 체크되면 바닥으로 떨어지는 처리
            {
                _gravity = GRAVITY;
                _state = JUMP;
                imgSetting();
                _isPixelCollision = false;
                break;
            }
        }
    }

    // 공중에 있는 상태에서 처리
    if (_state == JUMP || _state == JUMPATTACK || _state == JUMPBOTTOMATTACK || _state == HURT)
    {
        // 바닥 픽셀 충돌 처리
        int proveYBottom = _y + ((_collisionRect.bottom - _collisionRect.top) / 2) - _mapCamera->getCamY();

        for (int i = proveYBottom; i < proveYBottom + 10; i++)
        {
            if (_jumpPower > 0) continue;
            // 캐릭터 충돌 렉트의 왼쪽 값, proveYBottom 좌표 값에 마젠타가 있으면 충돌 처리
            if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), _collisionRect.left - _mapCamera->getCamX(), i) == RGB(255, 0, 255))
            {
                _y = i - (_collisionRect.bottom - _collisionRect.top) / 2 + _mapCamera->getCamY();
                _gravity = _jumpPower = 0;
                _state = IDLE;
                imgSetting();
                _isPixelCollision = true;
                break;
            }
            // 캐릭터 충돌 렉트의 오른쪽 값, proveYBottom 좌표 값에 마젠타가 있으면 충돌 처리
            if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), _collisionRect.right - _mapCamera->getCamX(), i) == RGB(255, 0, 255))
            {
                _y = i - (_collisionRect.bottom - _collisionRect.top) / 2 + _mapCamera->getCamY();
                _gravity = _jumpPower = 0;
                _state = IDLE;
                imgSetting();
                _isPixelCollision = true;
                break;
            }
        }

        // 상단 픽셀 충돌 처리
        int proveYTop = _y - ((_collisionRect.bottom - _collisionRect.top) / 2) - _mapCamera->getCamY();

        for (int i = proveYTop; i > proveYTop - 5; i--)
        {
            // 캐릭터 충돌 렉트의 왼쪽 값, proveYTop 좌표 값에 마젠타가 있으면 충돌 처리
            if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), _collisionRect.left - _mapCamera->getCamX(), i) == RGB(255, 0, 255))
            {
                _y = i + (_collisionRect.bottom - _collisionRect.top) / 2 + _mapCamera->getCamY() + 3;
                if (_jumpPower > 0) _jumpPower = 0;
                _gravity = GRAVITY;
                _state = JUMP;
                imgSetting();
                _isPixelCollision = false;
                break;
            }
            // 캐릭터 충돌 렉트의 오른쪽 값, proveYTop 좌표 값에 마젠타가 있으면 충돌 처리
            if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), _collisionRect.right - _mapCamera->getCamX(), i) == RGB(255, 0, 255))
            {
                _y = i + (_collisionRect.bottom - _collisionRect.top) / 2 + _mapCamera->getCamY() + 3;
                if (_jumpPower > 0) _jumpPower = 0;
                _gravity = GRAVITY;
                _state = JUMP;
                imgSetting();
                _isPixelCollision = false;
                break;
            }
        }
    }

    // 벽면 픽셀 충돌 처리
    if (_state != HANG && _state != DEATH)
    {
        if (_direction == 0) // 오른쪽 보고 있을 때
        {
            // 캐릭터 우측을 검사하기 위한 변수
            int proveXRight = _x + ((_collisionRect.right - _collisionRect.left) / 2) - _mapCamera->getCamX();

            for (int i = proveXRight - 1; i < proveXRight + 5; i++)
            {
                // proveXRight 좌표 값, 캐릭터 충돌 렉트의 상단 값에 마젠타가 있으면 충돌 처리 
                if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), i, _y - _mapCamera->getCamY()) == RGB(255, 0, 255))
                {
                    _x = i - (_collisionRect.right - _collisionRect.left) / 2 - _mapCamera->getSpeed() + _mapCamera->getCamX();
                    break;
                }
                // proveXRight 좌표 값, 캐릭터 충돌 렉트의 하단 값에 마젠타가 있으면 충돌 처리 
                if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), i, _collisionRect.bottom - 10 - _mapCamera->getCamY()) == RGB(255, 0, 255))
                {
                    _x = i - (_collisionRect.right - _collisionRect.left) / 2 - _mapCamera->getSpeed() + _mapCamera->getCamX();
                    break;
                }
            }
        }
        else // 왼쪽 보고 있을 때
        {
            // 캐릭터 좌측을 검사하기 위한 변수
            int proveXLeft = _x - ((_collisionRect.right - _collisionRect.left) / 2) - _mapCamera->getCamX();

            for (int i = proveXLeft + 1; i >= proveXLeft - 1; i--)
            {
                // proveXLeft 좌표 값, 캐릭터 충돌 렉트의 상단 값에 마젠타가 있으면 충돌 처리 
                if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), i, _y - _mapCamera->getCamY()) == RGB(255, 0, 255))
                {
                    _x = i + (_collisionRect.right - _collisionRect.left) / 2 + _mapCamera->getSpeed() + _mapCamera->getCamX();
                    break;
                }
                // proveXLeft 좌표 값, 캐릭터 충돌 렉트의 하단 값에 마젠타가 있으면 충돌 처리 
                if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), i, _collisionRect.bottom - 10 - _mapCamera->getCamY()) == RGB(255, 0, 255))
                {
                    _x = i + (_collisionRect.right - _collisionRect.left) / 2 + _mapCamera->getSpeed() + _mapCamera->getCamX();
                    break;
                }
            }
        }
    }

    // 캐릭터가 가시나 낭떠러지 충돌 시 죽음 처리
    int proveYBottom = _collisionRect.bottom - _mapCamera->getCamY();
    for (int i = proveYBottom; i < proveYBottom + 10; i++)
    {
        if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), _x - _mapCamera->getCamX(), i) == RGB(0, 0, 255))
        {
            hitDamage(8);
        }
    }
}

void character::platformCollision() // 캐릭터 발판 충돌 처리
{
    // 밑에 장애물이 없다면 중력받아 떨어지는 처리
    if (_isPixelCollision == false && _isSandBlockCollision == false) // 픽셀, 샌드블록 충돌 아닐 때
    {
        int collisionCount = 0;
        RECT platform = _object->getPlatform(_platformNum).rc;
        POINT check, check2, check3;
        check.x = _collisionRect.left;
        check2.x = _collisionRect.right;
        check.y = check2.y = _collisionRect.bottom;
        check3.x = _x;
        check3.y = _collisionRect.bottom + 15;
        if (PtInRect(&platform, check3)) // 만약 밑에 발판이 있다면 떨어지지 않음(움직이는 발판때문에 처리)
        {
            if (KEYMANAGER->isStayKeyDown('D') || KEYMANAGER->isStayKeyDown('A')) _state = RUN;
            else if (KEYMANAGER->isStayKeyDown('J')) _state = ATTACK;
            else _state = IDLE;
            imgSetting();
            _y += _mapCamera->getSpeed();
        }
        else
        {
            if (!PtInRect(&platform, check) && (_state == RUN || _state == IDLE || _state == SKILL)) // 좌측 체크
            {
                collisionCount++;
            }
            if (!PtInRect(&platform, check2) && (_state == RUN || _state == IDLE || _state == SKILL)) // 우측 체크
            {
                collisionCount++;
            }
            if (collisionCount >= 2) // 양쪽 모두 체크되면 떨어져라
            {
                _gravity = GRAVITY;
                _state = JUMP;
                imgSetting();
                _isPlatformCollision = false;
            }
        }
    }

    // 발판과 렉트 충돌 처리
    for (int i = 0; i < _object->getPlatformrMax(); i++)
    {
        if (_isSandBlockCollision == true) break; // 샌드 블록에 닿아있을 땐 브레이크

        RECT temp;
        RECT platform = _object->getPlatform(i).rc;
        if (IntersectRect(&temp, &_collisionRect, &platform))
        {
            float width = temp.right - temp.left;
            float height = temp.bottom - temp.top;

            if (width > height) // 상하 충돌
            {
                _platformNum = i; // 현재 어떤 장애물에 충돌했는지 기록

                if (_collisionRect.bottom <= platform.bottom) // 밑에서 충돌
                {
                    _y -= height;
                    _gravity = _jumpPower = 0; // 중력, 점프파워 초기화
                    if (KEYMANAGER->isStayKeyDown('D') || KEYMANAGER->isStayKeyDown('A')) _state = RUN;
                    else if (KEYMANAGER->isStayKeyDown('J')) _state = ATTACK;
                    else _state = IDLE;
                    imgSetting();
                    _isPlatformCollision = true;

                    if (_object->getPlatform(i).index == 1 && _object->getPlatform(i).isDirection == true) _x += _mapCamera->getSpeed();
                    if (_object->getPlatform(i).index == 1 && _object->getPlatform(i).isDirection == false) _x -= _mapCamera->getSpeed();
                    if (_object->getPlatform(i).index == 2 && _object->getPlatform(i).isDirection == true) _y -= _mapCamera->getSpeed();
                    if (_object->getPlatform(i).index == 2 && _object->getPlatform(i).isDirection == false) _y -= _mapCamera->getSpeed();

                    if (KEYMANAGER->isStayKeyDown('K') || KEYMANAGER->isStayKeyDown(VK_SPACE)) // 점프 실행
                    {
                        jump();
                    }
                }
                else // 위에서 충돌
                {
                    _y += height;
                    _jumpPower = 0;
                }
            }

            if (width <= height) // 옆면 충돌
            {
                if (_collisionRect.left <= platform.left) // 왼쪽에서 충돌
                {
                    _x -= width;
                }
                else // 오른쪽에서 충돌
                {
                    _x += width;
                }
            }
        }
    }
}

void character::sandBlockCollision() // 캐릭터 샌드블록 충돌 처리
{
    // 샌드 블록 공격 처리
    for (int i = 0; i < _object->getSandBlockMAX(); i++)
    {
        RECT temp;
        RECT sandBlock = _object->getSandBlock(i).rc;
        if (IntersectRect(&temp, &_attackCollisionRect, &sandBlock))
        {
            _object->setSandBlock(i, false); // 샌드블록 제거 신호

            if (_state == JUMPBOTTOMATTACK) // 점프 하단 공격이였을 경우
            {
                _jumpPower = JUMPPOWER;
                _gravity = GRAVITY;
            }
        }
    }

    // 샌드블록과 렉트 충돌 처리
    for (int i = 0; i < _object->getSandBlockMAX(); i++)
    {
        if (_isPlatformCollision == true) break; // 발판에 닿아있을 땐 브레이크

        RECT temp;
        RECT sandBlock = _object->getSandBlock(i).rc;
        if (IntersectRect(&temp, &_collisionRect, &sandBlock))
        {
            float width = temp.right - temp.left;
            float height = temp.bottom - temp.top;

            if (width > height) // 상하 충돌
            {
                _sandBlockNum = i; // 현재 어떤 장애물에 충돌했는지 기록

                if (_collisionRect.bottom <= sandBlock.bottom) // 밑에서 충돌
                {
                    _y -= height;
                    _gravity = _jumpPower = 0; // 중력, 점프파워 초기화
                    _state = IDLE;
                    imgSetting();
                    _isSandBlockCollision = true;
                }
                else // 위에서 충돌
                {
                    _y += height;
                    _jumpPower = 0;
                }
            }

            if (width <= height) // 옆면 충돌
            {
                if (_collisionRect.left <= sandBlock.left) // 왼쪽에서 충돌
                {
                    _x -= width;
                }
                else // 오른쪽에서 충돌
                {
                    _x += width;
                }
            }
        }
    }

    // 밑에 장애물이 없다면 중력받아 떨어지는 처리
    if (_isPixelCollision == false && _isPlatformCollision == false) // 픽셀, 발판 충돌 아닐 때
    {
        int collisionCount = 0;
        RECT sandBlock = _object->getSandBlock(_sandBlockNum).rc;
        POINT check, check2;
        check.x = _collisionRect.left;
        check2.x = _collisionRect.right;
        check.y = check2.y = _collisionRect.bottom + 1;

        if (!PtInRect(&sandBlock, check) && _state == RUN) // 좌측 체크
        {
            collisionCount++;
        }
        if (!PtInRect(&sandBlock, check2) && _state == RUN) // 우측 체크
        {
            collisionCount++;
        }
        if (collisionCount >= 2) // 양쪽 모두 체크되면 떨어져라
        {
            _gravity = GRAVITY;
            _state = JUMP;
            imgSetting();
            _isSandBlockCollision = false;
        }
    }
}

void character::hangCollision() // 캐릭터 사다리 충돌 처리
{
    // 어떤 사다리 충돌했는지 체크
    for (int i = 0; i < _object->getLadderMax(); i++)
    {
        RECT temp;
        RECT ladder = _object->getLadder(i).rc;
        if (IntersectRect(&temp, &_collisionRect, &ladder))
        {
            _hangRcNum = i;
        }
    }

    // 사다리 벗어나면
    RECT temp;
    RECT ladder = _object->getLadder(_hangRcNum).rc;
    if (!IntersectRect(&temp, &_collisionRect, &ladder))
    {
        if (ladder.top >= _collisionRect.bottom) // 사다리의 꼭대기 도착
        {
            _hangRcNum = 0;
            if (_state == HANG)
            {
                _state = IDLE;
                imgSetting();
            }
        }

        if (ladder.bottom <= _collisionRect.top) // 사다리의 밑부분 도착
        {
            _hangRcNum = 0;
            if (_state == HANG)
            {
                _state = JUMP;
                imgSetting();
                _gravity = GRAVITY;
            }
        }
    }
}

void character::bubbleCollision() // 캐릭터 버블 충돌 처리
{
    // 버블 공격 처리
    for (int i = 0; i < _object->getBubbleMAX(); i++)
    {
        RECT temp;
        RECT bubble = _object->getBubble(i).rc;
        if (IntersectRect(&temp, &_attackCollisionRect, &bubble))
        {
            _object->setBubble(i, false); // 버블 제거 신호

            if (_state == JUMPBOTTOMATTACK) // 점프 하단 공격이였을 경우
            {
                _jumpPower = JUMPPOWER;
                _gravity = GRAVITY;
            }
        }
    }

    // 버블 피격 처리
    for (int i = 0; i < _object->getBubbleMAX(); i++)
    {
        RECT temp;
        RECT bubble = _object->getBubble(i).rc;
        if (IntersectRect(&temp, &_collisionRect, &bubble))
        {
            if (_state != HURT && _state != JUMPBOTTOMATTACK) hitDamage(1); // 아닐 땐 데미지 받음
        }
    }
}

void character::enemyCollision() // 캐릭터 몬스터 충돌 처리
{
    if (_state != DEATH)
    {
        for (int i = 0; i < _enemyManager->getVEnemy().size(); i++)
        {
            RECT temp;
            RECT enemy = _enemyManager->getVEnemy()[i]->getRect();
            RECT enemyBody = _enemyManager->getVEnemy()[i]->getbodyRect();
            RECT beam = _enemyManager->getVEnemy()[i]->getLazerRect();

            // 몬스터에게 공격했을 때~
            if (IntersectRect(&temp, &_attackCollisionRect, &enemy) || IntersectRect(&temp, &_attackCollisionRect, &enemyBody))
            {
                if (_state == JUMPBOTTOMATTACK) // 점프 하단 공격이면 위로 다시 튀어 오름
                {
                    _jumpPower = JUMPPOWER;
                    _gravity = GRAVITY;
                }
            }

            // 보스 몬스터 공격했을 때 피 깍임
            if (IntersectRect(&temp, &_attackCollisionRect, &enemy))
            {
                if (_enemyManager->getVEnemy()[i]->getEnemyName() == "bugDragon")
                {
                    if (_bossAttack == false || _state == JUMPBOTTOMATTACK)
                    {
                        SCENEMANAGER->setBossHp(SCENEMANAGER->getBossHp() - 1);
                        _bossAttack = true;
                    }
                }
            }

            // 보스 몬스터 빔 쏜 공격 피격 처리
            if (IntersectRect(&temp, &_collisionRect, &beam))
            {
                if (_state != HURT && _state != DEATH) hitDamage(1);
            }

            // 몬스터 몸통 피격 처리
            if (IntersectRect(&temp, &_collisionRect, &enemy))
            {
                if (_state != HURT && _state != JUMPBOTTOMATTACK && _state != DEATH) hitDamage(1);
            }

            // 용 몸통에 피격 처리
            if (IntersectRect(&temp, &_collisionRect, &enemyBody))
            {
                if (_state != HURT && _state != JUMPBOTTOMATTACK && _state != DEATH) hitDamage(1);
            }
        }
    }
}

void character::jewelCollision() // 캐릭터 쥬얼 충돌 처리
{
    for (int i = 0; i < _object->getJewelMAX(); i++)
    {
        RECT temp;
        RECT jewel = _object->getJewel(i).rc;
        if (IntersectRect(&temp, &_collisionRect, &jewel))
        {
            if (_object->getJewel(i).index == 12) SCENEMANAGER->setGold(SCENEMANAGER->getGold() + 500); // 500원 보석
            if (_object->getJewel(i).index == 13) SCENEMANAGER->setGold(SCENEMANAGER->getGold() + 100); // 100원 동전

            _object->setJewel(i, false); // 쥬얼 제거
        }
    }
}

void character::foodCollision() // 캐릭터 음식 충돌 처리
{
    for (int i = 0; i < _object->getFoodMAX(); i++)
    {
        RECT temp;
        RECT food = _object->getFood(i).rc;
        if (IntersectRect(&temp, &_collisionRect, &food))
        {
            if (_object->getFood(i).index == 2)
            {
                _currentHP += 4;                                       // 체력 4 회복
                if (_currentHP > 8) _currentHP = 8;

                SCENEMANAGER->setMana(SCENEMANAGER->getMana() + 50);   // 마나 50 회복
                if (SCENEMANAGER->getMana() > 100) SCENEMANAGER->setMana(100);
            }

            _object->setFood(i, false); // 음식 제거
        }
    }
}

void character::bulletCollision() // 파이어볼 충돌 처리
{
    for (int i = 0; i < _bullet->getVBullet().size(); i++)
    {
        for (int j = 0; j < _enemyManager->getVEnemy().size(); j++)
        {
            RECT temp;
            RECT bulletRect = _bullet->getVBullet()[i].rc;
            RECT enemyRect = _enemyManager->getVEnemy()[j]->getRect();

            if (IntersectRect(&temp, &bulletRect, &enemyRect) && _enemyManager->getVEnemy()[j]->getEnemyName() == "bugDragon")
            {
                _bullet->removeMissile(i);
                SCENEMANAGER->setBossHp(SCENEMANAGER->getBossHp() - 1);
                _enemyManager->getVEnemy()[j]->setHit(1);
                _enemyManager->getVEnemy()[j]->setHead(true);
                _enemyManager->getVEnemy()[j]->setDefense(true);
                _bossAttack = true;

                break;
            }
            
            if (IntersectRect(&temp, &bulletRect, &enemyRect))
            {
                _bullet->removeMissile(i);
                _enemyManager->getVEnemy()[j]->setHit(1);
                _enemyManager->getVEnemy()[j]->setHead(true);
                _enemyManager->getVEnemy()[j]->setDefense(true);

                break;
            }
        }
    }
}

void character::npcCollisionOut() // NPC와 거리가 멀어지면 UI 죵료 처리
{
    if (_ui->getTalkOpen() == true)
    {
        _distance = getDistance(_object->getNPC(1).x, _object->getNPC(1).y, _x - _mapCamera->getCamX(), _y - _mapCamera->getCamY());
        if (_distance > 600) _ui->talklingManOff();
    }
    else if (_ui->getFireShopOpen() == true)
    {
        _distance = getDistance(_object->getNPC(2).x, _object->getNPC(2).y, _x - _mapCamera->getCamX(), _y - _mapCamera->getCamY());
        if (_distance > 1100) _ui->fireshopOff();
    }
    else if (_ui->getGoatShopOpen() == true)
    {
        _distance = getDistance(_object->getNPC(3).x, _object->getNPC(3).y, _x - _mapCamera->getCamX(), _y - _mapCamera->getCamY());
        if (_distance < 6600) _ui->goatshopOff();
    }
}

void character::imgFrameSetting() // 캐릭터 이미지 프레임 처리
{
    // 무적 프레임
    if (_isGod == true)
    {
        _noHitCount++;
        if (_noHitCount >= 100)
        {
            _noHitCount = 0;
            _isGod = false;
        }
    }

    // 캐릭터 데스 처리 체크
    if (_currentHP <= 0)
    {
        if (_isPixelCollision == true || _isSandBlockCollision == true || _isPlatformCollision == true) death();
    }

    // 죽었을 때만 예외로 천천히 프레임 진행시키려고!
    int frameSet;
    if (_isDeath == false) frameSet = 5;
    else frameSet = 50;

    // 프레임Y 이미지 갱신
    _characterImg->setFrameY(_direction);

    // 카운트가 일정 수치마다 프레임X 갱신
    _count++;
    if (_count % frameSet == 0)
    {
        // 프레임 초기화
        if (_state != HANG) // 사다리 상태가 아닐 때(사다리를 예외처리함)
        {
            if (_direction == 0)
            {
                _currentFrame++;
                if (_currentFrame > _characterImg->getMaxFrameX()) _currentFrame = 0;
            }
            else
            {
                _currentFrame--;
                if (_currentFrame < 0) _currentFrame = _characterImg->getMaxFrameX();
            }

            // X프레임 이미지 갱신
            _characterImg->setFrameX(_currentFrame);

            // 스킬 프레임 카운트 증가
            if (_state == SKILL) _skillFrameCount++;
        }
    }

    // 공격 초기화
    if (_state == ATTACK)
    {
        if (_direction == 0)
        {
            if (_currentFrame == _characterImg->getMaxFrameX())
            {
                _state = IDLE;
                imgSetting();
            }
        }
        else
        {
            if (_currentFrame == 0)
            {
                _state = IDLE;
                imgSetting();
            }
        }
    }

    // 점프 공격 초기화
    if (_state == JUMPATTACK)
    {
        if (_direction == 0)
        {
            if (_currentFrame == _characterImg->getMaxFrameX())
            {
                _state = JUMP;
                imgSetting();
            }
        }
        else
        {
            if (_currentFrame == 0)
            {
                _state = JUMP;
                imgSetting();
            }
        }
    }

    // 일정 스킬 애니메이션을 진행했으면 스킬 모션 초기화
    if (_skillFrameCount >= 6)
    {
        _skillFrameCount = 0;
        _state = IDLE;
        imgSetting();
    }

    // 사다리 타기 이미지 갱신(사다리 타기는 이동 안 할때는 붙잡고 있어야 해서 예외 처리)
    if (_state == HANG)
    {
        if (_hangFrameCount % 10 == 0) _characterImg->setFrameX(0);
        else if (_hangFrameCount % 19 == 0) _characterImg->setFrameX(1);

        if (_hangFrameCount >= 19) _hangFrameCount = 1;
    }

    // 카운트 초기화
    if (_count >= frameSet) _count = 0;
}

void character::imgSetting() // 상태에 따라 이미지 처리
{
    // 이미지 변경
    switch (_state)
    {
    case IDLE:
        _characterImg = IMAGEMANAGER->findImage("캐릭터_아이들");
        break;
    case RUN:
        _characterImg = IMAGEMANAGER->findImage("캐릭터_달리기");
        break;
    case JUMP:
        _characterImg = IMAGEMANAGER->findImage("캐릭터_점프1");
        break;
    case ATTACK:
        _characterImg = IMAGEMANAGER->findImage("캐릭터_공격");
        break;
    case JUMPATTACK:
        _characterImg = IMAGEMANAGER->findImage("캐릭터_점프공격");
        break;
    case JUMPBOTTOMATTACK:
        _characterImg = IMAGEMANAGER->findImage("캐릭터_점프하단공격");
        break;
    case HURT:
        _characterImg = IMAGEMANAGER->findImage("캐릭터_피격");
        break;
    case DEATH:
        _characterImg = IMAGEMANAGER->findImage("캐릭터_죽음");
        break;
    case HANG:
        _characterImg = IMAGEMANAGER->findImage("캐릭터_사다리");
        break;
    case SKILL:
        _characterImg = IMAGEMANAGER->findImage("캐릭터_스킬");
        break;
    }

    // 현재 이미지에 맞게 커런트 프레임 초기화
    if (_state != IDLE && _state != RUN)
    {
        if (_direction == 0) _currentFrame = 0;
        else if (_direction == 1) _currentFrame = _characterImg->getMaxFrameX();
    }
}

void character::idle(bool direction) // 캐릭터 아이들 처리
{
    if (_state != JUMP && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK && _state != HANG)
    {
        _state = IDLE;
        imgSetting();
    }

    _direction = direction;
    _speed = 0;
}

void character::run(bool direction) // 캐릭터 달리기 처리
{
    if (_state != JUMP && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK && _state != HANG)
    {
        _state = RUN;
        imgSetting();
    }

    _direction = direction;
    _speed = _mapCamera->getSpeed();

    if (direction == 1) _x -= _speed;
    else if (direction == 0) _x += _speed;
}

void character::jump() // 캐릭터 점프 처리
{
    _jumpPower = JUMPPOWER;
    _gravity = GRAVITY;
    _state = JUMP;
    imgSetting();
    _isPixelCollision = false;
    _isPlatformCollision = false;
    _isSandBlockCollision = false;
}

void character::attack() // 캐릭터 공격 처리
{
    _bossAttack = false;

    if (_state != JUMPATTACK)
    {
        if (_state == JUMP || _state == JUMPBOTTOMATTACK) // 점프 상태
        {
            _state = JUMPATTACK;
            imgSetting();
        }
        else if (_state == IDLE || _state == RUN)// 점프 상태가 아닐 때
        {
            _state = ATTACK;
            imgSetting();
        }
    }
}

void character::jumpBottomAttack() // 캐릭터 하단 공격 처리
{
    _state = JUMPBOTTOMATTACK;
    imgSetting();
}

void character::hang() // 캐릭터 사다리 타기 처리
{
    _state = HANG;
    imgSetting();
    _hangFrameCount++;
    _gravity = _jumpPower = 0;
}

void character::hangOut() // 캐릭터 사다리 벗어나는 처리
{
    _gravity = GRAVITY;
    _state = JUMP;
    imgSetting();
}

void character::skill() // 캐릭터 스킬 처리
{
    if (SCENEMANAGER->checkFire() == true) // 불지팡이 보유 중일 때
    {
        if (SCENEMANAGER->getMana() >= 5)
        {
            SCENEMANAGER->setMana(SCENEMANAGER->getMana() - 5);
            _state = SKILL;
            imgSetting();
            _bossAttack = false;
            if (_direction == 0) _bullet->fire(_x, _y, 0);
            else _bullet->fire(_x, _y, PI);
        }
    }
}

void character::hitDamage(float damage) // 캐릭터 피격 시 처리
{
    if (_state != DEATH) // 죽음 상태가 아닐 때
    {
        if (_isGod == false) // 무적 상태에서는 노히트
        {
            _currentHP -= damage;
            _state = HURT;
            imgSetting();

            _isPlatformCollision = false;
            _isSandBlockCollision = false;
            _isPixelCollision = false;
            _isGod = true;

            // 피격 당하면 뒤로 밀리는 처리를 위해
            _jumpPower = JUMPPOWER / 1.3;
            _gravity = GRAVITY;
        }
    }
}

void character::death() // 캐릭터 죽음 처리
{
    if (_state != DEATH)
    {
        _state = DEATH;
        imgSetting();
        _isDeath = true;
    }

    if (_direction == 0 && _currentFrame >= _characterImg->getMaxFrameX())
    {
        _deathFrameCount++;
        if (_deathFrameCount >= 50) SCENEMANAGER->changeScene("gameover");
    }
    if (_direction == 1 && _currentFrame <= 0)
    {
        _deathFrameCount++;
        if (_deathFrameCount >= 50) SCENEMANAGER->changeScene("gameover");
    }

}

void character::shop(int arrNum) // 캐릭터 상점 이용 처리
{
    if (_ui->getTalkOpen() == false && _ui->getFireShopOpen() == false && _ui->getGoatShopOpen() == false) // 아무 상점도 열려 있지 않을 때
    {
        switch (arrNum)
        {
        case 1: // 대장장이 아저쒸
            _ui->talklingManOn();
            break;
        case 2: // 미녀 언니
            _ui->fireshopOn();
            break;
        case 3: // 앙마 염소
            _ui->goatshopOn();
            break;
        }
    }
}

void character::render() // 캐릭터 렌더
{
    _bullet->render();

    // 캐릭터 이미지 렌더
    _characterImg->frameRender(getMemDC(), _imgRect.left, _imgRect.top);

    // 캐릭터 렉트 렌더
    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        Rectangle(getMemDC(), _imgRect);                                // 이미지 렉트
        HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
        HBRUSH oldbrush = (HBRUSH)SelectObject(getMemDC(), brush);
        Rectangle(getMemDC(), _collisionRect);                          // 캐릭터 충돌 렉트(녹색)
        SelectObject(getMemDC(), oldbrush);
        DeleteObject(brush);
        HBRUSH brush2 = CreateSolidBrush(RGB(255, 0, 0));
        HBRUSH oldbrush2 = (HBRUSH)SelectObject(getMemDC(), brush2);
        Rectangle(getMemDC(), _attackCollisionRect);                    // 캐릭터 공격 렉트(빨강색)
        SelectObject(getMemDC(), oldbrush2);
        DeleteObject(brush2);
    }

    //// 현재 프레임
    char str[128];
    sprintf_s(str, "_currentFrame : %d", _currentFrame);
    TextOut(getMemDC(), 0, 220, str, strlen(str));

    sprintf_s(str, "_state : %d", _state);
    TextOut(getMemDC(), 0, 240, str, strlen(str));

    sprintf_s(str, "_direction : %d", _direction);
    TextOut(getMemDC(), 0, 160, str, strlen(str));

    sprintf_s(str, "_charcterX : %d", (int)_x);
    TextOut(getMemDC(), 0, 180, str, strlen(str));

    sprintf_s(str, "_charcterY : %d", (int)_y);
    TextOut(getMemDC(), 0, 200, str, strlen(str));

    sprintf_s(str, "_jumpPower : %f", _jumpPower);
    TextOut(getMemDC(), 0, 260, str, strlen(str));

    sprintf_s(str, "_gravity : %f", _gravity);
    TextOut(getMemDC(), 0, 280, str, strlen(str));

    sprintf_s(str, "_platform : %d", _isPlatformCollision);
    TextOut(getMemDC(), 0, 300, str, strlen(str));

    sprintf_s(str, "_sandBlock : %d", _isSandBlockCollision);
    TextOut(getMemDC(), 0, 320, str, strlen(str));

    sprintf_s(str, "_pixel : %d", _isPixelCollision);
    TextOut(getMemDC(), 0, 340, str, strlen(str));

    sprintf_s(str, "_distance : %f", _distance);
    TextOut(getMemDC(), 0, 360, str, strlen(str));
}


