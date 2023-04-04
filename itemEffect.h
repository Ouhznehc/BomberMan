#ifndef ITEMEFFECT_H
#define ITEMEFFECT_H
#include "component.h"
#include "gamescene.h"
class ItemEffect: public Component
{
    public:
        ItemEffect();
        void addPower();
        void addMove();
        void setType(int x, GameScene* gameScene);
        void addBombNum();
        void onUpdate(float deltaTime) override;
        void change(GameObject* obj, int num);
        int restBombNum = 1;
        int bombPower = 1;
        float speed = 62.5;
        int score = 0;
        bool moveable = false;
        GameObject* life;
        GameObject* power;
        GameObject* Speed;
        GameObject* number;
        GameObject* score_1;
        GameObject* score_2;
    private:
        int type;
        float bombTime = 3.5;
        int maxBombNum = 1;
};
#endif // BOMBEFFECT_H
