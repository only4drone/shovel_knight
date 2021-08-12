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

HRESULT character::init() // ����
{
    IMAGEMANAGER->addFrameImage("ĳ����_���̵�", "image/shovel_character_idle.bmp", 1224, 192, 12, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ����_�޸���", "image/shovel_character_run.bmp", 720, 210, 6, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ����_����1", "image/shovel_character_jump1.bmp", 93, 204, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ����_����2", "image/shovel_character_jump2.bmp", 99, 204, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ����_����", "image/shovel_character_attack.bmp", 900, 210, 4, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ����_��������", "image/shovel_character_jumpattack.bmp", 900, 210, 4, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ����_�����ϴܰ���", "image/shovel_character_jumpbottomattack.bmp", 72, 216, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ����_�ǰ�", "image/shovel_character_hurt.bmp", 105, 234, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ����_����", "image/shovel_character_death.bmp", 333, 204, 3, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ����_��ٸ�", "image/shovel_character_hang.bmp", 150, 96, 2, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ����_��ų", "image/shovel_character_skill.bmp", 252, 192, 2, 2, true, RGB(255, 0, 255));

    _characterImg = IMAGEMANAGER->findImage("ĳ����_���̵�");
    _x = 200;
    _y = 380;
    _state = IDLE;
    _direction = 0;
    _isPixelCollision = true;
    _isPlatformCollision = false;
    _isSandBlockCollision = false;
    _speed = _gravity = _jumpPower = 0;
    _currentHP = _maxHP = 8;
    _currentFrame = _count = 0;
    _damage = 1;
    _hangFrameCount = _platformNum = _sandBlockNum = 0;

    _imgRect = RectMakeCenter(_x, _y, _characterImg->getFrameWidth(), _characterImg->getFrameHeight());
    _collisionRect = RectMakeCenter(_x, _y, 56, 96);

    return S_OK;
}

void character::release()
{
}

void character::update() // ������Ʈ
{
    gravity();
    controll();
    attackRectMake();
    collision();
    imgFrameSetting();

    // ��Ʈ ����
    _imgRect = RectMakeCenter(_x, _y, _characterImg->getFrameWidth(), _characterImg->getFrameHeight());
    _collisionRect = RectMakeCenter(_x, _y, 56, 96);
}

void character::gravity() // ĳ���� �߷� ó��
{
    // ĳ���Ͱ� �߷¹޾Ƽ� �������� ������ �� �̹��� ����
    if (_jumpPower < 0 && _state == JUMP)
        _characterImg = IMAGEMANAGER->findImage("ĳ����_����2");

    // �߷� �� ����
    if (_state == JUMP || _state == JUMPATTACK || _state == JUMPBOTTOMATTACK || _state == HURT || _state == SKILL) // ���� ����, �ǰ� ������ ��
    {
        _jumpPower -= _gravity;
        if (_jumpPower < -18.0f) _jumpPower = -18.0f;
        _y -= _jumpPower;
    }

    // �ǰ� ������ �� �ٶ� ������ �ڷ� �и�
    if (_state == HURT)
    {
        if (_direction == 0) _x -= _mapCamera->getSpeed();
        else _x += _mapCamera->getSpeed();
    }
}

