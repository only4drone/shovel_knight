#include "pch.h"
#include "character.h"
#include "mapCamera.h"
#include "object.h"

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

    _characterImg = IMAGEMANAGER->findImage("ĳ����_���̵�");
    _x = 400;
    _y = 580;
    _state = IDLE;
    _direction = 0;
    _isPixelCollision = true;
    _speed = _gravity = _jumpPower = 0;
    _currentHP = _maxHP = 8;
    _currentFrame = _count = 0;
    _damage = 1;
    _hangCount = _rcNum = 0;

    _imgRect = RectMakeCenter(_x, _y, _characterImg->getFrameWidth(), _characterImg->getFrameHeight());
    _collisionRect = RectMakeCenter(_x, _y, 55, 96);

    return S_OK;
}

void character::release()
{
}

void character::update() // ������Ʈ
{
    gravity();
    collision();
    controll();
    hang();
    attack();
    imgFrameSetting();
    
    // ��Ʈ ����
    _imgRect = RectMakeCenter(_x, _y, _characterImg->getFrameWidth(), _characterImg->getFrameHeight());
    _collisionRect = RectMakeCenter(_x, _y, 55, 96);
}

void character::controll() // ĳ���� ��Ʈ��Ű ó��
{
    if (_state != ATTACK && _state != HURT) // ���� ����, �ǰ� ���°� �ƴ� ��
    {
        // �޸���
        if (KEYMANAGER->isStayKeyDown('A'))
        {
            if (_state != JUMP && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK && _state != HANG)
            {
                _state = RUN;
                imgSetting();
            }

            _direction = 1;
            _speed = _mapCamera->getSpeed();
            _x -= _speed;
        }
        if (KEYMANAGER->isStayKeyDown('D'))
        {
            if (_state != JUMP && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK && _state != HANG)
            {
                _state = RUN;
                imgSetting();
            }

            _direction = 0;
            _speed = _mapCamera->getSpeed();
            _x += _speed;
        }

        // ���̵�
        if (KEYMANAGER->isOnceKeyUp('A'))
        {
            if (_state != JUMP && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK && _state != HANG)
            {
                _state = IDLE;
                imgSetting();
            }
            
            _direction = 1;
            _speed = 0;
        }
        if (KEYMANAGER->isOnceKeyUp('D'))
        {
            if (_state != JUMP && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK && _state != HANG)
            {
                _state = IDLE;
                imgSetting();
            }

            _direction = 0;
            _speed = 0;
        }

        // ����
        if (KEYMANAGER->isOnceKeyDown('J'))
        {
            if (_state != JUMPATTACK)
            {
                if (_state == JUMP || _state == JUMPBOTTOMATTACK) // ���� ����
                {
                    _state = JUMPATTACK;
                    imgSetting();                  
                }
                else if(_state == IDLE || _state == RUN)// ���� ���°� �ƴ� ��
                {
                    _state = ATTACK;
                    imgSetting();
                }
            }
        }

        // ����
        if (KEYMANAGER->isOnceKeyDown('K') || KEYMANAGER->isOnceKeyDown(VK_SPACE))
        {
            if (_state != JUMP && _state != JUMPATTACK && _state != JUMPBOTTOMATTACK && _state != HANG)
            {
                _jumpPower = JUMPPOWER;
                _gravity = GRAVITY;
                _state = JUMP;
                imgSetting();
                _isPixelCollision = false;
            }
        }

        // ���� �ϴ� ����
        if (_state == JUMP) // ���� ����
        {
            if (KEYMANAGER->isStayKeyDown('S'))
            {
                _state = JUMPBOTTOMATTACK;
                imgSetting();
            }
        }

        // ��ٸ� Ÿ��
        for (int i = 0; i < _object->getLadderMax(); i++)
        {
            RECT temp;
            RECT ladder = _object->getLadder(i).rc;
            if (IntersectRect(&temp, &_collisionRect, &ladder))
            {
                if (KEYMANAGER->isStayKeyDown('A') && _state == HANG)
                {
                    _gravity = GRAVITY;
                    _state = JUMP;
                    imgSetting();
                }
                if (KEYMANAGER->isStayKeyDown('D') && _state == HANG)
                {
                    _gravity = GRAVITY;
                    _state = JUMP;
                    imgSetting();
                }
                if (KEYMANAGER->isStayKeyDown('W')) 
                {
                    _state = HANG;
                    imgSetting();
                    _hangCount++;
                    _gravity = _jumpPower = 0;

                    _x = (temp.left + temp.right) / 2;
                    _y -= _mapCamera->getSpeed() / 1.5;
                }
                if (KEYMANAGER->isStayKeyDown('S'))
                {
                    _state = HANG;
                    imgSetting();
                    _hangCount++;
                    _gravity = _jumpPower = 0;

                    _x = (ladder.left + ladder.right) / 2; //(temp.left + temp.right) / 2;
                    _y += _mapCamera->getSpeed() / 1.5;
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
                    _state = HANG;
                    imgSetting();
                    _hangCount++;
                    _gravity = _jumpPower = 0;

                    _x = (ladder.left + ladder.right) / 2;
                    _y += _mapCamera->getSpeed() / 1.5;
                }
            }
        }
    }
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
    }

    // ���� �̹����� �°� Ŀ��Ʈ ������ �ʱ�ȭ
    if (_state != IDLE && _state != RUN)
    {
        if (_direction == 0) _currentFrame = 0;
        else if (_direction == 1) _currentFrame = _characterImg->getMaxFrameX();
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
        }
    }

    // ī��Ʈ �ʱ�ȭ
    if (_count >= 5) _count = 0;
}

