#include "base.h"
#include "gameobject.h"
#include "transform.h"
#include "component.h"
bool isBeginGame = false;
bool isPlayer1Live = true;
bool isPlayer2Live = true;
bool isAI1Live = true;
bool isAI2Live = true;
bool isRead = true;
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

int score[15][20];
int Dx[5] = {-1, 1, 0, 0, 0};
int Dy[5] = {0, 0, -1, 1, 0};

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
    if(Location[X][Y] == 9) return PLAYER1;
    if(Location[X][Y] == 10) return PLAYER2;
    else return -1;
}

bool searchItem(float x, float y, int type){
    if(location(x - 40, y) == type) return true;
    else if(location(x + 40, y) == type) return true;
    else if(location(x, y - 40) == type) return true;
    else if(location(x, y + 40) == type) return true;
    else if(location(x, y) == type) return true;
    return false;
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
    if(type == PLAYER1) Location[x][y] = 9;
    if(type == PLAYER2) Location[x][y] = 10;
}

void removeThing(GameObject *now){
    int x = (now->getComponent<Transform>()->pos().y() - 100) / 40;
    int y = (now->getComponent<Transform>()->pos().x() - 100) / 40;
    Location[x][y] = 0;
    return;
}

void upDateScore(){
    isRead = true;
    memset(score, 0, sizeof(score));
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 20; j++){
            if(Location[i][j] == 3){
                //qDebug("---");
                score[i][j] -= 80;
                for(int k = 1; k <= 3; k++){
                    if(i - k >= 0)
                    score[i - k][j] -= (4 - k) * 20;
                    if(j - k >= 0)
                    score[i][j - k] -= (4 - k) * 20;
                    score[i + k][j] -= (4 - k) * 20;
                    score[i][j + k] -= (4 - k) * 20;
                }
            }
            if(Location[i][j] >= 4 && Location[i][j] <= 8 && Location[i][j] != 7){
                score[i][j] += 10;
            }
            if(Location[i][j] == 7) score[i][j] -= 100;
            if(Location[i][j] == 9 || Location[i][j] == 10){
                score[i][j] += 20;
            }
            if(Location[i][j] == 0){
                if(Location[i - 1][j] == 2) score[i][j] += 1;
                if(Location[i + 1][j] == 2) score[i][j] += 1;
                if(Location[i][j - 1] == 2) score[i][j] += 1;
                if(Location[i][j + 1] == 2) score[i][j] += 1;
            }
            if(Location[i][j] == 1 || Location[i][j] == 2){
                score[i][j] = -100;
            }
        }
    }
    isRead = false;
    return;
}

std::pair<int, int> searchWay(int x, int y, int deep, int now){
    int max = -2000;
    int ans = -1;
    if(deep == 1){
        for(int i = 0; i < 5; i++){
            if(Location[x + Dx[i]][y + Dy[i]] == 1 || Location[x +Dx[i]][y + Dy[i]] == 2) continue;
            if(max < now + score[x + Dx[i]][y + Dy[i]]){
                max = now + score[x + Dx[i]][y + Dy[i]];
                ans = i;
            }
        }
        return std::make_pair(ans, max);
    }
    for(int i = 0; i < 5; i++){
        if(Location[x + Dx[i]][y + Dy[i]] == 1 || Location[x + Dx[i]][y + Dy[i]] == 2) continue;
        if(max < searchWay(x + Dx[i], y + Dy[i], deep - 1, now + score[x + Dx[i]][y + Dy[i]] * deep).second){
            max = searchWay(x + Dx[i], y + Dy[i], deep - 1, now + score[x + Dx[i]][y + Dy[i]] * deep).second;
            ans = i;
        }
    }
    return std::make_pair(ans, max);
}

int decide(int x, int y){
    int ans = searchWay(x, y, 8, 0).first;
    if(ans == 0) return UP;
    else if(ans == 1) return DOWN;
    else if(ans == 2) return LEFT;
    else if(ans == 3) return RIGHT;
    else if(ans == 4) return STAY;
    else return -1;
}
