#pragma once
#include "gameNode.h"

class character;

class uiManager : public gameNode
{

private:
	bool goatShopOpen;
	int	 goatCnt = 1;

	bool fireShopOpen;
	int	 fireCnt = 1;

	bool talkOpen;
	int	 talkCnt;
	int	 vibcnt;

	character* _character;


public:
	uiManager();
	~uiManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void goatshop();

	void goatshopOn();
	void goatshopOff();

	void fireshop();

	void fireshopOn();
	void fireshopOff();

	void talklingMan();

	void talklingManOn();
	void talklingManOff();

	bool getGoatShopOpen() { return goatShopOpen; }
	bool getFireShopOpen() { return fireShopOpen; }
	bool getTalkOpen() { return talkOpen; }

	void setcharacterMemoryAddressLink(character* character) { _character = character; }// 캐릭터 클라스 링크 
};

