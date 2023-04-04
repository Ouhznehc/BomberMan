#include "bomb.h"
#include "base.h"
#include "gameobject.h"
#include "itemEffect.h"
#include "transformbuilder.h"
#include "physics.h"
#include "transform.h"
#include <QApplication>
int dx[4] = {40, -40, 0, 0};
int dy[4] = {0, 0, 40, -40};

Bomb :: Bomb(){
    for(int i = 0; i < 12; i++) flash[i] = new GameObject();
}

void Bomb :: onAttach(){
    transform = this->gameObject->getComponent<Transform>();
    assert(transform != nullptr);
}

void Bomb :: onUpdate(float deltaTime){
    if(!isBeginGame) return;
    if(isBombMoving) return;
    bombTime -= deltaTime;
    if(bombTime > 3) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Item/Picture/Item/unit_bombwater_big.png");
    else if(bombTime > 2.5) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Item/Picture/Item/unit_bombwater_small.png");
    else if(bombTime > 2) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Item/Picture/Item/unit_bombwater_big.png");
    else if(bombTime > 1.5) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Item/Picture/Item/unit_bombwater_small.png");
    else if(bombTime > 1) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Item/Picture/Item/unit_bombwater_big.png");
    else if(bombTime > 0.5) this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Item/Picture/Item/unit_bombwater_small.png");
    else if(bombTime > 0)this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Item/Picture/Item/unit_bombwater_big.png");
    if(bombTime > 0) return;
    removeThing(this->getParentGameObject());
    if(!isAddNum)this->owner->getComponent<ItemEffect>()->restBombNum++, isAddNum = true;
    if(flashTime <= 0){
       for(int i = 0; i < 4; i++){
           for(int k = 1; k <= this->owner->getComponent<ItemEffect>()->bombPower; k++){
                int x = this->getParentGameObject()->getComponent<Transform>()->pos().x() + k * dx[i];
                int y = this->getParentGameObject()->getComponent<Transform>()->pos().y() + k * dy[i];
                if(location(x, y) == HARD_WALL) break;
                if(location(x, y) == FLASH) addThing(flash[3*i+k-1], FLOOR);
                assert(flash[3*i+k-1] != nullptr);
                destory(flash[3*i+k-1]);
            }
        }
       if(this->getParentGameObject() == nullptr) return;
       addThing(this->getParentGameObject(), FLOOR);
       destory(this->getParentGameObject());
       return;
    }
    else {
        if(isCheck){
            flashTime -= deltaTime;
            return;
        }
        this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Item/Picture/Item/unit_bombwater_center.png");
        addThing(this->getParentGameObject(), FLASH);
        this->getParentGameObject()->getComponent<Transform>()->setType(FLASH);
        for(int i = 0; i < 4; i++){
           for(int k = 1; k <= this->owner->getComponent<ItemEffect>()->bombPower; k++){
               assert(flash[3*i+k-1] != nullptr);
                int x = this->getParentGameObject()->getComponent<Transform>()->pos().x() + k * dx[i];
                int y = this->getParentGameObject()->getComponent<Transform>()->pos().y() + k * dy[i];
                if(location(x, y) == HARD_WALL || location(x, y) == BOMB){
                    //qDebug("x = %d, y = %d", (y - 100)/ 40, (x - 100) / 40);
                    break;
                }
                if(isSet) goto Check;
                if(i == 2 || i == 3){
                    ImageTransformBuilder()
                        .setPos(QPointF (x, y))
                        .setType(FLASH)
                        .setImage(":/Item/Picture/Item/unit_bombwater_vertical.png")
                        .setAlignment(Qt::AlignCenter)
                        .addToGameObject(flash[3*i+k-1]);
                        this->getParentGameObject()->attachGameObject(flash[3*i+k-1]);
                    flash[3*i+k-1]->getComponent<Transform>()->setZValue((y - 100) / 40);
                    //addThing(flash[3*i+k-1], FLASH);
                }
                else{
                    ImageTransformBuilder()
                        .setPos(QPointF (x, y))
                        .setType(FLASH)
                        .setImage(":/Item/Picture/Item/unit_bombwater_straight.png")
                        .setAlignment(Qt::AlignCenter)
                        .addToGameObject(flash[3*i+k-1]);
                        this->attachGameObject(flash[3*i+k-1]);
                    flash[3*i+k-1]->getComponent<Transform>()->setZValue((y - 100) / 40);
                   // addThing(flash[3*i+k-1], FLASH);
                }
                assert(flash[3*i+k-1] != nullptr);
                if(location(x, y) == SOFT_WALL || location(x, y) == FLASH){
                    addThing(flash[3*i+k-1], FLASH);
                    break;
                }
                else addThing(flash[3*i+k-1], FLASH);
                Check:
                assert(flash[3*i+k-1] != nullptr);
                for(auto item : this->getParentGameObject()->getComponent<Transform>()->collidingItems()){
                    auto trans = dynamic_cast<Transform*>(item);
                    if(trans->type() != FLOOR && trans->type() != FLASH && distance(trans, this->transform) < 40){
                        if(trans->type() == PLAYER1){
                            isPlayer1Live = false;
                            trans->getParentGameObject()->getComponent<ImageTransform>()->setImage("");
                        }
                        else if(trans->type() == PLAYER2){
                            isPlayer2Live = false;
                            trans->getParentGameObject()->getComponent<ImageTransform>()->setImage("");
                        }
                        else if(trans->type() == AI1){
                            isAI1Live = false;
                            trans->getParentGameObject()->getComponent<ImageTransform>()->setImage("");
                        }
                        else if(trans->type() == AI2){
                            isAI2Live = false;
                            trans->getParentGameObject()->getComponent<ImageTransform>()->setImage("");
                        }
                        else  if(trans->type() == BOMB) continue;
                        else destory(trans->getParentGameObject());
                    }

                }
                if(location(x, y) == FLASH){
                    for(auto item : flash[3*i+k-1]->getComponent<Transform>()->collidingItems()){
                        auto trans = dynamic_cast<Transform*>(item);
                        if(trans != nullptr) isCheck = true;
                       // qDebug("%d",trans->type());
                        if(trans == nullptr) continue;
                        if(distance(flash[3*i+k-1]->getComponent<Transform>(), trans) < 40 && trans->type() != FLOOR){
                            if(trans->type() == SOFT_WALL){
                                int num = rand() % 15;
                                //qDebug("%d", num);
                                this->owner->getComponent<ItemEffect>()->score++;
                                if(num == 0 && this->owner->getComponent<Transform>()->type() != AI1 && this->owner->getComponent<Transform>()->type() != AI2){
                                    trans->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Item/Picture/Item/item_71.png");
                                    trans->getParentGameObject()->getComponent<Transform>()->setType(POWER);
                                }
                                else if(num == 1){
                                    trans->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Item/Picture/Item/item_70.png");
                                    trans->getParentGameObject()->getComponent<Transform>()->setType(SPEED);
                                }
                                else if(num == 2 && this->owner->getComponent<Transform>()->type() != AI1 && this->owner->getComponent<Transform>()->type() != AI2){
                                    trans->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Item/Picture/Item/Tutorial_Hand2_1.png");
                                    trans->getParentGameObject()->getComponent<Transform>()->setType(PUSH);
                                }
                                else if(num == 3){
                                    trans->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Item/Picture/Item/item_100.png");
                                    trans->getParentGameObject()->getComponent<Transform>()->setType(ADDBOMB);
                                }
                                else destory(trans->getParentGameObject());
                            }
                            else if(trans->type() == BOMB){
                                //trans->getParentGameObject()->getComponent<Transform>()->setType(FLASH);
                               // trans->getParentGameObject()->getComponent<Bomb>()->bombTime = 0;
                                //break;
                                continue;
                            }
                            else if(trans->type() == FLASH) continue;
                            else if(trans->type() == PLAYER1){
                                isPlayer1Live = false;
                                trans->getParentGameObject()->getComponent<ImageTransform>()->setImage("");
                            }
                            else if(trans->type() == PLAYER2){
                                isPlayer2Live = false;
                                trans->getParentGameObject()->getComponent<ImageTransform>()->setImage("");
                            }
                            else if(trans->type() == AI1){
                                isAI1Live = false;
                                trans->getParentGameObject()->getComponent<ImageTransform>()->setImage("");
                            }
                            else if(trans->type() == AI2){
                                trans->getParentGameObject()->getComponent<ImageTransform>()->setImage("");
                                isAI2Live = false;
                            }
                            else destory(trans->getParentGameObject());
                        }
                    }
                }
            }
        }
        isSet = true;
    }
    flashTime -= deltaTime;
}

void setBomb(GameObject *Owner){
    auto bomb = new GameObject();
    bomb->addComponent(new Bomb());
    bomb->getComponent<Bomb>()->owner = Owner;
    if(location(Owner->getComponent<Transform>()->pos().x(), Owner->getComponent<Transform>()->pos().y()) == BOMB) return;
    Owner->getComponent<ItemEffect>()->restBombNum--;
    ImageTransformBuilder()
        .setPos(QPointF (Owner->getComponent<Transform>()->pos().x(), Owner->getComponent<Transform>()->pos().y()))
        .setType(BOMB)
        .setImage(":/Item/Picture/Item/custom_bubble_big.png")
        .setAlignment(Qt::AlignCenter)
        .addToGameObject(bomb);
        bomb->getComponent<Transform>()->setZValue(((Owner->getComponent<Transform>()->pos().y()) - 100 ) / 40);
        Owner->attachGameObject(bomb);
    addThing(bomb, BOMB);
}
