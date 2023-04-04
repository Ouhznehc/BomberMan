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
            if(location(x - 40, y) == HARD_WALL || location(x - 40, y) == SOFT_WALL || location(x - 40, y) == PLAYER1 || location(x - 40, y) == PLAYER2 || location(x - 40, y) == AI1 || location(x - 40, y) == AI2) return;
            if(location(x- 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x - 80, y) == HARD_WALL || location(x - 80, y) == SOFT_WALL || location(x - 80, y) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vx -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set1;
        }
        if (getKey(Qt ::Key_D)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_right.png");
            if(location(x + 40, y) == HARD_WALL || location(x + 40, y) == SOFT_WALL || location(x + 40, y) == PLAYER1 || location(x + 40, y) == PLAYER2 || location(x + 40, y) == AI1 || location(x + 40, y) == AI2) return;
            if(location(x + 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x + 80, y) == HARD_WALL || location(x + 80, y) == SOFT_WALL || location(x + 80, y) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vx += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set1;
        }
        if (getKey(Qt ::Key_W)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_back.png");
            if(location(x, y - 40) == HARD_WALL || location(x, y - 40) == SOFT_WALL || location(x, y - 40) == PLAYER1 || location(x, y - 40) == PLAYER2 || location(x, y - 40) == AI1 || location(x, y - 40) == AI2) return;
            if(location(x, y - 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y - 80) == HARD_WALL || location(x, y - 80) == SOFT_WALL || location(x, y - 80) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vy -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set1;
        }
        if (getKey(Qt ::Key_S)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_face.png");
            if(location(x, y + 40) == HARD_WALL || location(x, y + 40) == SOFT_WALL ||  location(x, y + 40) == PLAYER1 || location(x, y + 40) == PLAYER2 || location(x, y + 40) == AI1 || location(x, y + 40) == AI2) return;
            if(location(x, y + 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y + 80) == HARD_WALL || location(x, y + 80) == SOFT_WALL || location(x, y + 80) == BOMB) return;
                }
            }
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
            if(location(x - 40, y) == HARD_WALL || location(x - 40, y) == SOFT_WALL || location(x - 40, y) == PLAYER1 || location(x - 40, y) == PLAYER2 || location(x - 40, y) == AI1 || location(x - 40, y) == AI2) return;
            if(location(x- 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x - 80, y) == HARD_WALL || location(x - 80, y) == SOFT_WALL || location(x - 80, y) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vx -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set2;
        }
        if (getKey(Qt ::Key_Right)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_right.png");
            if(location(x + 40, y) == HARD_WALL || location(x + 40, y) == SOFT_WALL || location(x + 40, y) == PLAYER1 || location(x + 40, y) == PLAYER2 || location(x + 40, y) == AI1 || location(x + 40, y) == AI2) return;
            if(location(x + 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x + 80, y) == HARD_WALL || location(x + 80, y) == SOFT_WALL || location(x + 80, y) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vx += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set2;
        }
        if (getKey(Qt ::Key_Up)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_back.png");
            if(location(x, y - 40) == HARD_WALL || location(x, y - 40) == SOFT_WALL || location(x, y - 40) == PLAYER1 || location(x, y - 40) == PLAYER2 || location(x, y - 40) == AI1 || location(x, y - 40) == AI2) return;
            if(location(x, y - 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y - 80) == HARD_WALL || location(x, y - 80) == SOFT_WALL || location(x, y - 80) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vy -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            goto set2;
        }
        if (getKey(Qt ::Key_Down)){
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_face.png");
            if(location(x, y + 40) == HARD_WALL || location(x, y + 40) == SOFT_WALL ||  location(x, y + 40) == PLAYER1 || location(x, y + 40) == PLAYER2 || location(x, y + 40) == AI1 || location(x, y + 40) == AI2) return;
            if(location(x, y + 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y + 80) == HARD_WALL || location(x, y + 80) == SOFT_WALL || location(x, y + 80) == BOMB) return;
                }
            }
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
    if(this->Type() == AI1){
        if(coolSetBombTime > 0){
            coolSetBombTime -= deltaTime;
        }
        else{

            if(this->getParentGameObject()->getComponent<ItemEffect>()->restBombNum > 0){
                if(searchItem(x, y, SOFT_WALL)){
                    setBomb(this->getParentGameObject());
                    coolSetBombTime = 4;
                }
            }
        }
        if(coolMoveTime > 0){
            coolMoveTime -= deltaTime;
            return;
        }
        coolMoveTime = 0.5;
        int dir = rand() % 4;
        bool flag = true;
        if(location(x, y) == BOMB) flag = false;
        if(checkStuck(x, y)){
            if(this->getParentGameObject()->getComponent<ItemEffect>()->restBombNum > 0){
            setBomb(this->getParentGameObject());
          }
        }
        if(searchItem(x, y, BOMB)){
            if(location(x - 40, y) == FLOOR) goto next4;
            else if(location(x + 40, y) == FLOOR) goto next1;
            else if(location(x, y - 40) == FLOOR) goto next2;
            else if(location(x, y + 40) == FLOOR) goto next3;
        }
        if(dir == 0){
            next4:
            if((searchItem(x - 40, y, BOMB) && flag) || searchItem(x, y, FLASH)) return;
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_left.png");
            if(location(x - 40, y) == HARD_WALL || location(x - 40, y) == SOFT_WALL || location(x - 40, y) == PLAYER1 || location(x - 40, y) == PLAYER2 || location(x - 40, y) == AI1 || location(x - 40, y) == AI2) goto next1;
            if(location(x- 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x - 80, y) == HARD_WALL || location(x - 80, y) == SOFT_WALL || location(x - 80, y) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vx -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            return;
        }
        else if(dir == 1){
            next1:
            if((searchItem(x + 40, y, BOMB) && flag) || searchItem(x, y, FLASH)) return;
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_right.png");
            if(location(x + 40, y) == HARD_WALL || location(x + 40, y) == SOFT_WALL || location(x + 40, y) == PLAYER1 || location(x + 40, y) == PLAYER2 || location(x + 40, y) == AI1 || location(x + 40, y) == AI2) goto next2;
            if(location(x + 40, y) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x + 80, y) == HARD_WALL || location(x + 80, y) == SOFT_WALL || location(x + 80, y) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vx += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            return;
        }
        else if(dir == 2){
            next2:
            if((searchItem(x, y - 40, BOMB) && flag) || searchItem(x, y, FLASH)) return;
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_back.png");
            if(location(x, y - 40) == HARD_WALL || location(x, y - 40) == SOFT_WALL || location(x, y - 40) == PLAYER1 || location(x, y - 40) == PLAYER2 || location(x, y - 40) == AI1 || location(x, y - 40) == AI2) goto next3;
            if(location(x, y - 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y - 80) == HARD_WALL || location(x, y - 80) == SOFT_WALL || location(x, y - 80) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vy -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            return;
        }
        else if(dir == 3){
            next3:
            if((searchItem(x, y + 40, BOMB) && flag) || searchItem(x, y + 40, FLASH)) return;
            this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_face.png");
            if(location(x, y + 40) == HARD_WALL || location(x, y + 40) == SOFT_WALL ||  location(x, y + 40) == PLAYER1 || location(x, y + 40) == PLAYER2 || location(x, y + 40) == AI1 || location(x, y + 40) == AI2) goto next4;
            if(location(x, y + 40) == BOMB){
                if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                else{
                    if(location(x, y + 80) == HARD_WALL || location(x, y + 80) == SOFT_WALL || location(x, y + 80) == BOMB) return;
                }
            }
            this->physics->moveable = true;
            vy += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
            this->physics->setVelocity (vx, vy);
            return;
        }
    }
        if(this->Type() == AI2){
            if(coolSetBombTime > 0){
                coolSetBombTime -= deltaTime;
            }
            else{

                if(this->getParentGameObject()->getComponent<ItemEffect>()->restBombNum > 0){
                    if(searchItem(x, y, SOFT_WALL)){
                        setBomb(this->getParentGameObject());
                        coolSetBombTime = 4;
                    }
                }
            }
            if(coolMoveTime > 0){
                coolMoveTime -= deltaTime;
                return;
            }
            coolMoveTime = 0.5;
            int dir = rand() % 4;
            bool flag = true;
            if(location(x, y) == BOMB) flag = false;
            if(checkStuck(x, y)){
                if(this->getParentGameObject()->getComponent<ItemEffect>()->restBombNum > 0){
                setBomb(this->getParentGameObject());
              }
            }
            if(searchItem(x, y, BOMB)){
                if(location(x - 40, y) == FLOOR) goto Next4;
                else if(location(x + 40, y) == FLOOR) goto Next1;
                else if(location(x, y - 40) == FLOOR) goto Next2;
                else if(location(x, y + 40) == FLOOR) goto Next3;
            }
            if(dir == 0){
                Next4:
                if((searchItem(x - 40, y, BOMB) && flag) || searchItem(x, y, FLASH)) return;
                this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_left.png");
                if(location(x - 40, y) == HARD_WALL || location(x - 40, y) == SOFT_WALL || location(x - 40, y) == PLAYER1 || location(x - 40, y) == PLAYER2 || location(x - 40, y) == AI1 || location(x - 40, y) == AI2) goto Next1;
                if(location(x- 40, y) == BOMB){
                    if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                    else{
                        if(location(x - 80, y) == HARD_WALL || location(x - 80, y) == SOFT_WALL || location(x - 80, y) == BOMB) return;
                    }
                }
                this->physics->moveable = true;
                vx -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
                this->physics->setVelocity (vx, vy);
                return;
            }
            else if(dir == 1){
                Next1:
                if((searchItem(x + 40, y, BOMB) && flag) || searchItem(x, y, FLASH)) return;
                this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_right.png");
                if(location(x + 40, y) == HARD_WALL || location(x + 40, y) == SOFT_WALL || location(x + 40, y) == PLAYER1 || location(x + 40, y) == PLAYER2 || location(x + 40, y) == AI1 || location(x + 40, y) == AI2) goto Next2;
                if(location(x + 40, y) == BOMB){
                    if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                    else{
                        if(location(x + 80, y) == HARD_WALL || location(x + 80, y) == SOFT_WALL || location(x + 80, y) == BOMB) return;
                    }
                }
                this->physics->moveable = true;
                vx += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
                this->physics->setVelocity (vx, vy);
                return;
            }
            else if(dir == 2){
                Next2:
                if((searchItem(x, y - 40, BOMB) && flag) || searchItem(x, y, FLASH)) return;
                this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_back.png");
                if(location(x, y - 40) == HARD_WALL || location(x, y - 40) == SOFT_WALL || location(x, y - 40) == PLAYER1 || location(x, y - 40) == PLAYER2 || location(x, y - 40) == AI1 || location(x, y - 40) == AI2) goto Next3;
                if(location(x, y - 40) == BOMB){
                    if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                    else{
                        if(location(x, y - 80) == HARD_WALL || location(x, y - 80) == SOFT_WALL || location(x, y - 80) == BOMB) return;
                    }
                }
                this->physics->moveable = true;
                vy -= this->getParentGameObject()->getComponent<ItemEffect>()->speed;
                this->physics->setVelocity (vx, vy);
                return;
            }
            else if(dir == 3){
                Next3:
                if((searchItem(x, y + 40, BOMB) && flag) || searchItem(x, y + 40, FLASH)) return;
                this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_face.png");
                if(location(x, y + 40) == HARD_WALL || location(x, y + 40) == SOFT_WALL ||  location(x, y + 40) == PLAYER1 || location(x, y + 40) == PLAYER2 || location(x, y + 40) == AI1 || location(x, y + 40) == AI2) goto Next4;
                if(location(x, y + 40) == BOMB){
                    if(!this->getParentGameObject()->getComponent<ItemEffect>()->moveable) return;
                    else{
                        if(location(x, y + 80) == HARD_WALL || location(x, y + 80) == SOFT_WALL || location(x, y + 80) == BOMB) return;
                    }
                }
                this->physics->moveable = true;
                vy += this->getParentGameObject()->getComponent<ItemEffect>()->speed;
                this->physics->setVelocity (vx, vy);
                return;
        }
        else return;
    }
    else return;
}
