//
// Created by farah on 10.04.21.
//

#ifndef DEEPMINER_GOLDDIGGER_H
#define DEEPMINER_GOLDDIGGER_H
#include "Robot.h"
#include <vector>
#include <string>
using namespace std;
class GoldDigger: public Robot {

public:
    GoldDigger(int x, int y, int =9);

    virtual ~GoldDigger();

    const string &getName() const;

    void setName(const  string &name);
private:
     string name= "G";
    void mineMaterial( vector<vector<vector<int> > > &mineField) override;

    void grabMaterial(vector<int>& gamefieldPillar) override;
};
#endif //DEEPMINER_GOLDDIGGER_H
