#include "physics.h"
#include "transformbuilder.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include "gameobject.h"
#include "component.h"
#include "base.h"
#include "hitable.h"
#include "bomb.h"
#include "itemEffect.h"
Physics :: Physics(){}

void Physics ::  setType(int type){
    this->my_type = type;
}

int Physics :: type(){
    return my_type;
}

void Physics :: onAttach(){
    transform = this->gameObject->getComponent<Transform>();
    assert(transform != nullptr);
}
void Physics :: onUpdate(float deltaTime){
    if(!isBeginGame) return;
    if(this->type() == PLAYER1 && !isPlayer1Live) return;
    if(this->type() == PLAYER2 && !isPlayer2Live) return;
    if(this->type() == AI1 && !isAI1Live) return;
    if(this->type() == AI2 && !isAI2Live) return;
    int dx = vx / fabs(vx), dy = vy / fabs(vy);
    if(this->type() == PLAYER1 || this->type() == PLAYER2 || this->type() == AI1 || this->type() == AI2){
        if(!moveable){
            return;
        }
        if(changeTime >= 0) changeTime -= deltaTime;
        else{
            if(this->type() == PLAYER1 && isPlayer1Live){
                if(vx == 0 && vy > 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_face_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_face_2.png");
                }
                if(vx == 0 && vy < 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_back_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_back_2.png");
                }
                if(vx > 0 && vy == 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_right_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_right_2.png");
                }
                if(vx < 0 && vy == 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_left_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_left_2.png");
                }
                changeSign ^= 1;
                changeTime = 0.2;
            }
            if(this->type() == PLAYER2 && isPlayer2Live){
                if(vx == 0 && vy > 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_face_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_face_2.png");
                }
                if(vx == 0 && vy < 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_back_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_back_2.png");
                }
                if(vx > 0 && vy == 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_right_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_right_2.png");
                }
                if(vx < 0 && vy == 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_left_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_left_2.png");
                }
                changeSign ^= 1;
                changeTime = 0.2;
            }
            if(this->type() == AI1 && isAI1Live){
                if(vx == 0 && vy > 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_face_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_face_2.png");
                }
                if(vx == 0 && vy < 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_back_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_back_2.png");
                }
                if(vx > 0 && vy == 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_right_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_right_2.png");
                }
                if(vx < 0 && vy == 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_left_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_left_2.png");
                }
                changeSign ^= 1;
                changeTime = 0.2;
            }
            if(this->type() == AI2 && isAI2Live){
                if(vx == 0 && vy > 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_face_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_face_2.png");
                }
                if(vx == 0 && vy < 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_back_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_back_2.png");
                }
                if(vx > 0 && vy == 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_right_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_right_2.png");
                }
                if(vx < 0 && vy == 0){
                    if(changeSign) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_left_1.png");
                    else this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_left_2.png");
                }
                changeSign ^= 1;
                changeTime = 0.2;
            }

        }
        this->transform->moveBy(deltaTime * vx, deltaTime * vy);
        if(this->getParentGameObject()->getComponent<ItemEffect>()->moveable){
            for(auto item : this->transform->collidingItems()){
                auto trans = dynamic_cast<Transform*>(item);
                if(trans->type() == BOMB && distance(trans, this->transform) < 40){
                    auto temp = new Transform();
                    temp->setPos(this->transform->pos().x() - deltaTime * vx, this->transform->pos().y() - deltaTime * vy);
                    if(distance(temp, trans) > distance(this->transform, trans)){
                        addThing(trans->getParentGameObject(), FLOOR);
                        trans->getParentGameObject()->addComponent(new Physics());
                        trans->getParentGameObject()->getComponent<Physics>()->onAttach();
                        trans->getParentGameObject()->getComponent<Physics>()->setType(BOMB);
                        trans->getParentGameObject()->getComponent<Physics>()->setVelocity(500 * dx, 500 * dy);
                        trans->getParentGameObject()->getComponent<Bomb>()->isBombMoving = true;
                        trans->getParentGameObject()->getComponent<Physics>()->moveable = true;
                    }
                }
                if(trans->type() == FLASH && distance(trans, this->transform) < 40){
                    if(this->type() == PLAYER1){
                        isPlayer1Live = false;
                        addThing(trans->getParentGameObject(), FLOOR);
                        this->getParentGameObject()->getComponent<ImageTransform>()->setImage("");
                    }
                    else if(this->type() == PLAYER2){
                        isPlayer2Live = false;
                        addThing(trans->getParentGameObject(), FLOOR);
                        this->getParentGameObject()->getComponent<ImageTransform>()->setImage("");
                    }
                    else if(this->type() == AI1){
                        isAI1Live = false;
                        this->getParentGameObject()->getComponent<ImageTransform>()->setImage("");
                    }
                    else if(this->type() == AI2){
                        isAI2Live = false;
                        this->getParentGameObject()->getComponent<ImageTransform>()->setImage("");
                    }
                }
            }
        }

        if(checkAchieve(this->transform)){
            moveable = false;
            if(this->type() == PLAYER1 && !isPlayer1Live) return;
            if(this->type() == PLAYER2 && !isPlayer2Live) return;
            if(this->type() == AI1 && !isAI1Live) return;
            if(this->type() == AI2 && !isAI2Live) return;
            if(this->type() == PLAYER1){
                if(vx == 0 && vy > 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_face.png");
                if(vx == 0 && vy < 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_back.png");
                if(vx > 0 && vy == 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_right.png");
                if(vx < 0 && vy == 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player1_left.png");
            }
            if(this->type() == PLAYER2){
                if(vx == 0 && vy > 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_face.png");
                if(vx == 0 && vy < 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_back.png");
                if(vx > 0 && vy == 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_right.png");
                if(vx < 0 && vy == 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/player2_left.png");
            }
            if(this->type() == AI1){
                if(vx == 0 && vy > 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_face.png");
                if(vx == 0 && vy < 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_back.png");
                if(vx > 0 && vy == 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_right.png");
                if(vx < 0 && vy == 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI1_left.png");
            }
            if(this->type() == AI2){
                if(vx == 0 && vy > 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_face.png");
                if(vx == 0 && vy < 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_back.png");
                if(vx > 0 && vy == 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_right.png");
                if(vx < 0 && vy == 0) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Player/AI2_left.png");
            }
            if(this->type() == PLAYER1 && isPlayer1Live){
                addThing(this->getParentGameObject(), PLAYER1);
            }
            if(this->type() == PLAYER2 && isPlayer1Live){
                addThing(this->getParentGameObject(), PLAYER2);
            }
            this->transform->setZValue((this->transform->pos().y() - 100)/40);
            for(auto item : this->transform->collidingItems()){
                auto trans = dynamic_cast<Transform*>(item);
                if(trans->type() != FLOOR && distance(trans, this->transform) < 40 && trans->type() != BOMB){
                    if(trans->type() == ADDBOMB){
                        this->getParentGameObject()->getComponent<ItemEffect>()->addBombNum();
                        addThing(trans->getParentGameObject(), FLOOR);
                    }
                    if(trans->type() == SPEED){
                        if(this->getParentGameObject()->getComponent<ItemEffect>()->speed < 250)
                            this->getParentGameObject()->getComponent<ItemEffect>()->speed *= 2;
                        addThing(trans->getParentGameObject(), FLOOR);
                    }
                    if(trans->type() == POWER){
                        addThing(trans->getParentGameObject(), FLOOR);
                        this->getParentGameObject()->getComponent<ItemEffect>()->addPower();
                    }
                    if(trans->type() == PUSH){
                        addThing(trans->getParentGameObject(), FLOOR);
                        this->getParentGameObject()->getComponent<ItemEffect>()->addMove();
                    }
                    if(trans->type() == PLAYER1 || trans->type() == AI1 || trans->type() == PLAYER2 || trans->type() == AI2) continue;
                    destory(trans->getParentGameObject());
                }
            }
            return;
        }
    }
    if(this->type() == BOMB){
        if(!moveable) return;
        assert(this->transform != nullptr);
        this->transform->moveBy(deltaTime * vx, deltaTime * vy);
        if(checkAchieve(this->transform)){
            int x = this->transform->pos().x();
            int y = this->transform->pos().y();
            if(location(x + 40 * dx, y + 40 * dy) == HARD_WALL || location(x + 40 * dx, y + 40 * dy) == SOFT_WALL || location(x + 40 * dx, y + 40 * dy) == BOMB){
                moveable = false;
                this->getParentGameObject()->getComponent<Bomb>()->isBombMoving = false;
                addThing(this->getParentGameObject(), BOMB);
                this->transform->setZValue((this->transform->pos().y() - 100)/40);
            }
        }
    }
}
void Physics ::  setVelocity(float vx, float vy){
    this->vx = vx;
    this->vy = vy;
}
