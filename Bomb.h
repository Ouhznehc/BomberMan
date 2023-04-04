#ifndef BOMB_H
#define BOMB_H
#include <component.h>
#include <gameobject.h>
#include <transform.h>

void setBomb(GameObject *Owner);
class Bomb: public Component
{
    public:
        Bomb();
        void onAttach() override;
        void onUpdate(float deltaTime) override;
        GameObject *owner;
        bool isAddNum = false;
        bool isCheck = false;
        bool isSet = false;
        bool isBombMoving = false;
        Transform *transform;
        GameObject *flash[12];
    private:
        float bombTime = 3.5;
        float flashTime = 0.1;
};
#endif // BOMB_H
