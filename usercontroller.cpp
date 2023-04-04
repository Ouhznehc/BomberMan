#include "usercontroller.h"
#include "imagetransform.h"
#include "bomb.h"
#include "transformbuilder.h"
#include "base.h"
#include "gamescene.h"
#include "itemEffect.h"
#include "physics.h"
UserController::UserController() {}

void UserController ::  setType(int type){
    my_type = type;
}

int UserController :: Type(){return my_type;}

void UserController :: onAttach () {
    this->physics = this->gameObject->getComponent<Physics>();
    assert(this->physics != nullptr);
}

void UserController :: onUpdate (float deltaTime) {
//    if (coolUpdateTime >= 0) coolUpdateTime -= deltaTime;
//    else{
//        upDateScore();
//        coolUpdateTime = 1;
//    }

    if(!isBeginGame) return;
    if(!isAI1Live && !isAI2Live){
        isBeginGame = false;
        stopGame->getComponent<ImageTransform>()->setImage("");
        endGame->getComponent<ImageTransform>()->setImage(":/Player/Picture/Others/exit.png");
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 9, 100 + 40 * 7))
            .setImage(":/Player/Picture/Others/Result_win.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(win);
        win->getComponent<Transform>()->setZValue(100);
        this->attachGameObject(win);
    }
    if(!isPlayer1Live && !isPlayer2Live){
        isBeginGame = false;
        stopGame->getComponent<ImageTransform>()->setImage("");
        endGame->getComponent<ImageTransform>()->setImage(":/Player/Picture/Others/exit.png");
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 9, 100 + 40 * 7))
            .setImage(":/Player/Picture/Others/Result_lose.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(lose);
        lose->getComponent<Transform>()->setZValue(100);
        this->attachGameObject(lose);
    }
    if(this->Type() == PLAYER1 && !isPlayer1Live) return;
    else if(this->Type() == PLAYER2 && !isPlayer2Live) return;
    else if(this->Type() == AI1 && !isAI1Live) return;
    else if(this->Type() == AI2 && !isAI2Live) return;
    float vx = 0, vy = 0;
    if(!checkAchieve(this->physics->transform)) return;
    float x = this->physics->transform->pos().x();
    float y = this->physics->transform->pos().y();
    //qDebug("%lf %lf",x, y);
    if(this->Type() == PLAYER1){
        if (getKey(Qt ::Key_A)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_left.png");
            if(location(x - 40, y) == HARD_WALL || location(x - 40, y) == SOFT_WALL) return;
            if(location(x- 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x - 80, y) == HARD_WALL || location(x - 80, y) == SOFT_WALL || location(x - 80, y) == BOMB) return;
                }
            }
            if(location(x, y) == PLAYER1) addThing(this->getParentGameObject(), FLOOR);
            this->physics->moveable = true;
            vx -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set1;
        }
        if (getKey(Qt ::Key_D)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_right.png");
            if(location(x + 40, y) == HARD_WALL || location(x + 40, y) == SOFT_WALL) return;
            if(location(x + 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x + 80, y) == HARD_WALL || location(x + 80, y) == SOFT_WALL || location(x + 80, y) == BOMB) return;
                }
            }
            if(location(x, y) == PLAYER1) addThing(this->getParentGameObject(), FLOOR);
            this->physics->moveable = true;
            vx += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set1;
        }
        if (getKey(Qt ::Key_W)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_back.png");
            if(location(x, y - 40) == HARD_WALL || location(x, y - 40) == SOFT_WALL) return;
            if(location(x, y - 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y - 80) == HARD_WALL || location(x, y - 80) == SOFT_WALL || location(x, y - 80) == BOMB) return;
                }
            }
            if(location(x, y) == PLAYER1) addThing(this->getParentGameObject(), FLOOR);
            this->physics->moveable = true;
            vy -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set1;
        }
        if (getKey(Qt ::Key_S)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_face.png");
            if(location(x, y + 40) == HARD_WALL || location(x, y + 40) == SOFT_WALL) return;
            if(location(x, y + 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y + 80) == HARD_WALL || location(x, y + 80) == SOFT_WALL || location(x, y + 80) == BOMB) return;
                }
            }
            if(location(x, y) == PLAYER1) addThing(this->getParentGameObject(), FLOOR);
            this->physics->moveable = true;
            vy += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set1;
        }
        set1:
        if (getKeyDown(Qt ::Key_Space)){
            if(this->getParentGameObject()->getComponent<ItemEffect>()->restBombNum > 0){
                    setBomb(this->getParentGameObject());
            }
            return;
        }
    }
    if(this->Type() == PLAYER2){
        if (getKey(Qt ::Key_Left)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_left.png");
            if(location(x - 40, y) == HARD_WALL || location(x - 40, y) == SOFT_WALL) return;
            if(location(x- 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x - 80, y) == HARD_WALL || location(x - 80, y) == SOFT_WALL || location(x - 80, y) == BOMB) return;
                }
            }
            if(location(x, y) == PLAYER2) addThing(this->getParentGameObject(), FLOOR);
            this->physics->moveable = true;
            vx -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set2;
        }
        if (getKey(Qt ::Key_Right)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_right.png");
            if(location(x + 40, y) == HARD_WALL || location(x + 40, y) == SOFT_WALL) return;
            if(location(x + 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x + 80, y) == HARD_WALL || location(x + 80, y) == SOFT_WALL || location(x + 80, y) == BOMB) return;
                }
            }
            if(location(x, y) == PLAYER2) addThing(this->getParentGameObject(), FLOOR);
            this->physics->moveable = true;
            vx += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set2;
        }
        if (getKey(Qt ::Key_Up)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_back.png");
            if(location(x, y - 40) == HARD_WALL || location(x, y - 40) == SOFT_WALL) return;
            if(location(x, y - 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y - 80) == HARD_WALL || location(x, y - 80) == SOFT_WALL || location(x, y - 80) == BOMB) return;
                }
            }
            if(location(x, y) == PLAYER2) addThing(this->getParentGameObject(), FLOOR);
            this->physics->moveable = true;
            vy -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set2;
        }
        if (getKey(Qt ::Key_Down)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_face.png");
            if(location(x, y + 40) == HARD_WALL || location(x, y + 40) == SOFT_WALL) return;
            if(location(x, y + 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y + 80) == HARD_WALL || location(x, y + 80) == SOFT_WALL || location(x, y + 80) == BOMB) return;
                }
            }
            if(location(x, y) == PLAYER2) addThing(this->getParentGameObject(), FLOOR);
            this->physics->moveable = true;
            vy += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set2;
        }
        set2:
        if (getKeyDown(Qt ::Key_Return)){
            if(this->getParentGameObject()->getComponent<ItemEffect>()->restBombNum > 0){
                setBomb(this->getParentGameObject());
            }
            return;
        }
    }
    if(this->Type() == AI1 && isAI1Live){
        upDateScore();
        int ix = (y - 100) / 40;
        int iy = (x - 100) / 40;
        int dir = decide(ix, iy);
        if(coolBombTime >= 0) coolBombTime -= deltaTime;
        if(searchItem(x, y, SOFT_WALL) || searchItem(x, y, PLAYER1) || searchItem(x, y, PLAYER2)){
            if(this->getParentGameObject()->getComponent<ItemEffect>()->restBombNum > 0){
                setBomb(this->getParentGameObject());
                coolBombTime = 0.5;
            }
        }
        if(dir == UP){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_back.png");
            if(location(x, y - 40) == HARD_WALL || location(x, y - 40) == SOFT_WALL) return;
            if(location(x, y - 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y - 80) == HARD_WALL || location(x, y - 80) == SOFT_WALL || location(x, y - 80) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vy -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
        }
        if(dir == DOWN){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_face.png");
            if(location(x, y + 40) == HARD_WALL || location(x, y + 40) == SOFT_WALL) return;
            if(location(x, y + 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y + 80) == HARD_WALL || location(x, y + 80) == SOFT_WALL || location(x, y + 80) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vy += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
        }
        if(dir == LEFT){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_left.png");
            if(location(x - 40, y) == HARD_WALL || location(x - 40, y) == SOFT_WALL) return;
            if(location(x- 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x - 80, y) == HARD_WALL || location(x - 80, y) == SOFT_WALL || location(x - 80, y) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vx -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
        }
        if(dir == RIGHT){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_right.png");
            if(location(x + 40, y) == HARD_WALL || location(x + 40, y) == SOFT_WALL) return;
            if(location(x + 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x + 80, y) == HARD_WALL || location(x + 80, y) == SOFT_WALL || location(x + 80, y) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vx += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
        }
    }
    if(this->Type() == AI2 && isAI2Live){
        upDateScore();
        int ix = (y - 100) / 40;
        int iy = (x - 100) / 40;
        int dir = decide(ix, iy);
        if(coolBombTime >= 0) coolBombTime -= deltaTime;
        if(searchItem(x, y, SOFT_WALL) || searchItem(x, y, PLAYER1) || searchItem(x, y, PLAYER2)){
            if(this->getParentGameObject()->getComponent<ItemEffect>()->restBombNum > 0){
                setBomb(this->getParentGameObject());
                coolBombTime = 0.5;
            }
        }
        if(dir == UP){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_back.png");
            if(location(x, y - 40) == HARD_WALL || location(x, y - 40) == SOFT_WALL) return;
            if(location(x, y - 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y - 80) == HARD_WALL || location(x, y - 80) == SOFT_WALL || location(x, y - 80) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vy -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
        }
        if(dir == DOWN){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_face.png");
            if(location(x, y + 40) == HARD_WALL || location(x, y + 40) == SOFT_WALL) return;
            if(location(x, y + 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y + 80) == HARD_WALL || location(x, y + 80) == SOFT_WALL || location(x, y + 80) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vy += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
        }
        if(dir == LEFT){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_left.png");
            if(location(x - 40, y) == HARD_WALL || location(x - 40, y) == SOFT_WALL) return;
            if(location(x- 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x - 80, y) == HARD_WALL || location(x - 80, y) == SOFT_WALL || location(x - 80, y) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vx -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
        }
        if(dir == RIGHT){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_right.png");
            if(location(x + 40, y) == HARD_WALL || location(x + 40, y) == SOFT_WALL) return;
            if(location(x + 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x + 80, y) == HARD_WALL || location(x + 80, y) == SOFT_WALL || location(x + 80, y) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vx += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
        }
    }
    else return;
}
