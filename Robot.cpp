//
// Created by farah on 10.04.21.
//
#include <iostream>
#include "Robot.h"
#include "mine.h"

Robot::Robot() {

}

Robot::~Robot() {

}

bool Robot::botMove() {
    srand(time(NULL));
    int randomInt = 0;
    randomInt = rand() % 4 + 1;
    bool moved = false;
    while (!moved) {
        switch (randomInt) {
            case 1:
                if (pos->x != 0) {
                    pos->x--;
                } else {
                    return false;
                }
                break;
            case 2:
                if (pos->y != 4) {
                    pos->y++;
                } else {
                    return false;
                }
                break;
            case 3:
                if (pos->x != 4) {
                    pos->x++;
                } else {
                    return false;
                }
                break;
            case 4:
                if (pos->y != 0) {
                    pos->y--;
                } else {
                    return false;
                }
                break;
        }
        moved = true;
    }
    return moved;
}

bool Robot::move() {
    char direction;
    while (true) {
         cout << "Please enter w, a, s, d" <<  endl;
         cin >> direction;
        if ((direction == 'w') || (direction == 'a') || (direction == 's') || (direction == 'd')) {
            break;
        }
         cin.clear();
         cin.ignore();
    }
    switch (direction) {
        case 'w':
            if (pos->x != 0) {
                pos->x--;
            } else {
                return false;
            }
            break;
        case 'd':
            if (pos->y != 4) {
                pos->y++;
            } else {
                return false;
            }
            break;
        case 's':
            if (pos->x != 4) {
                pos->x++;
            } else {
                return false;
            }
            break;
        case 'a':
            if (pos->y != 0) {
                pos->y--;
            } else {
                return false;
            }
            break;
    }
    //sollte seine neue Position zurrückgeben
    return true;

}

Position *Robot::getPos() const {
    return pos;
}

void Robot::setPos(Position *pos) {
    Robot::pos = pos;
}

int Robot::getTotalPoints() const {
    return totalPoints;
}

void Robot::setTotalPoints(int totalPoints) {
    Robot::totalPoints = totalPoints;
}

bool Robot:: checkForSpecialEffects( vector<int> &gameFieldPillar) {
    Position position;
    int negativeVal;
    bool hasEffect = false;
    for (int & it : gameFieldPillar) {
       if(it < 0 ) {
           negativeVal = it;
           hasEffect = true;
           it = 0;
           break;
       }
    }
    if(hasEffect) {
        switch (negativeVal) {
            case -1:
                return false;            //robot is not allowed to mine
            case -2:
               this->setPos(Mine::positionWithLowestValueOnLevel9);
                //this->pos     //changed
                //iterate threw mine at z=9 and find minimum
                return true;                 //is allowed to mine, but on different position
            case -3 :
                if(this->totalPoints <=50) {
                    this->totalPoints = 0;
                } else {
                    this->totalPoints -=50;
                }
                return true;                //is allowed to mine
        }
    }
        return true;
}

void Robot::threadMining(Mine& mine) {
    while (!mine.gameEnd) {

        for(int i = 0; i< mine.botCount; i++) {
            if(this->move()) {
                cout <<"Bot " << ID<<"'s position is x: " << this->pos->x << " y: "<< this->pos->y;
                this->mineMaterial(mine.mineField);
                cout << " Total Points: " << this->totalPoints;
            } else {
                cout <<"Bot " << ID<< " didn't move";
            }
        }
        mine.printMineLevel9();
        if (this->totalPoints / 50 >= mine.mineRebootCounter) {
            mine.mineRebootCounter++;
            cout << "Mine is rebooted";
            mine.rebootMine();
        }
        if (this->totalPoints >= 200) {
            cout << "Bot "<<ID<< " won" <<endl;
            mine.gameEnd = true;
        }
        //MISSING: if robots meet

    }
}

int Robot::getId() const {
    return ID;
}

void Robot::setId(int id) {
    ID = id;
}
