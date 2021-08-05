#include "pch.h"
#include "character.h"

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

    IMAGEMANAGER->addImage("����浹", "image/shovel_knight_map_collision.bmp", 1280, 720, false, RGB(255, 0, 255));
    _backGroundCollision = IMAGEMANAGER->findImage("����浹");

    _characterImg = IMAGEMANAGER->findImage("ĳ����_���̵�");
    _x = WINSIZEX / 2;
    _y = WINSIZEY / 2 + 210;
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

    // �׽�Ʈ�� ��Ʈ
    //_rc[0] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 310, WINSIZEX, 100);
    _rc[1] = RectMakeCenter(WINSIZEX / 2 + 200, WINSIZEY / 2, 200, 50);
    _rc[2] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, 200, 50);
    _rc[3] = RectMakeCenter(165, 200, 200, 50);

    _attackRc = RectMakeCenter(WINSIZEX / 2 - 400, WINSIZEY / 2 + 200, 50, 50);

    _hangRc[0] = RectMakeCenter(WINSIZEX / 2 - 600, WINSIZEY / 2 + 200, 50, 800);
    _hangRc[1] = RectMakeCenter(WINSIZEX / 2 - 500, WINSIZEY / 2, 55, 200);

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
            _speed = SPEED;
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
            _speed = SPEED;
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
        for (int i = 0; i < HANGRCMAX; i++)
        {
            RECT temp;
            if (IntersectRect(&temp, &_collisionRect, &_hangRc[i]))
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
                    _y -= SPEED/1.5;
                }
                if (KEYMANAGER->isStayKeyDown('S'))
                {
                    _state = HANG;
                    imgSetting();
                    _hangCount++;
                    _gravity = _jumpPower = 0;

                    _x = (temp.left + temp.right) / 2;
                    _y += SPEED/1.5;
                }
            }

            // ĳ���� �ϴܿ� ��ٸ��� ���� ��� ������ ������ �� �ֵ��� ó��
            POINT check;
            check.x = _x;
            check.y = _collisionRect.bottom + 10;
            if (PtInRect(&_hangRc[i], check))
            {
                if (KEYMANAGER->isStayKeyDown('S') && !IntersectRect(&temp, &_collisionRect, &_hangRc[i]))
                {
                    _state = HANG;
                    imgSetting();
                    _hangCount++;
                    _gravity = _jumpPower = 0;

                    _x = (_hangRc[i].left + _hangRc[i].right) / 2;
                    _y += SPEED / 1.5;
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
        if (_direction == 0) _x -= SPEED;
        else _x += SPEED;
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
    for (int i = 0; i < HANGRCMAX; i++)
    {
        RECT temp;
        if (IntersectRect(&temp, &_collisionRect, &_hangRc[i]))
        {
            _hangRcNum = i;
        }
    }

    // ��ٸ� �����
    for (int i = 0; i < HANGRCMAX; i++)
    {
        RECT temp;
        if (!IntersectRect(&temp, &_collisionRect, &_hangRc[_hangRcNum]))
        {
            if (_hangRc[_hangRcNum].top >= _collisionRect.bottom)
            {
                _hangRcNum = 0;
                if (_state == HANG) _state = IDLE;
                imgSetting();
            }

            if (_hangRc[_hangRcNum].bottom <= _collisionRect.top)
            {
                _hangRcNum = 0;
                if (_state == HANG) _state = JUMP;
                imgSetting();
                _gravity = GRAVITY;
            }
        }
    }    
}

void character::collision() // ĳ���� �浹 ó��
{
    // �ٴ� �ȼ� �浹 ó��
    if (_state == JUMP || _state == JUMPATTACK || _state == JUMPBOTTOMATTACK || _state == HURT)
    {
        int proveY = _y + (_collisionRect.bottom - _collisionRect.top) / 2;
        for (int i = proveY - 10; i < proveY + 10; i++)
        {
            if (GetPixel(_backGroundCollision->getMemDC(), _x, i) == RGB(255, 0, 255))
            {
                _y = i - (_collisionRect.bottom - _collisionRect.top) / 2 - 5;
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
        int proveX = _x + (_collisionRect.right - _collisionRect.left) / 2;
        for (int i = proveX - 10; i < proveX + 10; i++)
        {
            if (GetPixel(_backGroundCollision->getMemDC(), i, _y) == RGB(255, 0, 255))
            {
                _x = i - (_collisionRect.right - _collisionRect.left) / 2 - SPEED;
                break;
            }
        }
    }
    else // ���� ���� ���� ��
    {
        int proveX = _x - (_collisionRect.right - _collisionRect.left) / 2;
        for (int i = proveX + 10; i >= proveX - 10; i--)
        {
            if (GetPixel(_backGroundCollision->getMemDC(), i, _y) == RGB(255, 0, 255))
            {
                _x = i + (_collisionRect.right - _collisionRect.left) / 2 + SPEED;
                break;
            }
        }
    }

    // ��ֹ��� ��Ʈ �浹 ó��
    for (int i = 0; i < RCMAX; i++)
    {
        RECT temp;
        if (IntersectRect(&temp, &_collisionRect, &_rc[i]))
        {
            float width = temp.right - temp.left;
            float height = temp.bottom - temp.top;

            if (width <= height) // ���� �浹
            {
                if (_collisionRect.left <= _rc[i].left) // ���ʿ��� �浹
                {
                    _x -= SPEED;
                }
                else // �����ʿ��� �浹
                {
                    _x += SPEED;
                }
            }

            if (width > height) // ���� �浹
            {
                _rcNum = i; // ���� � ��ֹ��� �浹�ߴ��� ���

                if (_collisionRect.bottom <= _rc[i].bottom) // �ؿ��� �浹
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
        POINT check;
        if (_direction == 0) check.x = _collisionRect.left;
        else check.x = _collisionRect.right;
        //check.x = _x;
        check.y = _collisionRect.bottom;

        if (!PtInRect(&_rc[_rcNum], check) && _state == RUN)
        {
            _gravity = GRAVITY;
            _state = JUMP;
            imgSetting();
        }
    }

    //// ���� �浹�� ��ֹ����� ����� �߷¹޾� �������� ó��
    //if (_collisionRect.right < _rc[_rcNum].left)
    //{
    //    _gravity = GRAVITY;
    //    _rcNum = 0;

    //    if (_state != JUMPBOTTOMATTACK) _state = JUMP;
    //}
    //else if (_collisionRect.left > _rc[_rcNum].right)
    //{
    //    _gravity = GRAVITY;
    //    _rcNum = 0;

    //    if (_state != JUMPBOTTOMATTACK) _state = JUMP;
    //}

    // �ǰ� �׽�Ʈ�� ��Ʈ
    RECT temp2;
    if (IntersectRect(&temp2, &_collisionRect, &_attackRc))
    {
        if (_state == JUMPBOTTOMATTACK) // �ϴ� ������ ���� ���� �ٽ� Ƣ�����
        {
            _jumpPower = JUMPPOWER;
            _gravity = GRAVITY;
        }
        else hitDamage(2); // �ƴ� �� ������ ����
    }
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
    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        _backGroundCollision->render(getMemDC(), 0, 0);
    }

    HBRUSH brush2 = CreateSolidBrush(RGB(0, 255, 0));
    HBRUSH oldbrush2 = (HBRUSH)SelectObject(getMemDC(), brush2);
    Rectangle(getMemDC(), _hangRc[0]);                 // ��ٸ� �׽�Ʈ�� ��Ʈ
    Rectangle(getMemDC(), _hangRc[1]);                 // ��ٸ� �׽�Ʈ�� ��Ʈ
    SelectObject(getMemDC(), oldbrush2);
    DeleteObject(brush2);

    // ĳ���� �̹��� ����
    _characterImg->frameRender(getMemDC(), _imgRect.left, _imgRect.top);

    // ĳ���� ��Ʈ ����
    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        Rectangle(getMemDC(), _imgRect);
        Rectangle(getMemDC(), _collisionRect);
        //Rectangle(getMemDC(), _rc[0]); //�׽�Ʈ ��Ʈ
    }

    for (int i = 1; i < RCMAX; i++) // �׽�Ʈ ��Ʈ
    {
        Rectangle(getMemDC(), _rc[i]);
    }

    HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
    HBRUSH oldbrush = (HBRUSH)SelectObject(getMemDC(), brush);
    Rectangle(getMemDC(), _attackRc); // �ǰ� �׽�Ʈ�� ��Ʈ
    SelectObject(getMemDC(), oldbrush);
    DeleteObject(brush);

    // ���� ������
    char str[128];
    sprintf_s(str, "_currentFrame : %d", _currentFrame);
    TextOut(getMemDC(), 0, 100, str, strlen(str));
}


