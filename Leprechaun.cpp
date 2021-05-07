//
// Created by farah on 25.04.21.
//

#include "Leprechaun.h"
#include <string>
Leprechaun::Leprechaun(int x, int y, int z) {
   this->pos = new Position(x,y,z);
}

Leprechaun::~Leprechaun() {

}

const  string &Leprechaun::getName() const {
    return name;
}
void Leprechaun::mineMaterial(  vector<vector<vector<int> > > &mineField) {
    vector<int> &gameFieldPillar=  mineField[this->getPos()->getX()][this->getPos()->getY()];
     vector<int> swapArray;
    swapArray.assign(10,1);
     swap(gameFieldPillar, swapArray);
    int lostMinePoints = 0;
        for (int & it : swapArray) {
            lostMinePoints+= it;
        }
    this->setTotalPoints(this->getTotalPoints() +lostMinePoints/9);
    //Mine::totalPoints -= lostMinePoints;
}

void Leprechaun::grabMaterial( vector<int> &gamefieldPillar) {

}
