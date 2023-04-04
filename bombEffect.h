#ifndef BOMBEFFECT_H
#define BOMBEFFECT_H
#include "component.h"

class BombEffect: public Component
{
    public:
        BombEffect();
        void addPower();
        void addMove();
        void addBombNum();
        int restBombNum = 1;
    private:
        float bombTime = 3.5;
        int maxBombNum = 1;
        int bombPower = 1;
        bool moveable = false;
};
#endif // BOMBEFFECT_H
