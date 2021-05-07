#include "AllrounderDigger.h"

AllrounderDigger::AllrounderDigger(int x, int y, int z) {
    this->pos = new Position(x,y,z);
};

AllrounderDigger::~AllrounderDigger() {

}

void AllrounderDigger::mineMaterial( vector<vector<vector<int> > > &mineField) {
    vector<int> &gameFieldPillar=  mineField[this->getPos()->getX()][this->getPos()->getY()];
    if(checkForSpecialEffects(gameFieldPillar)) {
        int counter = 0;
        auto it = gameFieldPillar.begin();
        while(counter != 3) {
            this->totalPoints += *it;
            //Mine::totalPoints -= *it;
            gameFieldPillar[counter] = 0;
            it++;
            counter++;
        }
    }
}

void AllrounderDigger::grabMaterial( vector<int> &gamefieldPillar) {

}

const  string &AllrounderDigger::getName() const {
    return name;
}

void AllrounderDigger::setName(const  string &name) {
    AllrounderDigger::name = name;
}
