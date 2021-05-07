//
// Created by farah on 10.04.21.
//
#include "GoldDigger.h"
#include "Robot.h"
#include "vector"
#include "algorithm"

GoldDigger::GoldDigger(int x, int y, int z) {
    this->pos = new Position(x,y,z);
};


GoldDigger::~GoldDigger() {

}

void GoldDigger::mineMaterial(  vector<vector<vector<int> > > &mineField) {
    vector<int> &gameFieldPillar=  mineField[this->getPos()->getX()][this->getPos()->getY()];
    //overload operator, so that it works in ascending order
    struct comparator{
        bool operator()(int a, int b) {
            return a < b;
        }
    }comparator;
   //  vector<int> sortedGamefieldPillarDesc = {9,8,7,6,5,4,3,2,1};9};
    //check if array is sorted
    if(!is_sorted(gameFieldPillar.begin(), gameFieldPillar.end(), comparator)) {
            sort(gameFieldPillar.begin(), gameFieldPillar.end(), comparator);
    }
    grabMaterial(gameFieldPillar);

}
void GoldDigger::grabMaterial( vector<int>& gamefieldPillar) {
    this->totalPoints += gamefieldPillar[9];
    //Mine::totalPoints -= gamefieldPillar[9];
    gamefieldPillar[9] = 0;
}

const string &GoldDigger::getName() const {
    return name;
}

void GoldDigger::setName(const string &name) {
    GoldDigger::name = name;
}