void character::controll() // ĳ���� ��Ʈ��Ű ó��
{
    if (_state != ATTACK && _state != SKILL && _state != HURT && _state != DEATH) // ���� ����, �ǰ� ����, ���� ���°� �ƴ� ��
    {
        // �޸���
        if (KEYMANAGER->isStayKeyDown('A'))
        {
            run(1);
        }
        if (KEYMANAGER->isStayKeyDown('D'))
        {
            run(0);
        }

        // ���̵�
        if (KEYMANAGER->isOnceKeyUp('A'))
        {
            idle(1);
        }
        if (KEYMANAGER->isOnceKeyUp('D'))
        {
            idle(0);
        }

        // ���� �̿�
        for (int i = 0; i < _object->getNPCMAX(); i++)
        {
            RECT temp;
            RECT npc = _object->getNPC(i).rc; // ���� npc ��Ʈ �޾ƿ�
            if (IntersectRect(&temp, &_collisionRect, &npc))
            {
                int npcIndex = i + 1;
                if (KEYMANAGER->isOnceKeyDown('J'))
                {
                    shop(npcIndex); // �浹�� npc�� ���� �̿�
                }
            }
        }

        // ���� �̿� �� �� �� ����
        for (int i = 0; i < _object->getNPCMAX(); i++)
        {
            RECT temp;
            RECT npc = _object->getNPC(i).rc; // ���� npc ��Ʈ �޾ƿ�
            if (KEYMANAGER->isOnceKeyDown('J') && !IntersectRect(&temp, &_collisionRect, &npc)) // �ƹ� npc�� �浹���� �ʾ��� �� ����
            {
                attack();
            }
        }

        // ����
        if (KEYMANAGER->isOnceKeyDown('K') || KEYMANAGER->isOnceKeyDown(VK_SPACE))
        {
            if (_state != JUMP && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK && _state != HANG)
            {
                jump();
            }
        }

        // ���� �ϴ� ����
        if (_state == JUMP) // ���� ����
        {
            if (KEYMANAGER->isStayKeyDown('S'))
            {
                jumpBottomAttack();
            }
        }

        // ��ų ���
        if (KEYMANAGER->isOnceKeyDown('U'))
        {
            skill();
        }

        // ��ٸ� Ÿ��
        for (int i = 0; i < _object->getLadderMax(); i++)
        {
            RECT temp;
            RECT ladder = _object->getLadder(i).rc;

            if (IntersectRect(&temp, &_collisionRect, &ladder)) // ��ٸ��� �浹�� ���¿���~
            {
                if (KEYMANAGER->isStayKeyDown('A') && _state == HANG) // ��ٸ��� ������ ���¿��� �·� ������� �� ��
                {
                    hangOut();
                }

                if (KEYMANAGER->isStayKeyDown('D') && _state == HANG) // ��ٸ��� ������ ���¿��� ��� ������� �� ��
                {
                    hangOut();
                }
                if (KEYMANAGER->isStayKeyDown('W')) // ��ٸ� ����� && ��� �̵� 
                {
                    _x = (ladder.left + ladder.right) / 2;
                    _y -= _mapCamera->getSpeed() / 1.5;
                    hang();
                }
                if (KEYMANAGER->isStayKeyDown('S')) // ��ٸ� ����� && �ϴ� �̵� 
                {
                    _x = (ladder.left + ladder.right) / 2;
                    _y += _mapCamera->getSpeed() / 1.5;
                    hang();
                }
            }

            // ĳ���� �ϴܿ� ��ٸ��� ���� ��� ������ ������ �� �ֵ��� ó��
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

void character::attackRectMake() // ĳ���� ���� ��Ʈ ó��
{
    // ����, ���� ���� �� ��Ʈ ����
    if (_state == ATTACK || _state == JUMPATTACK)
    {
        if (_direction == 0) _attackCollisionRect = RectMakeCenter(_collisionRect.right + 13, _y + 16, 140, 80); // ����
        if (_direction == 1) _attackCollisionRect = RectMakeCenter(_collisionRect.left - 13, _y + 16, 140, 80); // ����
    }

    // ���� �ϴ� ���� ��Ʈ ����
    if (_state == JUMPBOTTOMATTACK)
    {
        _attackCollisionRect = RectMakeCenter(_x, _y + 24, 56, 48);
    }

    // ����, ���� ����, ���� �ϴ� ���� ���°� �ƴϸ� ���� ��Ʈ �ʱ�ȭ
    if (_state != ATTACK && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK)
    {
        _attackCollisionRect = RectMakeCenter(0, 0, 0, 0);
    }
}

void character::collision() // �浹 ó�� ����
{
    pixelCollision();
    platformCollision();
    sandBlockCollision();
    hangCollision();
    bubbleCollision();
    enemyCollision();
    //jewelCollision();
}

void character::pixelCollision() // ĳ���� �ȼ� �浹 ó��
{
    // �ɾ�ٴ� �� �ٴڿ� �ȼ� �浹 �� �Ǹ� �ٴ����� ��������
    if (_state == IDLE || _state == RUN)
    {
        int proveYBottom = _collisionRect.bottom - _mapCamera->getCamY(); // ĳ���� �ٴ��� �˻��ϱ� ���� ����
        int collisionCount = 0;                                           // ĳ���� �浹 ��Ʈ�� �¿����� ��� �浹���� �ʴ��� üũ

        for (int i = proveYBottom; i < proveYBottom + 1; i++)
        {
            if (_isPlatformCollision == true) break; // ��Ʈ �浹 ���� ���� �ȼ� �浹 �ʿ� ������ �극��ũ
            if (_isSandBlockCollision == true) break;

            // ĳ���� �浹 ��Ʈ�� ������ ��, proveYBottom ��ǥ ���� ����Ÿ�� ������ üũ
            if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), _collisionRect.left - _mapCamera->getCamX(), i) != RGB(255, 0, 255))
            {
                collisionCount++;
            }
            // ĳ���� �浹 ��Ʈ�� ������ ��, proveYBottom ��ǥ ���� ����Ÿ�� ������ üũ
            if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), _collisionRect.right - _mapCamera->getCamX(), i) != RGB(255, 0, 255))
            {
                collisionCount++;
            }
            if (collisionCount >= 2) // �浹 ��Ʈ�� �¿����� ��� üũ�Ǹ� �ٴ����� �������� ó��
            {
                _gravity = GRAVITY;
                _state = JUMP;
                imgSetting();
                _isPixelCollision = false;
                break;
            }
        }
    }

    // ���߿� �ִ� ���¿��� ó��
    if (_state == JUMP || _state == JUMPATTACK || _state == JUMPBOTTOMATTACK || _state == HURT)
    {
        // �ٴ� �ȼ� �浹 ó��
        int proveYBottom = _y + ((_collisionRect.bottom - _collisionRect.top) / 2) - _mapCamera->getCamY();

        for (int i = proveYBottom; i < proveYBottom + 10; i++)
        {
            if (_jumpPower > 0) continue;
            // ĳ���� �浹 ��Ʈ�� ������ ��, proveYBottom ��ǥ ���� ����Ÿ�� ������ �浹 ó��
            if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), _collisionRect.left - _mapCamera->getCamX(), i) == RGB(255, 0, 255))
            {
                _y = i - (_collisionRect.bottom - _collisionRect.top) / 2 + _mapCamera->getCamY();
                _gravity = _jumpPower = 0;
                _state = IDLE;
                imgSetting();
                _isPixelCollision = true;
                break;
            }
            // ĳ���� �浹 ��Ʈ�� ������ ��, proveYBottom ��ǥ ���� ����Ÿ�� ������ �浹 ó��
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

        // ��� �ȼ� �浹 ó��
        int proveYTop = _y - ((_collisionRect.bottom - _collisionRect.top) / 2) - _mapCamera->getCamY();

        for (int i = proveYTop; i > proveYTop - 1; i--)
        {
            // ĳ���� �浹 ��Ʈ�� ���� ��, proveYTop ��ǥ ���� ����Ÿ�� ������ �浹 ó��
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
            // ĳ���� �浹 ��Ʈ�� ������ ��, proveYTop ��ǥ ���� ����Ÿ�� ������ �浹 ó��
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

    // ���� �ȼ� �浹 ó��
    if (_state != HANG && _state != DEATH)
    {
        if (_direction == 0) // ������ ���� ���� ��
        {
            // ĳ���� ������ �˻��ϱ� ���� ����
            int proveXRight = _x + ((_collisionRect.right - _collisionRect.left) / 2) - _mapCamera->getCamX();

            for (int i = proveXRight - 1; i < proveXRight + 1; i++)
            {
                // proveXRight ��ǥ ��, ĳ���� �浹 ��Ʈ�� ��� ���� ����Ÿ�� ������ �浹 ó�� 
                if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), i, _y - _mapCamera->getCamY()) == RGB(255, 0, 255))
                {
                    _x = i - (_collisionRect.right - _collisionRect.left) / 2 - _mapCamera->getSpeed() + _mapCamera->getCamX();
                    break;
                }
                // proveXRight ��ǥ ��, ĳ���� �浹 ��Ʈ�� �ϴ� ���� ����Ÿ�� ������ �浹 ó�� 
                if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), i, _collisionRect.bottom - 10 - _mapCamera->getCamY()) == RGB(255, 0, 255))
                {
                    _x = i - (_collisionRect.right - _collisionRect.left) / 2 - _mapCamera->getSpeed() + _mapCamera->getCamX();
                    break;
                }
            }
        }
        else // ���� ���� ���� ��
        {
            // ĳ���� ������ �˻��ϱ� ���� ����
            int proveXLeft = _x - ((_collisionRect.right - _collisionRect.left) / 2) - _mapCamera->getCamX();

            for (int i = proveXLeft + 1; i >= proveXLeft - 1; i--)
            {
                // proveXLeft ��ǥ ��, ĳ���� �浹 ��Ʈ�� ��� ���� ����Ÿ�� ������ �浹 ó�� 
                if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), i, _y - _mapCamera->getCamY()) == RGB(255, 0, 255))
                {
                    _x = i + (_collisionRect.right - _collisionRect.left) / 2 + _mapCamera->getSpeed() + _mapCamera->getCamX();
                    break;
                }
                // proveXLeft ��ǥ ��, ĳ���� �浹 ��Ʈ�� �ϴ� ���� ����Ÿ�� ������ �浹 ó�� 
                if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), i, _collisionRect.bottom - 10 - _mapCamera->getCamY()) == RGB(255, 0, 255))
                {
                    _x = i + (_collisionRect.right - _collisionRect.left) / 2 + _mapCamera->getSpeed() + _mapCamera->getCamX();
                    break;
                }
            }
        }
    }
}

