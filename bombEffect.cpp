#include "bombEffect.h"

BombEffect :: BombEffect(){}

void BombEffect :: addMove(){
    moveable = true;
    return;
}

void BombEffect :: addPower(){
    if(bombPower < 5) bombPower++;
    return;
}

void BombEffect ::  addBombNum(){
    maxBombNum++;
    restBombNum++;
    return;
}

