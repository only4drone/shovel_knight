#include "pch.h"
#include "mapCamera.h"
#include "character.h"
#include "object.h"

mapCamera::mapCamera()
{
}

mapCamera::~mapCamera()
{
}


//�ʱ�ȭ�� ���⿡�� �ض�!!!
HRESULT mapCamera::init()
{
	gameNode::init();

	// ���
	_background = IMAGEMANAGER->addImage("���", "image/map_black.bmp", 23000, 4500, true, RGB(255, 0, 255));
	_background_magenta = IMAGEMANAGER->addImage("��渶��Ÿ", "image/map_magenta.bmp", 23000, 4500, false, RGB(255, 0, 255));

	// ī�޶�
	//_camera.left = _character->getCharacterX() - (WIDTH / 2);
	//_camera.right = _character->getCharacterX() + (WIDTH / 2);
	// ī�޶� �߰�s

	_camera.top = 200;
	_camera.bottom = WINSIZEY - 200;

	_camX = 0;
	_camY = -2200;

	_mapCountX = 1;
	_mapCountY = 0;

	_camFollowX = true;
	_camFollowY = true;

	return S_OK;
}

//�޸� ������ ����� �ض�!!!!
void mapCamera::release()
{
	gameNode::release();


}


//����ó���� ����ٰ�!
void mapCamera::update()
{
	gameNode::update();

	_camera.left = _character->getCharacterX() - (WIDTH / 2);
	_camera.right = _character->getCharacterX() + (WIDTH / 2);

	CameraMove(_camera);

}

//����� �׷����!!!
void mapCamera::render()
{
	_background->render(getMemDC(), _camX, _camY);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		_background_magenta->render(getMemDC(), _camX, _camY);
		Rectangle(getMemDC(), _camera);
	}

	char str[128];

	sprintf_s(str, "cameraleft : %d", _camera.left);
	TextOut(getMemDC(), 10, 70, str, strlen(str));

	sprintf_s(str, "camX : %d", _camX);
	TextOut(getMemDC(), 10, 90, str, strlen(str));
	sprintf_s(str, "camY : %d", _camY);
	TextOut(getMemDC(), 100, 90, str, strlen(str));
}

void mapCamera::SetCamera(RECT& camera, int left, int top, int width, int height)
{
	camera.left = left;
	camera.right = _camera.left + width;


	camera.top = top;
	camera.bottom = _camera.top + height;
}


void mapCamera::CameraMove(RECT& camera)
{
	//CAMERAMANAGER->SetCamera(_camera, 200, 200, 400, 400);
	//CAMERAMANAGER->MoveCamera(_player.rc, _background, _player.speed, _camX, _camY);

	// ī�޶� üũ ���� ����
	SetCamera(camera, (WINSIZEX / 2) - (WIDTH / 2), 200, WIDTH, 400);

	// camera ���� �ȿ����� �÷��̾ ���� �̵�(Ȥ�� ī�޶� �̵��� �Ұ����� ���)
	if (_background->getHeight() <= WINSIZEY - _camY || _camY == 0 || _character->getCharacterRect().bottom < camera.bottom || _character->getCharacterRect().top > camera.top)
	{
		_character->setCharacterY(_character->getCharacterY() - _character->getJumpPower());
		_character->setJumpPower(_character->getJumpPower() - _character->getGravity());
	}

	// ���ȭ���� ���� ���� ������ â�� �����̶� �������� �̵� ����
	// ���ȭ���� ������ ���� ������ â�� �������̶� �������� �̵� ����
	if (_camX >= 0 || _camX >= -5050)
	{
		_character->setSpeed(SPEED);
	}
	else
	{
		_character->setSpeed(SPEED);
		_camFollowX = false;
	}

	if (_camY <= 0 || _camY < -2139)
	{
		_character->setSpeed(SPEED);
	}
	else
	{
		_character->setSpeed(SPEED);
		_camFollowY = false;
	}


	// 1. �簢���� �̿��ϴ� ���
	// ���� ������ �簢�� rc�� ĳ������ rc�� ���� ���(left, right, top, bottom)�� ���� ��������
	// �ش� �������� ī�޶� �̵�

	//if (_player.x - _camX == -3840) _camFollow = false;

	// ī�޶� �������� �̵� (����� ����������)

	if (_camFollowX)
	{
		if (_character->getCharacterX() <= camera.left + 40 && KEYMANAGER->isStayKeyDown('A'))
		{
			if (_camX < 0)
			{
				_camX += SPEED;
				_character->setSpeed(0);
				_character->setCharacterX(_camera.left + 40);
			}
		}
		// ī�޶� ���������� �̵� (����� ��������) _player.x >= camera.right - 40 && 
		else if (_character->getCharacterX() >= camera.right - 40 && KEYMANAGER->isStayKeyDown('D'))
		{
			if (_camX + _background->getWidth() >= WINSIZEX)
			{
				_camX -= SPEED;
				_character->setSpeed(0);
				_character->setCharacterX(_camera.right - 40);
			}

		}
		else
		{
			_character->setSpeed(SPEED);
		}
	}



	if (_character->getCharacterX() - _camX >= WINSIZEX * _mapCountX - 160)
	{
		_mapCountX++;
		_isCamMove = true;
		_LR = 1;

	}
	else if (_character->getCharacterX() - _camX < WINSIZEX * (_mapCountX - 1) - 160)
	{
		_mapCountX--;
		_isCamMove = true;
		_LR = 0;
	}
	else if (_camX == -(WINSIZEX * (_mapCountX - 1)) + 160) //���� �Ѿ�ٰ� ������ǥ������ ķ���갡 �����ºκ�
	{
		_isCamMove = false;

	}


	if (!_camFollowX)
	{
		if (_LR && _isCamMove)
		{
			_camX -= SPEED;
			_character->setSpeed(0);
			_character->setCharacterX(_character->getCharacterX() - SPEED);
			//_player.x -= SPEED;
		}
		else if (!_LR && _isCamMove)
		{
			_camX += SPEED;
			_character->setSpeed(0);
			_character->setCharacterX(_character->getCharacterX() + SPEED);
			//_player.x += SPEED;
		}
		else
		{
			_character->setSpeed(SPEED);
		}
	}

	//ī�޶� ���� �̵�

	if (!_camFollowY)
	{
		_camY += SPEED;
		_character->setJumpPower(0);
		_character->setCharacterY(_character->getCharacterY() + SPEED);

		if (_camY > -1500 + ((_mapCountY - 1) * WINSIZEY)) _camFollowY = true;
	}
	else
	{
		if (_character->getCharacterY() >= camera.bottom - 50)
		{
			if (2850 - _mapCountY * WINSIZEY >= WINSIZEY - _camY)
			{
				_camY += _character->getJumpPower();
				_character->setCharacterY(camera.bottom - 50);
			}
		}
	}
	if (_character->getCharacterY() < 0)
	{
		_mapCountY++;
		_camFollowY = false;
	}

	// 2. ��ǥ���� �̿��ϴ� ���
	// ĳ������ �߽� x,y��ǥ���� ���� ��ǥ���� ���ؼ�
	// ī�޶� �̵�
}

void mapCamera::MakeObject(RECT& rect, int left, int top, int width, int height)
{
	rect.left = _camX + left;
	rect.right = rect.left + width;
	rect.top = _camY + top;
	rect.bottom = rect.top + height;
}