void character::platformCollision() // ĳ���� ��Ʈ �浹 ó��
{
    // ���ǰ� ��Ʈ �浹 ó��
    for (int i = 0; i < _object->getPlatformrMax(); i++)
    {
        if (_isSandBlockCollision == true) break;

        RECT temp;
        RECT platform = _object->getPlatform(i).rc;
        if (IntersectRect(&temp, &_collisionRect, &platform))
        {
            float width = temp.right - temp.left;
            float height = temp.bottom - temp.top;

            if (width > height) // ���� �浹
            {
                _platformNum = i; // ���� � ��ֹ��� �浹�ߴ��� ���

                if (_collisionRect.bottom <= platform.bottom) // �ؿ��� �浹
                {
                    _y -= height;
                    _gravity = _jumpPower = 0; // �߷�, �����Ŀ� �ʱ�ȭ
                    _state = IDLE;
                    imgSetting();
                    _isPlatformCollision = true;
                }
                else // ������ �浹
                {
                    _y += height;
                    _jumpPower = 0;
                }
            }

            if (width <= height) // ���� �浹
            {
                if (_collisionRect.left <= platform.left) // ���ʿ��� �浹
                {
                    _x -= width;
                }
                else // �����ʿ��� �浹
                {
                    _x += width;
                }
            }
        }
    }

    // �ؿ� ��ֹ��� ���ٸ� �߷¹޾� �������� ó��
    if (_isPixelCollision == false && _isSandBlockCollision == false)
    {
        int collisionCount = 0;
        RECT platform = _object->getPlatform(_platformNum).rc;
        POINT check, check2;
        check.x = _collisionRect.left;
        check2.x = _collisionRect.right;
        check.y = check2.y = _collisionRect.bottom + 1;

        if (!PtInRect(&platform, check) && _state == RUN)
        {
            collisionCount++;
        }
        if (!PtInRect(&platform, check2) && _state == RUN)
        {
            collisionCount++;
        }
        if (collisionCount >= 2)
        {
            _gravity = GRAVITY;
            _state = JUMP;
            imgSetting();
            _isPlatformCollision = false;
        }
    }
}