void character::gravity() // ĳ���� �߷� ó��
{
    // ĳ���Ͱ� �߷¹޾Ƽ� �������� ������ �� �̹��� ����
    if (_jumpPower < 0 && _state != JUMPBOTTOMATTACK && _state != JUMPATTACK && _state != HURT && _state != HANG)
        _characterImg = IMAGEMANAGER->findImage("ĳ����_����2");

    // �߷� �� ����
    if (_state == JUMP || _state == JUMPATTACK || _state == JUMPBOTTOMATTACK || _state == HURT) // ���� ����, �ǰ� ������ ��
    {
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

void character::hang() // ĳ���� ��ٸ� Ÿ�� ó��
{
    // ��ٸ� Ÿ�� �̹��� ����(��ٸ� Ÿ��� �̵� �� �Ҷ��� ����� �־�� �ؼ� ���� ó��)
    if (_state == HANG)
    {
        if (_hangCount % 10 == 0) _characterImg->setFrameX(0);
        else if (_hangCount % 19 == 0) _characterImg->setFrameX(1);

        if (_hangCount >= 19) _hangCount = 1;
    }

    // � ��ٸ� �浹�ߴ���
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
        if (ladder.top >= _collisionRect.bottom)
        {
            _hangRcNum = 0;
            if (_state == HANG) _state = IDLE;
            imgSetting();
        }

        if (ladder.bottom <= _collisionRect.top)
        {
            _hangRcNum = 0;
            if (_state == HANG) _state = JUMP;
            imgSetting();
            _gravity = GRAVITY;
        }
    }  
}

void character::collision() // ĳ���� �浹 ó��
{
    // �ٴ� �ȼ� �浹 ó��
    if (_state == JUMP || _state == JUMPATTACK || _state == JUMPBOTTOMATTACK || _state == HURT)
    {
        int proveY = _y + ((_collisionRect.bottom - _collisionRect.top) / 2) - _mapCamera->getCamY();
        for (int i = proveY - 10; i < proveY + 10; i++)
        {
            if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), _x - _mapCamera->getCamX(), i) == RGB(255, 0, 255))
            {
                _y = i - (_collisionRect.bottom - _collisionRect.top) / 2 - 5 + _mapCamera->getCamY();
                _gravity = _jumpPower = 0;
                _state = IDLE;
                imgSetting();
                _isPixelCollision = true;
                break;
            }
        }
    }

    // ���� �ȼ� �浹 ó��
    if (_direction == 0) // ������ ���� ���� ��
    {
        int proveX = _x + ((_collisionRect.right - _collisionRect.left) / 2) - _mapCamera->getCamX();
        for (int i = proveX - 10; i < proveX + 10; i++)
        {
            if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), i, _y - _mapCamera->getCamY()) == RGB(255, 0, 255))
            {
                _x = i - (_collisionRect.right - _collisionRect.left) / 2 - _mapCamera->getSpeed() + _mapCamera->getCamX();
                break;
            }
        }
    }
    else // ���� ���� ���� ��
    {
        int proveX = _x - ((_collisionRect.right - _collisionRect.left) / 2) - _mapCamera->getCamX();
        for (int i = proveX + 10; i >= proveX - 10; i--)
        {
            if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), i, _y - _mapCamera->getCamY()) == RGB(255, 0, 255))
            {
                _x = i + (_collisionRect.right - _collisionRect.left) / 2 + _mapCamera->getSpeed() + _mapCamera->getCamX();
                break;
            }
        }
    }

    // ��ֹ��� ��Ʈ �浹 ó��
    for (int i = 0; i < _object->getPlatformrMax(); i++)
    {
        RECT temp;
        RECT platform = _object->getPlatform(i).rc;
        if (IntersectRect(&temp, &_collisionRect, &platform))
        {
            float width = temp.right - temp.left;
            float height = temp.bottom - temp.top;

            if (width <= height) // ���� �浹
            {
                if (_collisionRect.left <= platform.left) // ���ʿ��� �浹
                {
                    _x -= _mapCamera->getSpeed();
                }
                else // �����ʿ��� �浹
                {
                    _x += _mapCamera->getSpeed();
                }
            }

            if (width > height) // ���� �浹
            {
                _rcNum = i; // ���� � ��ֹ��� �浹�ߴ��� ���

                if (_collisionRect.bottom <= platform.bottom) // �ؿ��� �浹
                {
                    _y -= height;
                    _gravity = _jumpPower = 0; // �߷�, �����Ŀ� �ʱ�ȭ
                    _state = IDLE;
                    imgSetting();
                }
                else // ������ �浹
                {
                    _y += height;
                    _jumpPower = 0;
                }
            }
        }
    }

    // �ؿ� ��ֹ��� ���ٸ� �߷¹޾� �������� ó��
    if (_isPixelCollision == false)
    {
        RECT platform = _object->getPlatform(_rcNum).rc;
        POINT check;
        if (_direction == 0) check.x = _collisionRect.left;
        else check.x = _collisionRect.right;
        //check.x = _x;
        check.y = _collisionRect.bottom;

        if (!PtInRect(&platform, check) && _state == RUN)
        {
            _gravity = GRAVITY;
            _state = JUMP;
            imgSetting();
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

void character::attack() // ĳ���� ���� ó��
{
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

void character::render() // ĳ���� ����
{
    // ĳ���� �̹��� ����
    _characterImg->frameRender(getMemDC(), _imgRect.left, _imgRect.top);

    // ĳ���� ��Ʈ ����
    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        Rectangle(getMemDC(), _imgRect);
        Rectangle(getMemDC(), _collisionRect);
    }

    //// ���� ������
    //char str[128];
    //sprintf_s(str, "_currentFrame : %d", _currentFrame);
    //TextOut(getMemDC(), 0, 100, str, strlen(str));
}


