#pragma once
#include "gameNode.h"

#define SPEED 5.0f
#define WIDTH 55
#define HEIGHT 96

class character;
class object;

class mapCamera : public gameNode
{
private:
	int temp =0;
	// background image
	image* _background;
	image* _background_magenta;

	float _xPower, _yPower;

	character* _character;
	object* _object;

	// Camera
	RECT _camera;
	int _camX, _camY;				// �� ��ü�� left, top ��

	int _mapCountX;					// ���� 1280���� ������ ���� x��
	int _mapCountY;					// ���� 720���� ������ ���� y��

	bool _isCamMove;
	bool _isCamMove2;

	int _LR;
	int _TB = 0;

	bool _camFollowX;
	bool _camFollowY;

public:
	mapCamera();
	~mapCamera();

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�

	image* getBackGround() { return _background; }
	image* getBackGroundMagenta() { return _background_magenta; }

	int getCamX() { return _camX; }					//camX - ����� ���۵Ǵ� left ��ǥ
	int getCamY() { return _camY; }					//camY - ����� ���۵Ǵ� top ��ǥ

	bool getIsCamMove() { return _isCamMove; }

	float getSpeed() { return SPEED; }

	void SetCamera(RECT& camera, int left, int top, int width, int height);
	void CameraMove(RECT& camera);


	void MakeObject(RECT& rect, int left, int right, int top, int bottom);		// �� �� ������Ʈ(ī�޶� �̵�)


	//void RendObject(RECT rect[], int max);
	//void RendObject(RECT& rect);

	void setCharacterAddressLink(character* character) { _character = character; }			// ĳ���� Ŭ�� ��ũ 
	void setObjectMemoryAddressLink(object* object) { _object = object; }			// ������Ʈ Ŭ�� ��ũ 
};
