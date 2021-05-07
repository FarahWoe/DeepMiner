#ifndef DEEPMINER_MINE_H
#define DEEPMINER_MINE_H

#include "Robot.h"
#include "GoldDigger.h"
#include "AllrounderDigger.h"
#include "Leprechaun.h"
#include <pthread.h>

using namespace std;

class Mine {
    public:
        Mine();
        virtual ~Mine();
        static int totalPoints;
        static Position* positionWithLowestValueOnLevel9;
        Position* robotPos;
        void printMineLevel9();
        void threadRobot();
        int botCount;
        bool gameEnd = false;
        vector<vector<vector<int> > > mineField;
        void rebootMine();
        int mineRebootCounter = 1;
        void setField(int x, int y, int value);
    private:
        vector<int> zPillar;
        void randomizeEntries();
        void chooseRobot();
        int getValueFromPosition(Position* pos);
    //    Robot* robot;
    //    Robot* botOne;
    //    Robot* botTwo;
        Robot** bots;
        void searchForPositionWithLowestValueOnLevel9();
        void insert(vector<int> &cont, int value);
};
#endif //DEEPMINER_MINE_H
