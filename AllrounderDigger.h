#ifndef DEEPMINER_ALLROUNDERDIGGER_H
#define DEEPMINER_ALLROUNDERDIGGER_H
#include "Robot.h"
#include <string>
using namespace std;
class AllrounderDigger: public Robot {
public:

    AllrounderDigger(int x, int y, int =9);
    virtual ~AllrounderDigger();

    const string &getName() const;

    void setName(const string &name);

private:

    string name= "A";
    void mineMaterial(vector<vector<vector<int> > > &mineField) override;

    void grabMaterial(vector<int>& gamefieldPillar) override;
};
#endif //DEEPMINER_ALLROUNDERDIGGER_H
