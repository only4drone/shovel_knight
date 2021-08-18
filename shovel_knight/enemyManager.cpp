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

    _bullet = new mHellFire;
    _bullet->init(100, 1000);

    return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
    for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
    {
        (*_viEnemy)->update(_mapCamera->getCamX(), _mapCamera->getCamY(), _character->getCharacterX(), _character->getCharacterY());
    }

    //_isDelet가 true면 벡터에서 지움
    for (int i = 0; i < getVEnemy().size(); i++)
    {
        if (getVEnemy()[i]->getDelete() == true)
        {
            _vEnemy.erase(_vEnemy.begin() + i);
        }
    }
    enemyBulletFire();
    collision();
    _bullet->update();
}

void enemyManager::render()
{
    for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
    {
        (*_viEnemy)->render();
    }

    _bullet->render();
}

void enemyManager::enemySetting()
{
    
	enemy* enemyBeeto;

    
    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(1600, 580), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(2000, 580), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(2400, 580), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(2800, 580), E_LEFT);
    _vEnemy.push_back(enemyBeeto);
    
    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(3200, 480), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(3560, 480), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(4000, 375), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new steed;
    enemyBeeto->init("steed", PointMake(4000, 580), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(4800, 325), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new steed;
    enemyBeeto->init("steed", PointMake(4800, 580), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(5600, 530), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(6000, 480), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(6500, 480), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(7200, 580), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new wizard;
    enemyBeeto->init("wizard", PointMake(8300, 330), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new steed;
    enemyBeeto->init("steed", PointMake(7800, 585 - WINSIZEY), E_RIGHT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new dragon;
    enemyBeeto->init("dragon", PointMake(10500, 580 - WINSIZEY), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new steed;
    enemyBeeto->init("steed", PointMake(10400, 480), E_RIGHT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new steed;
    enemyBeeto->init("steed", PointMake(10600, 480), E_RIGHT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new wizard;
    enemyBeeto->init("wizard", PointMake(10300, 2020), E_RIGHT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(10950, 2020), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new steed;
    enemyBeeto->init("steed", PointMake(12200, 2025), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(14700, 1355), E_LEFT);
    _vEnemy.push_back(enemyBeeto);


    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(14300, 530), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(14600, 530), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(14800, 380 - WINSIZEY), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(16000, 480 - WINSIZEY), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(18200, 630 - WINSIZEY), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(19800, 630 - WINSIZEY * 2), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(19500, 630 - WINSIZEY * 2), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(19200, 630 - WINSIZEY * 2), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(19200, 430 - WINSIZEY * 2), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(19820, 430 - WINSIZEY * 3), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(20000, 530 - WINSIZEY * 3), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(20900, 380 - WINSIZEY * 3), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new beeto;
    enemyBeeto->init("beeto", PointMake(21400, 580 - WINSIZEY * 3), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

    enemyBeeto = new bugDragon;
    enemyBeeto->init("bugDragon", PointMake(22200, 580 - WINSIZEY * 3), E_LEFT);
    _vEnemy.push_back(enemyBeeto);

}



void enemyManager::enemyBulletFire()
{
    for (int i = 0; i < _vEnemy.size(); ++i)
    {
        if (getVEnemy()[i]->getEnemyState() == E_SMOKE) continue;
        if (getVEnemy()[i]->getEnemyName() != "wizard") continue;

        float direction;
        if (getVEnemy()[i]->getEnemyDirction() == 0) direction = PI;
        else if (getVEnemy()[i]->getEnemyDirction() == 1) direction = 0;

        getVEnemy()[i]->setAttackCount(getVEnemy()[i]->getAttackCount() + 1);

        if (getVEnemy()[i]->getAttackCount() > 150)
        {
            float x = (getVEnemy()[i]->getRect().left + getVEnemy()[i]->getRect().right) / 2;
            float y = (getVEnemy()[i]->getRect().top + getVEnemy()[i]->getRect().bottom) / 2;
            _bullet->fire(x, y, direction);
            getVEnemy()[i]->setAttackCount(0);
        }
        break;
    }

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
        RECT characterAttackRC = _character->getAttackRect();

        if(_character->getState() == JUMPBOTTOMATTACK)
        {
            if (IntersectRect(&temp, &characterAttackRC, &enemyRC) && getVEnemy()[i]->getDefense() == false)
            {
                getVEnemy()[i]->setHead(true);
                //getVEnemy()[i]->setEnemyState(E_SMOKE);
                getVEnemy()[i]->setHit(1);
                getVEnemy()[i]->setDefense(true);
                break;
              
            }
        }
        if (_character->getState() == ATTACK || _character->getState() == JUMPATTACK)
        {
            if (IntersectRect(&temp, &characterAttackRC, &enemyRC) && getVEnemy()[i]->getDefense() == false)
            {
                getVEnemy()[i]->setHead(false);
                //getVEnemy()[i]->setEnemyState(E_SMOKE);
                getVEnemy()[i]->setHit(1);
                getVEnemy()[i]->setDefense(true);
                break;
                
            }
        }
    }
    
    for (int i = 0; i < getVEnemy().size(); i++)
    {
        if (getVEnemy()[i]->getEnemyState() == E_DIE)
        {
            int proveXRight = getVEnemy()[i]->getX() + (getVEnemy()[i]->getRect().right - getVEnemy()[i]->getRect().left);
            
            for (int j = proveXRight; j < proveXRight + 3; j++)
            {
                if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), j, getVEnemy()[i]->getY() - _mapCamera->getCamY()) == RGB(255, 0, 255))
                {
                    getVEnemy()[i]->setHead(true);
                    break;
                }
            }
           
        }

        if (getVEnemy()[i]->getEnemyState() == E_MOVE && getVEnemy()[i]->getEnemyName() == "steed")
        {
            int proveXRight = getVEnemy()[i]->getX() + (getVEnemy()[i]->getRect().right - getVEnemy()[i]->getRect().left);
            int proveXLeft = getVEnemy()[i]->getX();
        
            
            for (int j = proveXLeft; j < proveXLeft + 3; j++)
            {
                if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), j , getVEnemy()[i]->getY() - _mapCamera->getCamY() - 15) == RGB(255, 0, 255))
                {
                    getVEnemy()[i]->setHit(1);
                    getVEnemy()[i]->setHead(true);
                    break;
                }
            }
            for (int j = proveXRight; j < proveXRight + 3; j++)
            {
                if (GetPixel(_mapCamera->getBackGroundMagenta()->getMemDC(), j, getVEnemy()[i]->getY() - _mapCamera->getCamY() - 15) == RGB(255, 0, 255))
                {
                    getVEnemy()[i]->setHit(1);
                    getVEnemy()[i]->setHead(true);
                    break;
                }
            }
        }
    }
    
    // 파이어볼과 캐릭터 충돌 처리
    for (int i = 0; i < _bullet->getVBullet().size(); i++)
    {
        RECT temp;
        RECT character = _character->getCharacterRect();
        RECT fireball = _bullet->getVBullet()[i].rc;
        if (IntersectRect(&temp, &character, &fireball))
        {
            _character->hitDamage(1);
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
    IMAGEMANAGER->addFrameImage("steed and idle", "image/shovel knight_steed and idle.bmp", 150, 200, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("steed and move", "image/shovel knight_steed and move.bmp", 600, 200, 4, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("steed and die", "image/shovel knight_steed and die.bmp", 60, 200, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("steed and legacy", "image/shovel knight_steed and legacy.bmp", 100, 60, 1, 2, true, RGB(255, 0, 255));
    //wizard
    IMAGEMANAGER->addFrameImage("wizard and idle", "image/shovel knight_wizard and idle.bmp", 140, 200, 2, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("wizard and attack", "image/shovel knight_wizard and attack.bmp", 180, 200, 2, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("wizard and die", "image/shovel knight_wizard and attack.bmp", 180, 200, 2, 2, true, RGB(255, 0, 255));
    //dragon
    IMAGEMANAGER->addFrameImage("dragon and idle", "image/shovel knight_dragon and idle.bmp", 6000, 300, 12, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("dragon and move", "image/shovel knight_dragon and move.bmp", 3000, 300, 6, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("dragon and attack", "image/shovel knight_dragon and attack.bmp", 3000, 300, 6, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("dragon and die", "image/shovel knight_dragon and die.bmp", 500, 300, 1, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("lazer", "image/shovel knight_lazer.bmp", 4800, 150, 6, 1, true, RGB(255, 0, 255));
    //bugDragon
    IMAGEMANAGER->addFrameImage("bugDragon and idle", "image/shovel knight_bugDragon and idle.bmp", 6000, 300, 12, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("bugDragon and move", "image/shovel knight_bugDragon and move.bmp", 3000, 300, 6, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("bugDragon and attack", "image/shovel knight_bugDragon and attack.bmp", 3000, 300, 6, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("bugDragon and die", "image/shovel knight_bugDragon and die.bmp", 500, 300, 1, 1, true, RGB(255, 0, 255));
    
    //죽었을 때 연기
    IMAGEMANAGER->addFrameImage("smoke", "image/shovel knight_smoke.bmp", 300, 40, 5, 1, true, RGB(255, 0, 255));

}
