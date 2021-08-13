#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<string, gameNode*>				mapSceneList;
	typedef map<string, gameNode*>::iterator	mapSceneIter;

private:
	static gameNode* _currentScene;

	mapSceneList _mSceneList;
	bool isUIcall;
	bool hasFire =false;
	int _gold = 10000;
	int _mana = 100;
	
public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	gameNode* addScene(string sceneName, gameNode* scene);

	HRESULT changeScene(string sceneName);

	int bossHp = 0;
	int hp = 0;
	void nowHP(int x);


	// SCENEMANAGER-> getGold() 같은 식으로 사용
	int getGold();
	void setGold(int x);

	int getMana();
	void setMana(int x);

	int getBossHp();
	void setBossHp(int x);

	// 파이어 유물을 사다.
	void getFire();
	void delFire();

	// 파이어 유물을  보유하고 있는지 아닌지 체크해서 반환해준다;
	bool checkFire();



};

