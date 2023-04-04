#ifndef PHYSICS_H
#define PHYSICS_H

#include <component.h>
#include <gameobject.h>
#include <transform.h>

class Physics: public Component
{
    public:
        Physics();
        void onAttach() override;
        void setType(int type);
        int type();
        void move(float deltaTime, float v);
        void onUpdate(float deltaTime) override;
        void setVelocity(float vx, float vy);
        Transform *transform;
        bool moveable = true;
    private:
        float vx = 0, vy = 0;
        int my_type;
        float changeTime = 0.2;
        int changeSign = 0;
};

#endif // PHYSICS_H
