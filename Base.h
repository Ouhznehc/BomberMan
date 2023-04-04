#ifndef BASE_H
#define BASE_H
#include "transform.h"
#define HARD_WALL 1
#define SOFT_WALL 2
#define FLOOR 3
#define SPEED 4
#define POWER 5
#define PUSH 6
#define BOMB 7
#define PLAYER1 8
#define FLASH 9
#define ADDBOMB 10
#define AI1 11
#define PLAYER2 12
#define AI2 13
#define LEFT 14
#define RIGHT 15
#define UP 16
#define DOWN 17
#define STAY 18
extern GameObject* beginGame;
extern GameObject* endGame;
extern GameObject* help;
extern GameObject* stopGame;
extern GameObject* backGround;
extern GameObject* bomberMan;
extern GameObject* helpScene;
extern GameObject* lose;
extern GameObject* win;
extern GameObject* player1;
extern GameObject* player2;
extern GameObject* Ai1;
extern GameObject* Ai2;
extern bool isBeginGame;
extern bool isPlayer1Live;
extern bool isPlayer2Live;
extern bool isAI1Live;
extern bool isAI2Live;
extern bool isRead;
float distance(Transform* a, Transform* b);
bool checkAchieve(Transform *now);
int location(float x, float y);
void upDateScore();
bool searchItem(float x, float y, int type);
void addThing(GameObject *now, int type);
void removeThing(GameObject *now);
int decide(int x, int y);
#endif // BASE_H