void character::sandBlockCollision()
{
    // ���� ��� ���� ó��
    for (int i = 0; i < _object->getSandBlockMAX(); i++)
    {
        RECT temp;
        RECT sandBlock = _object->getSandBlock(i).rc;
        if (IntersectRect(&temp, &_attackCollisionRect, &sandBlock))
        {
            _object->setSandBlock(i, false); // ������ ���� ��ȣ

            if (_state == JUMPBOTTOMATTACK) // ���� �ϴ� �����̿��� ���
            {
                _jumpPower = JUMPPOWER;
                _gravity = GRAVITY;
            }
        }
    }

    // �����ϰ� ��Ʈ �浹 ó��
    for (int i = 0; i < _object->getSandBlockMAX(); i++)
    {
        if (_isPlatformCollision == true) break;

        RECT temp;
        RECT sandBlock = _object->getSandBlock(i).rc;
        if (IntersectRect(&temp, &_collisionRect, &sandBlock))
        {
            float width = temp.right - temp.left;
            float height = temp.bottom - temp.top;

            if (width > height) // ���� �浹
            {
                _sandBlockNum = i; // ���� � ��ֹ��� �浹�ߴ��� ���

                if (_collisionRect.bottom <= sandBlock.bottom) // �ؿ��� �浹
                {
                    _y -= height;
                    _gravity = _jumpPower = 0; // �߷�, �����Ŀ� �ʱ�ȭ
                    _state = IDLE;
                    imgSetting();
                    _isSandBlockCollision = true;
                }
                else // ������ �浹
                {
                    _y += height;
                    _jumpPower = 0;
                }
            }

            if (width <= height) // ���� �浹
            {
                if (_collisionRect.left <= sandBlock.left) // ���ʿ��� �浹
                {
                    _x -= width;
                }
                else // �����ʿ��� �浹
                {
                    _x += width;
                }
            }
        }
    }

    // �ؿ� ��ֹ��� ���ٸ� �߷¹޾� �������� ó��
    if (_isPixelCollision == false && _isPlatformCollision == false)
    {
        int collisionCount = 0;
        RECT sandBlock = _object->getSandBlock(_sandBlockNum).rc;
        POINT check, check2;
        check.x = _collisionRect.left;
        check2.x = _collisionRect.right;
        check.y = check2.y = _collisionRect.bottom + 1;

        if (!PtInRect(&sandBlock, check) && _state == RUN)
        {
            collisionCount++;
        }
        if (!PtInRect(&sandBlock, check2) && _state == RUN)
        {
            collisionCount++;
        }
        if (collisionCount >= 2)
        {
            _gravity = GRAVITY;
            _state = JUMP;
            imgSetting();
            _isSandBlockCollision = false;
        }
    }
}

