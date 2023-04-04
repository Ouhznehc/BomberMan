#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <component.h>
#include <gameobject.h>
#include <physics.h>

class UserController : public Component
{
public:
    UserController();

    void onAttach() override;
    void onUpdate(float deltaTime) override;
    int Type();
    void setType(int type);
    float coolSetBombTime = 4;
    float coolMoveTime = 0.5;

private:
    int my_type;
    Physics *physics;
};

#endif // USERCONTROLLER_H
