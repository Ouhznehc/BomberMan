#include "summondummy.h"

#include <gameobject.h>
#include <transform.h>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include "base.h"
#include "health.h"
#include "imagetransform.h"
#include <transformbuilder.h>
SummonDummy::SummonDummy() {}

void SummonDummy :: setType(int type){
    my_type = type;
}

int SummonDummy :: type(){
    return my_type;
}

void SummonDummy::onAttach() {
  auto transform = this->gameObject->getComponent<Transform>();
  Q_ASSERT(transform != nullptr);
  // Handle mouse event of text by this->transform
  transform->setFiltersChildEvents(true);
}

void SummonDummy::onClick(QGraphicsSceneMouseEvent *ev) {
  //this->gameObject->removeComponent(this);
   if(this->type() == STOP_GAME){
       if(isBeginGame == true){
           isBeginGame = false;
           this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Others/stop.png");
           return;
       }
       if(isBeginGame == false){
           isBeginGame = true;
           this->getParentGameObject()->getComponent<ImageTransform>()->setImage(":/Player/Picture/Others/continue.png");
           return;
       }
   }
   else if(this->type() == BEGIN_GAME){
       isBeginGame = true;
       backGround->getComponent<ImageTransform>()->setImage("");
       bomberMan->getComponent<ImageTransform>()->setImage("");
       help->getComponent<ImageTransform>()->setImage("");
       endGame->getComponent<ImageTransform>()->setImage("");
       this->gameObject->getComponent<ImageTransform>()->setImage("");
       ImageTransformBuilder()
           .setPos(QPointF(100 + 40 * 21, 100 + 40 * 14))
           .setImage(":/Player/Picture/Others/continue.png")
           .setAlignment(Qt::AlignCenter)
           .addToGameObject(stopGame);
       stopGame->addComponent(new SummonDummy());
       stopGame->getComponent<Transform>()->setZValue(99);
       stopGame->getComponent<SummonDummy>()->setType(STOP_GAME);
       this->attachGameObject(stopGame);
      //destory(this->getParentGameObject());
    }
   else if(this->type() == END_GAME){
       QApplication :: quit();
   }
   else if(this->type() == HELP){
       this->setType(BACK);
       ImageTransformBuilder()
           .setPos(QPointF(100 + 40 * 14, 100 + 40 * 10))
           .setImage(":/Others/Picture/Others/paper.png")
               .setAlignment(Qt::AlignCenter)
           .addToGameObject(helpScene);
       helpScene->getComponent<Transform>()->setZValue(100);
       this->attachGameObject(helpScene);
       helpScene->getComponent<ImageTransform>()->setImage(":/Others/Picture/Others/paper.png");
       endGame->getComponent<ImageTransform>()->setImage("");
       beginGame->getComponent<ImageTransform>()->setImage("");
       this->gameObject->getComponent<ImageTransform>()->setImage(":/Player/Picture/Others/exit1.png");
   }
   else if(this->type() == BACK){
       this->setType(HELP);
       this->gameObject->getComponent<ImageTransform>()->setImage(":/Player/Picture/Others/help.png");
       beginGame->getComponent<ImageTransform>()->setImage(":/Others/Picture/Others/begin2.png");
       endGame->getComponent<ImageTransform>()->setImage(":/Player/Picture/Others/exit.png");
       helpScene->getComponent<ImageTransform>()->setImage("");
   }
}
