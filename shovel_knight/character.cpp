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
    _isRectCollision = false;
    _speed = _gravity = _jumpPower = 0;
    _currentHP = _maxHP = 8;
    _currentFrame = _count = 0;
    _damage = 1;
    _hangFrameCount = _rcNum = 0;

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
    pixelCollision();
    rectCollision();
    attackRect();
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
        if (_jumpPower < -20.0f) _jumpPower = -20.0f;
        _y -= _jumpPower;
        _jumpPower -= _gravity;
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

void character::pixelCollision() // ĳ���� �ȼ� �浹 ó��
{
    // �ɾ�ٴ� �� �ٴڿ� �ȼ� �浹 �� �Ǹ� �ٴ����� ��������
    if (_state == IDLE || _state == RUN)
    {
        int proveYBottom = _collisionRect.bottom - _mapCamera->getCamY(); // ĳ���� �ٴ��� �˻��ϱ� ���� ����
        int collisionCount = 0;                                           // ĳ���� �浹 ��Ʈ�� �¿����� ��� �浹���� �ʴ��� üũ

        for (int i = proveYBottom; i < proveYBottom + 1; i++)
        {
            if (_isRectCollision == true) break; // ��Ʈ �浹 ���� ���� �ȼ� �浹 �ʿ� ������ �극��ũ

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

void character::rectCollision() // ĳ���� ��Ʈ �浹 ó��
{
    // ��ֹ��� ��Ʈ �浹 ó��
    for (int i = 0; i < _object->getPlatformrMax(); i++)
    {
        RECT temp;
        RECT platform = _object->getPlatform(i).rc;
        if (IntersectRect(&temp, &_collisionRect, &platform))
        {
            float width = temp.right - temp.left;
            float height = temp.bottom - temp.top;

            if (width > height) // ���� �浹
            {
                _rcNum = i; // ���� � ��ֹ��� �浹�ߴ��� ���

                if (_collisionRect.bottom <= platform.bottom) // �ؿ��� �浹
                {
                    _y -= height;
                    _gravity = _jumpPower = 0; // �߷�, �����Ŀ� �ʱ�ȭ
                    _state = IDLE;
                    imgSetting();
                    _isRectCollision = true;
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
    if (_isPixelCollision == false)
    {
        RECT platform = _object->getPlatform(_rcNum).rc;
        POINT check;
        check.x = _x;
        check.y = _collisionRect.bottom + 1;

        if (!PtInRect(&platform, check) && _state == RUN)
        {
            _gravity = GRAVITY;
            _state = JUMP;
            imgSetting();
            _isRectCollision = false;
        }
    }

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

    //// �ǰ� �׽�Ʈ�� ��Ʈ
    //RECT temp2;
    //if (IntersectRect(&temp2, &_collisionRect, &_attackRc))
    //{
    //    if (_state == JUMPBOTTOMATTACK) // �ϴ� ������ ���� ���� �ٽ� Ƣ�����
    //    {
    //        _jumpPower = JUMPPOWER;
    //        _gravity = GRAVITY;
    //    }
    //    else hitDamage(1); // �ƴ� �� ������ ����
    //}
}

void character::attackRect() // ĳ���� ���� ��Ʈ ó��
{
    // ����, ���� ���� �� ��Ʈ ����
    if (_state == ATTACK || _state == JUMPATTACK)
    {
        if (_direction == 0) _attackCollisionRect = RectMakeCenter(_collisionRect.right + 13, _y, 140, 96); // ����
        if (_direction == 1) _attackCollisionRect = RectMakeCenter(_collisionRect.left - 13, _y, 140, 96); // ����
    }

    // ���� �ϴ� ���� ��Ʈ ����
    if (_state == JUMPBOTTOMATTACK)
    {
        _attackCollisionRect = RectMakeCenter(_x, _y, 56, 96);
    }

    // ����, ���� ����, ���� �ϴ� ���� ���°� �ƴϸ� ���� ��Ʈ �ʱ�ȭ
    if (_state != ATTACK && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK)
    {
        _attackCollisionRect = RectMakeCenter(0, 0, 0, 0);
    }
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

void character::idle(bool direction)
{
    if (_state != JUMP && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK && _state != HANG)
    {
        _state = IDLE;
        imgSetting();
    }

    _direction = direction;
    _speed = 0;
}

void character::run(bool direction)
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

void character::jump()
{
    _jumpPower = JUMPPOWER;
    _gravity = GRAVITY;
    _state = JUMP;
    imgSetting();
    _isPixelCollision = false;
    _isRectCollision = false;
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

void character::jumpBottomAttack()
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

void character::skill()
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
        Rectangle(getMemDC(), _imgRect);
        Rectangle(getMemDC(), _collisionRect);
        Rectangle(getMemDC(), _attackCollisionRect);
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
}


