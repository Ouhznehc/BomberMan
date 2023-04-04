#include "base.h"
#include "gameobject.h"
#include "transform.h"
#include "component.h"
bool isBeginGame = false;
bool isPlayer1Live = true;
bool isPlayer2Live = true;
bool isAI1Live = true;
bool isAI2Live = true;
GameObject* beginGame = new GameObject();
GameObject* endGame = new GameObject();
GameObject* stopGame = new GameObject();
GameObject* backGround = new GameObject();
GameObject* bomberMan = new GameObject();
GameObject* helpScene = new GameObject();
GameObject* help = new GameObject();
GameObject* lose = new GameObject();
GameObject* win = new GameObject();
GameObject* player1 = new GameObject();
GameObject* player2 = new GameObject();
GameObject* Ai1 = new GameObject();
GameObject* Ai2 = new GameObject();
int Location[15][20] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,2,2,0,2,2,1,0,2,1,0,0,2,1,2,0,0,1,
    1,0,1,2,1,0,1,2,1,0,1,1,0,1,2,1,2,2,0,1,
    1,2,2,0,1,0,1,0,0,2,0,0,2,1,2,1,2,1,2,1,
    1,1,1,2,1,2,1,0,1,1,0,1,0,1,2,1,0,1,2,1,
    1,2,2,2,0,0,2,0,2,0,2,0,2,2,0,2,0,2,2,1,
    1,2,1,2,1,1,0,1,0,1,1,2,0,0,1,1,0,1,2,1,
    1,0,2,0,0,1,0,1,0,1,1,0,1,0,1,0,0,2,0,1,
    1,2,1,0,1,1,2,0,2,1,1,0,1,0,1,1,2,1,2,1,
    1,2,2,0,2,0,2,2,0,2,0,2,0,2,0,0,2,0,0,1,
    1,1,1,0,1,2,1,2,2,0,1,1,0,1,2,0,2,1,1,1,
    1,2,2,2,1,2,1,0,0,0,2,0,0,1,0,1,0,2,2,1,
    1,0,1,1,1,2,1,0,1,1,0,1,2,1,0,1,1,1,0,1,
    1,0,0,2,2,2,0,0,1,2,0,1,0,0,2,2,2,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
float distance(Transform* a, Transform* b){
    int x = fabs(a->pos().x() - b->pos().x());
    int y = fabs(a->pos().y() - b->pos().y());
    return fmax(x, y);
}

bool checkAchieve(Transform* now){
    float x = now->pos().x();
    float y = now->pos().y();
    if(((int)(x - 100) % 40 == 0) && ((int)(y - 100) % 40 == 0)) return true;
    return false;
}

int location(float x, float y){
    int X = (y - 100) / 40;
    int Y = (x - 100) / 40;
    if(X < 0 || Y < 0 || X > 14 || Y > 19){
        qDebug("error x = %d, y = %d", X, Y);
        return -1;
    }
    if(Location[X][Y] == 0) return FLOOR;
    if(Location[X][Y] == 1) return HARD_WALL;
    if(Location[X][Y] == 2) return SOFT_WALL;
    if(Location[X][Y] == 3) return BOMB;
    if(Location[X][Y] == 4) return SPEED;
    if(Location[X][Y] == 5) return POWER;
    if(Location[X][Y] == 6) return PUSH;
    if(Location[X][Y] == 7) return FLASH;
    if(Location[X][Y] == 8) return ADDBOMB;
    else return -1;
}

bool searchItem(float x, float y, int type){
    if(location(x - 40, y) == type) return true;
    else if(location(x + 40, y) == type) return true;
    else if(location(x, y - 40) == type) return true;
    else if(location(x, y + 40) == type) return true;
    return false;
}

bool checkStuck(float x, float y){
    if(location(x - 40, y) != FLOOR && location(x + 40, y) != FLOOR && location(x, y - 40) != FLOOR && location(x, y + 40) != FLOOR)
        return true;
    else return false;
}

void addThing(GameObject* now, int type){
    int x = (now->getComponent<Transform>()->pos().y() - 100) / 40;
    int y = (now->getComponent<Transform>()->pos().x() - 100) / 40;
    if(type == FLOOR) Location[x][y] = 0;
    if(type == BOMB) Location[x][y] = 3;
    if(type == SPEED) Location[x][y] = 4;
    if(type == POWER) Location[x][y] = 5;
    if(type == PUSH) Location[x][y] = 6;
    if(type == FLASH) Location[x][y] = 7;
    if(type == ADDBOMB) Location[x][y] = 8;
}

void removeThing(GameObject *now){
    int x = (now->getComponent<Transform>()->pos().y() - 100) / 40;
    int y = (now->getComponent<Transform>()->pos().x() - 100) / 40;
    Location[x][y] = 0;
    return;
}
