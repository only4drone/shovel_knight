#include "pch.h"
#include "enemyManager.h"
#include "character.h"
#include "mapCamera.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
    enemyImageStorage();        //적 이미지 초기화

    return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
    for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
    {
        (*_viEnemy)->update(_mapCamera->getCamX(), _mapCamera->getCamY(), _character->getCharacterX());
    }

    enemyBulletFire();
    collision();
}

void enemyManager::render()
{
    for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
    {
        (*_viEnemy)->render();
    }
}

void enemyManager::enemySetting()
{
    
	enemy* enemyBeeto;

    enemyBeeto = new beeto;
    enemyBeeto->init("steed", PointMake(1600, 580), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(2000, 580), E_LEFT);
    _vEnemy.push_back(enemyBeeto);
    
    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(3200, 480), E_LEFT);
    _vEnemy.push_back(enemyBeeto);
}



void enemyManager::enemyBulletFire()
{
}

void enemyManager::removeEnemy(int arrNum)
{
    _vEnemy.erase(_vEnemy.begin() + arrNum);
}

void enemyManager::collision()
{
    for (int i = 0; i < getVEnemy().size(); i++)
    {
        RECT temp;
        RECT enemyRC = getVEnemy()[i]->getRect();
        RECT characterRC = _character->getAttackRect();

        if (IntersectRect(&temp, &characterRC, &enemyRC) && getVEnemy()[i]->getDefense() == false)
        {
            getVEnemy()[i]->setDefense(true);
            getVEnemy()[i]->setHit(1);
        }
    }
}

void enemyManager::enemyImageStorage()
{
    //beeto
    IMAGEMANAGER->addFrameImage("beeto and idle", "image/shovel knight_beeto and move.bmp", 280, 78, 4, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("beeto and move", "image/shovel knight_beeto and move.bmp", 280, 78, 4, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("beeto and die", "image/shovel knight_beeto and die.bmp", 123, 81, 2, 2, true, RGB(255, 0, 255));
    //steed
    IMAGEMANAGER->addFrameImage("steed and idle", "image/shovel knight_steed and idle.bmp", 99, 100, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("steed and move", "image/shovel knight_steed and move.bmp", 600, 200, 4, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("steed and die", "image/shovel knight_steed and die.bmp", 35, 100, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("steed and legacy", "image/shovel knight_steed and legacy.bmp", 80, 40, 1, 2, true, RGB(255, 0, 255));
    //wizard
    IMAGEMANAGER->addFrameImage("wizard and idle", "image/shovel knight_wizard and idle.bmp", 90, 160, 2, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("wizard and attack", "image/shovel knight_wizard and attack.bmp", 120, 160, 2, 2, true, RGB(255, 0, 255));
    //dragon
    IMAGEMANAGER->addFrameImage("dragon and idle", "image/shovel knight_dragon and idle.bmp", 6000, 300, 12, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("dragon and move", "image/shovel knight_dragon and move.bmp", 3000, 300, 6, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("dragon and attack", "image/shovel knight_dragon and attack.bmp", 3000, 300, 6, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("dragon and die", "image/shovel knight_dragon and die.bmp", 500, 300, 1, 1, true, RGB(255, 0, 255));
    //boss
}
