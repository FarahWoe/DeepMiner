#ifndef DEEPMINER_ROBOT_H
#define DEEPMINER_ROBOT_H

#include <vector>
#include "position.h"
#include <string>
#include <thread>
using namespace std;

class Mine;

class Robot{
public:
    Robot();
    virtual ~Robot();
    virtual void mineMaterial( vector<vector<vector<int> > > &mineField) = 0;
    virtual const  string &getName() const = 0;
    virtual void grabMaterial(vector<int>& gamefieldPillar) = 0;
    bool move();
    Position *getPos() const;
    void setPos(Position *pos);
    int getTotalPoints() const;
    void setTotalPoints(int totalPoints);
    bool botMove();
    void threadMining(Mine& mine);
    int getId() const;
    void setId(int id);

protected:
    int totalPoints = 0;
    Position* pos;
    int ID;
    bool checkForSpecialEffects( vector<int> &gameFieldPillar);
};
#endif //DEEPMINER_ROBOT_H


