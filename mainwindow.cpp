#include "mainwindow.h"
#include "bomb.h"
#include <gameobject.h>
#include <imagetransform.h>
#include <shooter.h>
#include <summondummy.h>
#include <transformbuilder.h>
#include <physics.h>
#include <usercontroller.h>
#include <hitable.h>
#include "./ui_mainwindow.h"
#include "base.h"
#include "itemEffect.h"
#include "summondummy.h"
#include <QGraphicsEllipseItem>
int Map[15][20] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,2,2,0,2,2,1,0,2,1,0,0,2,1,2,0,0,1,
    1,0,1,2,1,0,1,2,1,0,1,1,0,1,2,1,2,2,0,1,
    1,2,2,0,1,0,1,0,0,2,0,0,2,1,2,1,2,1,2,1,
    1,1,1,2,1,2,1,0,1,1,0,1,0,1,2,1,0,1,2,1,
    1,2,2,2,0,0,2,0,2,0,2,0,2,2,0,2,0,2,2,1,
    1,2,1,2,1,1,0,1,0,1,1,2,0,0,1,1,0,1,2,1,
    1,0,2,0,0,1,0,1,0,1,1,0,1,0,1,0,0,2,0,1,
    1,2,1,0,1,1,2,0,2,1,1,0,1,0,1,1,2,1,2,1,
    1,2,2,0,2,0,2,2,0,2,0,2,0,2,0,0,2,0,0,1,
    1,1,1,0,1,2,1,2,2,0,1,1,0,1,2,0,2,1,1,1,
    1,2,2,2,1,2,1,0,0,0,2,0,0,1,0,1,0,2,2,1,
    1,0,1,1,1,2,1,0,1,1,0,1,2,1,0,1,1,1,0,1,
    1,0,0,2,2,2,0,0,1,2,0,1,0,0,2,2,2,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