void character::hangCollision() // ĳ���� ��ٸ� �浹 ó��
{
    // � ��ٸ� �浹�ߴ��� üũ
    for (int i = 0; i < _object->getLadderMax(); i++)
    {
        RECT temp;
        RECT ladder = _object->getLadder(i).rc;
        if (IntersectRect(&temp, &_collisionRect, &ladder))
        {
            _hangRcNum = i;
        }
    }

    // ��ٸ� �����
    RECT temp;
    RECT ladder = _object->getLadder(_hangRcNum).rc;
    if (!IntersectRect(&temp, &_collisionRect, &ladder))
    {
        if (ladder.top >= _collisionRect.bottom) // ��ٸ��� ����� ����
        {
            _hangRcNum = 0;
            if (_state == HANG)
            {
                _state = IDLE;
                imgSetting();
            }
        }

        if (ladder.bottom <= _collisionRect.top) // ��ٸ��� �غκ� ����
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

void character::bubbleCollision() // ĳ���� ���� �浹 ó��
{
    // ���� ���� ó��
    for (int i = 0; i < _object->getBubbleMAX(); i++)
    {
        RECT temp;
        RECT bubble = _object->getBubble(i).rc;
        if (IntersectRect(&temp, &_attackCollisionRect, &bubble))
        {
            _object->setBubble(i, false); // ���� ���� ��ȣ

            if (_state == JUMPBOTTOMATTACK) // ���� �ϴ� �����̿��� ���
            {
                _jumpPower = JUMPPOWER;
                _gravity = GRAVITY;
            }
        }
    }

    // ���� �ǰ� ó��
    for (int i = 0; i < _object->getBubbleMAX(); i++)
    {
        RECT temp;
        RECT bubble = _object->getBubble(i).rc;
        if (IntersectRect(&temp, &_collisionRect, &bubble))
        {
            if (_state != HURT && _state != JUMPBOTTOMATTACK) hitDamage(1); // �ƴ� �� ������ ����
        }
    }
}

void character::enemyCollision() // ĳ���� ���� �浹 ó��
{
    for (int i = 0; i < _enemyManager->getVEnemy().size(); i++)
    {
        RECT temp;
        RECT enemy = _enemyManager->getVEnemy()[i]->getRect();

        if (IntersectRect(&temp, &_attackCollisionRect, &enemy)) // ���Ϳ��� ���� ó��
        {
            if (_state == JUMPBOTTOMATTACK) // ���� �ϴ� �����̸� ���� �ٽ� Ƣ�� ����
            {
                _jumpPower = JUMPPOWER;
                _gravity = GRAVITY;
            }
        }

        if (IntersectRect(&temp, &_collisionRect, &enemy))  // ���Ϳ��� �ǰ� ó��
        {
            if (_state != HURT && _state != JUMPBOTTOMATTACK) hitDamage(1); 
        }
    }
}

void character::jewelCollision() // ĳ���� ��� �浹 ó��
{
    //for (int i = 0; i < _object->getJewelMax(); i++)
    //{
    //    RECT temp;
    //    RECT jewel = _object->getJewel(i).rc;
    //    if (IntersectRect(&temp, &_collisionRect, &jewel))
    //    {
    //        _
    //    }
    //}
}

void character::imgFrameSetting() // ĳ���� �̹��� ������ ó��
{
    // ������Y �̹��� ����
    _characterImg->setFrameY(_direction);

    // ī��Ʈ�� ���� ��ġ���� ������X ����
    _count++;
    if (_count % 5 == 0)
    {
        // ������ �ʱ�ȭ
        if (_state != HANG) // ��ٸ� ���°� �ƴ� ��(��ٸ��� ����ó����)
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

            // X������ �̹��� ����
            _characterImg->setFrameX(_currentFrame);

            // ��ų ������ ī��Ʈ ����
            if (_state == SKILL) _skillFrameCount++;
        }
    }

    // ���� �ʱ�ȭ
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

    // ���� ���� �ʱ�ȭ
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

    // ���� ��ų �ִϸ��̼��� ���������� ��ų ��� �ʱ�ȭ
    if (_skillFrameCount >= 6)
    {
        _skillFrameCount = 0;
        _state = IDLE;
        imgSetting();
    }

    // ��ٸ� Ÿ�� �̹��� ����(��ٸ� Ÿ��� �̵� �� �Ҷ��� ����� �־�� �ؼ� ���� ó��)
    if (_state == HANG)
    {
        if (_hangFrameCount % 10 == 0) _characterImg->setFrameX(0);
        else if (_hangFrameCount % 19 == 0) _characterImg->setFrameX(1);

        if (_hangFrameCount >= 19) _hangFrameCount = 1;
    }

    // ī��Ʈ �ʱ�ȭ
    if (_count >= 5) _count = 0;
}

void character::imgSetting() // ���¿� ���� �̹��� ó��
{
    // �̹��� ����
    switch (_state)
    {
    case IDLE:
        _characterImg = IMAGEMANAGER->findImage("ĳ����_���̵�");
        break;
    case RUN:
        _characterImg = IMAGEMANAGER->findImage("ĳ����_�޸���");
        break;
    case JUMP:
        _characterImg = IMAGEMANAGER->findImage("ĳ����_����1");
        break;
    case ATTACK:
        _characterImg = IMAGEMANAGER->findImage("ĳ����_����");
        break;
    case JUMPATTACK:
        _characterImg = IMAGEMANAGER->findImage("ĳ����_��������");
        break;
    case JUMPBOTTOMATTACK:
        _characterImg = IMAGEMANAGER->findImage("ĳ����_�����ϴܰ���");
        break;
    case HURT:
        _characterImg = IMAGEMANAGER->findImage("ĳ����_�ǰ�");
        break;
    case DEATH:
        _characterImg = IMAGEMANAGER->findImage("ĳ����_����");
        break;
    case HANG:
        _characterImg = IMAGEMANAGER->findImage("ĳ����_��ٸ�");
        break;
    case SKILL:
        _characterImg = IMAGEMANAGER->findImage("ĳ����_��ų");
        break;
    }

    // ���� �̹����� �°� Ŀ��Ʈ ������ �ʱ�ȭ
    if (_state != IDLE && _state != RUN)
    {
        if (_direction == 0) _currentFrame = 0;
        else if (_direction == 1) _currentFrame = _characterImg->getMaxFrameX();
    }
}

void character::idle(bool direction) // ĳ���� ���̵� ó��
{
    if (_state != JUMP && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK && _state != HANG)
    {
        _state = IDLE;
        imgSetting();
    }

    _direction = direction;
    _speed = 0;
}

void character::run(bool direction) // ĳ���� �޸��� ó��
{
    if (_state != JUMP && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK && _state != HANG)
    {
        _state = RUN;
        imgSetting();
    }

    _direction = direction;
    _speed = _mapCamera->getSpeed();

    if(direction == 1) _x -= _speed;
    else if (direction == 0) _x += _speed;
}

void character::jump() // ĳ���� ���� ó��
{
    _jumpPower = JUMPPOWER;
    _gravity = GRAVITY;
    _state = JUMP;
    imgSetting();
    _isPixelCollision = false;
    _isPlatformCollision = false;
    _isSandBlockCollision = false;
}

void character::attack() // ĳ���� ���� ó��
{
    if (_state != JUMPATTACK)
    {
        if (_state == JUMP || _state == JUMPBOTTOMATTACK) // ���� ����
        {
            _state = JUMPATTACK;
            imgSetting();
        }
        else if (_state == IDLE || _state == RUN)// ���� ���°� �ƴ� ��
        {
            _state = ATTACK;
            imgSetting();
        }
    }
}

void character::jumpBottomAttack() // ĳ���� �ϴ� ���� ó��
{
    _state = JUMPBOTTOMATTACK;
    imgSetting();
}

void character::hang() // ĳ���� ��ٸ� Ÿ�� ó��
{
    _state = HANG;
    imgSetting();
    _hangFrameCount++;
    _gravity = _jumpPower = 0;
}

void character::hangOut() // ĳ���� ��ٸ� ����� ó��
{
    _gravity = GRAVITY;
    _state = JUMP;
    imgSetting();
}

void character::skill() // ĳ���� ��ų ó��
{
    if (SCENEMANAGER->checkFire() == true) // �������� ���� ���� ��
    {
        if (SCENEMANAGER->getMana() >= 5)
        {
            SCENEMANAGER->setMana(SCENEMANAGER->getMana() - 5);
            _state = SKILL;
            imgSetting();

            // fireball() �߻�!!!
        }
    }
}

void character::hitDamage(float damage) // ĳ���� �ǰ� �� ó��
{
    _currentHP -= damage;
    _state = HURT;
    imgSetting();

    // �ǰ� ���ϸ� �ڷ� �и��� ó���� ����
    _jumpPower = JUMPPOWER / 1.3;
    _gravity = GRAVITY;

    //death();
}

void character::death() // ĳ���� ���� ó��
{
    if(_currentHP <= 0)
    {
        _state = DEATH;
        imgSetting();
    }
}

void character::shop(int arrNum) // ĳ���� ���� �̿� ó��
{
    switch (arrNum)
    {
    case 1: // �������� ������
        _ui->talklingManOn();
        break;
    case 2: // �̳� ���
        _ui->fireshopOn();
        break;
    case 3: // �Ӹ� ����
        _ui->goatshopOn();
        break;
    }
}

void character::render() // ĳ���� ����
{
    // ĳ���� �̹��� ����
    _characterImg->frameRender(getMemDC(), _imgRect.left, _imgRect.top);

    // ĳ���� ��Ʈ ����
    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        Rectangle(getMemDC(), _imgRect);                                // �̹��� ��Ʈ
        HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
        HBRUSH oldbrush = (HBRUSH)SelectObject(getMemDC(), brush);
        Rectangle(getMemDC(), _collisionRect);                          // ĳ���� �浹 ��Ʈ(���)
        SelectObject(getMemDC(), oldbrush);
        DeleteObject(brush);
        HBRUSH brush2 = CreateSolidBrush(RGB(255, 0, 0));
        HBRUSH oldbrush2 = (HBRUSH)SelectObject(getMemDC(), brush2);
        Rectangle(getMemDC(), _attackCollisionRect);                    // ĳ���� ���� ��Ʈ(������)
        SelectObject(getMemDC(), oldbrush2);
        DeleteObject(brush2);
    }

    //// ���� ������
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
}


