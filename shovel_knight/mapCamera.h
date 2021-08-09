#pragma once
#include "gameNode.h"


#define WIDTH 80
#define HEIGHT 100

class character;
class object;

class mapCamera : public gameNode
{
private:

	// background image
	image* _background;

	float _xPower, _yPower;

	character* _character;
	object* _object;

	// Camera
	RECT _camera;
	int _camX, _camY;

	int _mapCountX;
	int _mapCountY;

	bool _isCamMove;
	bool _isCamMove2;

	int _LR;
	int _TB;

	bool _camFollowX;
	bool _camFollowY;

public:
	mapCamera();
	~mapCamera();

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render(HDC hdc);	//�׸��� �Լ�

	void Collision();



	void SetCamera(RECT& camera, int left, int top, int width, int height);
	void CameraMove(RECT& camera);


	void MakeObject(RECT& rect, int left, int right, int top, int bottom);		// �� �� ������Ʈ(ī�޶� �̵�)


	//void RendObject(RECT rect[], int max);
	//void RendObject(RECT& rect);

	void setCharacterAddressLink(character* character) { _character = character; }			// ĳ���� Ŭ�� ��ũ 
	void setObjectMemoryAddressLink(object* object) { _object = object; }			// ������Ʈ Ŭ�� ��ũ 
};