void initMap(GameScene *gameScene){
    GameObject *Wall[10][10];
    GameObject* floor[15][20];
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 20; j++){
            floor[i][j] = new GameObject();
                ImageTransformBuilder()
                        .setPos(QPointF(100 + 40 * j,  100 + 40 * i))
                        .setType(FLOOR)
                        .setImage(":/Map/Picture/Map/map_ice_tile2.png")
                            .setAlignment(Qt::AlignCenter)
                        .addToGameObject(floor[i][j]);
                gameScene->attachGameObject(floor[i][j]);
        }
    }
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 20; j++){
            if(!Map[i][j]) continue;
            auto map = new GameObject();
            if(Map[i][j] == 1){
                ImageTransformBuilder()
                        .setPos(QPointF(100 + 40 * j,  100 + 40 * i))
                        .setType(HARD_WALL)
                        .setImage(":/Map/Picture/Map/map_ice_tile6.png")
                            .setAlignment(Qt::AlignCenter)
                        .addToGameObject(map);
                gameScene->attachGameObject(map);
            }
            if(Map[i][j] == 2){
                ImageTransformBuilder()
                        .setPos(QPointF(100 + 40 * j,  100 + 40 * i))
                        .setType(SOFT_WALL)
                        .setImage(":/Map/Picture/Map/map_ice_object5.png")
                            .setAlignment(Qt::AlignCenter)
                        .addToGameObject(map);
                gameScene->attachGameObject(map);
            }
            map->getComponent<Transform>()->setZValue(i);
        }
    }
    ImageTransformBuilder()
        .setPos(QPointF(140, 140))
        .setType(PLAYER1)
        .setImage(":/Player/Picture/Player/player1_face.png")
            .setAlignment(Qt::AlignCenter)
        .addToGameObject(player1);
    player1->addComponent(new Physics());
    player1->getComponent<Physics>()->setType(PLAYER1);
    player1->addComponent(new UserController());
    player1->getComponent<UserController>()->setType(PLAYER1);
    player1->addComponent(new ItemEffect());
    player1->getComponent<ItemEffect>()->setType(PLAYER1, gameScene);
    gameScene->attachGameObject(player1);
    ImageTransformBuilder()
        .setPos(QPointF(100 + 40 * 18, 140))
        .setType(PLAYER2)
        .setImage(":/Player/Picture/Player/player2_face.png")
            .setAlignment(Qt::AlignCenter)
        .addToGameObject(player2);
    player2->addComponent(new Physics());
    player2->getComponent<Physics>()->setType(PLAYER2);
    player2->addComponent(new UserController());
    player2->getComponent<UserController>()->setType(PLAYER2);
    player2->addComponent(new ItemEffect());
    player2->getComponent<ItemEffect>()->setType(PLAYER2, gameScene);
    gameScene->attachGameObject(player2);
    ImageTransformBuilder()
        .setPos(QPointF(100 + 40 * 1, 100 + 40 * 13))
        .setType(AI1)
        .setImage(":/Player/Picture/Player/AI1_face.png")
            .setAlignment(Qt::AlignCenter)
        .addToGameObject(Ai1);
    Ai1->addComponent(new Physics());
    Ai1->getComponent<Physics>()->setType(AI1);
    Ai1->addComponent(new UserController());
    Ai1->getComponent<UserController>()->setType(AI1);
    Ai1->addComponent(new ItemEffect());
    Ai1->getComponent<ItemEffect>()->setType(AI1, gameScene);
    gameScene->attachGameObject(Ai1);
    ImageTransformBuilder()
        .setPos(QPointF(100 + 40 * 18, 100 + 40 * 13))
        .setType(AI2)
        .setImage(":/Player/Picture/Player/AI2_face.png")
            .setAlignment(Qt::AlignCenter)
        .addToGameObject(Ai2);
    Ai2->addComponent(new Physics());
    Ai2->getComponent<Physics>()->setType(AI2);
    Ai2->addComponent(new UserController());
    Ai2->getComponent<UserController>()->setType(AI2);
    Ai2->addComponent(new ItemEffect());
    Ai2->getComponent<ItemEffect>()->setType(AI2, gameScene);
    gameScene->attachGameObject(Ai2);
    auto score = new GameObject();
    ImageTransformBuilder()
        .setPos(QPointF(100 + 40 * 22, 100 + 40 * 6))
        .setType(HARD_WALL)
        .setImage(":/Others/Picture/Others/score.png")
            .setAlignment(Qt::AlignCenter)
        .addToGameObject(score);
    score->getComponent<Transform>()->setZValue(99);
    gameScene->attachGameObject(score);
}
void loadScene(GameScene *gameScene) {
  initMap(gameScene);
  ImageTransformBuilder()
      .setPos(QPointF(100 + 40 * 14, 100 + 40 * 10))
      .setImage(":/Player/Picture/Others/bg_lobby.png")
          .setAlignment(Qt::AlignCenter)
      .addToGameObject(backGround);
  backGround->getComponent<Transform>()->setZValue(100);
  gameScene->attachGameObject(backGround);
  ImageTransformBuilder()
      .setPos(QPointF(100 + 40 * 11, 100 + 40 * 2))
      .setImage(":/Player/Picture/Others/Title_logo.png")
          .setAlignment(Qt::AlignCenter)
      .addToGameObject(bomberMan);
  bomberMan->getComponent<Transform>()->setZValue(100);
  gameScene->attachGameObject(bomberMan);
  ImageTransformBuilder()
      .setPos(QPointF(100 + 40 * 7, 100 + 40 * 15))
      .setImage(":/Others/Picture/Others/begin2.png")
          .setAlignment(Qt::AlignCenter)
      .addToGameObject(beginGame);
  beginGame->addComponent(new SummonDummy());
  beginGame->getComponent<Transform>()->setZValue(100);
  beginGame->getComponent<SummonDummy>()->setType(BEGIN_GAME);
  gameScene->attachGameObject(beginGame);
  ImageTransformBuilder()
      .setPos(QPointF(100 + 40 * 25, 100 + 40 * 0))
      .setImage(":/Player/Picture/Others/help.png")
          .setAlignment(Qt::AlignCenter)
      .addToGameObject(help);
  help->addComponent(new SummonDummy());
  help->getComponent<Transform>()->setZValue(101);
  help->getComponent<SummonDummy>()->setType(HELP);
  gameScene->attachGameObject(help);
  ImageTransformBuilder()
      .setPos(QPointF(100 + 40 * 21, 100 + 40 * 17))
      .setImage(":/Player/Picture/Others/exit.png")
          .setAlignment(Qt::AlignCenter)
      .addToGameObject(endGame);
  endGame->addComponent(new SummonDummy());
  endGame->getComponent<Transform>()->setZValue(100);
  endGame->getComponent<SummonDummy>()->setType(END_GAME);
  gameScene->attachGameObject(endGame);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  gameScene = new GameScene();
  gameScene->setParent(this);
  auto view = new QGraphicsView(gameScene, this);
  view->setFrameStyle(QFrame::NoFrame);
  view->resize(this->size());
  view->setSceneRect(QRect(0, 0, this->width(), this->height()));
  //view->setViewportUpdateMode(QGraphicsView:: BoundingRectViewportUpdate);
  view->setViewportUpdateMode((QGraphicsView:: FullViewportUpdate));
  loadScene(gameScene);
}

MainWindow::~MainWindow() { delete ui; }
