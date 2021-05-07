//
// Created by farah on 25.04.21.
//

#ifndef DEEPMINER_LEPRECHAUN_H
#define DEEPMINER_LEPRECHAUN_H
#include "Robot.h"
using namespace std;

class Leprechaun: public Robot{
public:
    Leprechaun(int x, int y, int =9);
    virtual ~Leprechaun();
private:
     string name= "L";
    void mineMaterial(vector<vector<vector<int> > > &mineField) override;

    void grabMaterial(vector<int>& gamefieldPillar) override;

    const  string &getName() const;
};


#endif //DEEPMINER_LEPRECHAUN_H
