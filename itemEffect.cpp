#include "itemEffect.h"
#include "gameobject.h"
#include "component.h"
#include "transform.h"
#include "imagetransform.h"
#include "transformbuilder.h"
#include "base.h"
ItemEffect :: ItemEffect(){
    life = new GameObject();
    Speed = new GameObject();
    power = new GameObject();
    number = new GameObject();
    score_1 = new GameObject();
    score_2 = new GameObject();
}

void ItemEffect ::  setType(int x, GameScene* gameScene){
    type = x;
    if(x == PLAYER1){
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 4, 100 + 40 * 0))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(life);
        life->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(life);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 4, 100 + 28))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(number);
        number->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(number);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 4, 100 + 54))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(power);
        power->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(power);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 4, 100 + 81))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(Speed);
        Speed->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(Speed);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 21 - 4, 100 + 86))
            .setImage(":/Others/Picture/Others/0.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(score_1);
        score_1->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(score_1);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 21 + 14, 100 + 86))
            .setImage(":/Others/Picture/Others/0.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(score_2);
        score_2->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(score_2);
        return;
    }
    if(x == PLAYER2){
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 4, 100 + 40 * 3 + 15))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(life);
        life->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(life);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 4, 100 + 28 + 135))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(number);
        number->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(number);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 4, 100 + 54 + 135))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(power);
        power->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(power);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 4, 100 + 81 + 135))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(Speed);
        Speed->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(Speed);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 21 - 4, 100 + 86 + 136))
            .setImage(":/Others/Picture/Others/0.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(score_1);
        score_1->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(score_1);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 21 + 14, 100 + 86 + 136))
            .setImage(":/Others/Picture/Others/0.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(score_2);
        score_2->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(score_2);
        return;
    }
    if(x == AI1){
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 4, 100 + 135 * 2))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(life);
        life->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(life);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 4, 100 + 28 + 135 * 2))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(number);
        number->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(number);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 4, 100 + 54 + 135 * 2))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(power);
        power->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(power);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 4, 100 + 81 + 135 * 2))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(Speed);
        Speed->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(Speed);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 21 - 4, 100 + 86 + 136 * 2 - 2))
            .setImage(":/Others/Picture/Others/0.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(score_1);
        score_1->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(score_1);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 21 + 14, 100 + 86 + 136 * 2 - 2))
            .setImage(":/Others/Picture/Others/0.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(score_2);
        score_2->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(score_2);
        return;
    }
    if(x == AI2){
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 2, 100 + 135 * 3 + 2))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(life);
        life->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(life);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 2, 100 + 28 + 135 * 3 + 2))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(number);
        number->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(number);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 2, 100 + 54 + 135 * 3 + 2))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(power);
        power->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(power);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 24 - 2, 100 + 81 + 135 * 3 + 2))
            .setImage(":/Others/Picture/Others/1.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(Speed);
        Speed->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(Speed);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 21 - 4, 100 + 86 + 136 * 3 ))
            .setImage(":/Others/Picture/Others/0.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(score_1);
        score_1->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(score_1);
        ImageTransformBuilder()
            .setPos(QPointF(100 + 40 * 21 + 14, 100 + 86 + 136 * 3 ))
            .setImage(":/Others/Picture/Others/0.png")
                .setAlignment(Qt::AlignCenter)
            .addToGameObject(score_2);
        score_2->getComponent<Transform>()->setZValue(100);
        gameScene->attachGameObject(score_2);
        return;
    }
}
void ItemEffect :: change(GameObject* obj, int num){
    if(num == 0) obj->getComponent<ImageTransform>()->setImage(":/Others/Picture/Others/0.png");
    if(num == 1) obj->getComponent<ImageTransform>()->setImage(":/Others/Picture/Others/1.png");
    if(num == 2) obj->getComponent<ImageTransform>()->setImage(":/Others/Picture/Others/2.png");
    if(num == 3) obj->getComponent<ImageTransform>()->setImage(":/Others/Picture/Others/3.png");
    if(num == 4) obj->getComponent<ImageTransform>()->setImage(":/Others/Picture/Others/4.png");
    if(num == 5) obj->getComponent<ImageTransform>()->setImage(":/Others/Picture/Others/5.png");
    if(num == 6) obj->getComponent<ImageTransform>()->setImage(":/Others/Picture/Others/6.png");
    if(num == 7) obj->getComponent<ImageTransform>()->setImage(":/Others/Picture/Others/7.png");
    if(num == 8) obj->getComponent<ImageTransform>()->setImage(":/Others/Picture/Others/8.png");
    if(num == 9) obj->getComponent<ImageTransform>()->setImage(":/Others/Picture/Others/9.png");
}

void ItemEffect :: onUpdate(float deltaTime){
     if(!isPlayer1Live) change(player1->getComponent<ItemEffect>()->life, 0);
     if(!isPlayer2Live) change(player2->getComponent<ItemEffect>()->life, 0);
     if(!isAI1Live) change(Ai1->getComponent<ItemEffect>()->life, 0);
     if(!isAI2Live) change(Ai2->getComponent<ItemEffect>()->life, 0);
     if(this->speed == 125) change(this->Speed, 2);
     if(this->speed == 250) change(this->Speed, 3);
     change(this->power, this->bombPower);
     change(this->number, this->maxBombNum);
     change(this->score_1, this->score / 10);
     change(this->score_2, this->score % 10);
     return;
}

void ItemEffect :: addMove(){
    moveable = true;
    return;
}
void ItemEffect :: addPower(){
    if(bombPower < 3) bombPower++;
    return;
}

void ItemEffect ::  addBombNum(){
    if(maxBombNum < 9){
        maxBombNum++;
        restBombNum++;
    }
    return;
}

