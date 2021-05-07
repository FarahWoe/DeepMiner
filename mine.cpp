//
// Created by farah on 10.04.21.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "mine.h"
#include <cstdlib>
#include <algorithm>
#include <mutex>

std::mutex m;
Mine::Mine() {
    srand(time(NULL));
    botCount = 4;
    zPillar.assign(9, 0);
    randomizeEntries();
    threadRobot();
    //chooseRobot();
    //randomly choose der bots for thread
    bots = new Robot*[this->botCount];
    for(int i= 0; i< botCount; i++) {
        int randVal = rand()%3;
        int randomX = rand() % 3 + 1;
        int randomY = rand() % 3 + 1;
        if(randVal == 0) {
            this->bots[i] = new AllrounderDigger(0,0);
        } else if(randVal == 1) {
                this->bots[i] = new GoldDigger(randomX + 1, randomY);
        }
        else if(randVal == 2) {
            this->bots[i] = new Leprechaun(randomY + 1, randomX);
        }
    }
}

Mine::~Mine() {
    delete[] bots;
}

int Mine::totalPoints;

Position* Mine::positionWithLowestValueOnLevel9;

void Mine::randomizeEntries() {
    srand(time(NULL));
    int randomInt = 0;
    int specialEffects;
    mineField.clear();
    for (int i = 0; i < 5; i++) {
        vector<vector<int> > w;
        mineField.push_back(w);
        for (int j = 0; j < 5; j++) {
            vector<int> v;
            mineField[i].push_back(v);
            for (int k = 0; k < 10; k++) {
                randomInt = rand() % 10 + 1;
                specialEffects =  rand() % 20 + 1;
                if(specialEffects == 10) {
                    mineField[i][j].push_back(-1);          //blocked
                } else if (specialEffects == 9) {
                    mineField[i][j].push_back(-2);          //different position
                } else if(specialEffects == 8) {
                    mineField[i][j].push_back(-3);          //minus 50 Points (<50 then all points are gone)
                } else {
                    mineField[i][j].push_back(randomInt);
                }
                totalPoints += randomInt;
            }
        }
    }
    searchForPositionWithLowestValueOnLevel9();
}

typedef  vector<int> ints;
void Mine::insert( ints &cont, int value ) {
    ints::iterator it =  lower_bound( cont.begin(), cont.end(), value,  less<int>() ); // find proper position in descending order
    cont.insert( it, value ); // insert before iterator it
}

void Mine::rebootMine() {
    totalPoints = 0;
    srand(time(NULL));
    int randomMize;
    int randomInt = 0;
    randomMize = rand() % 3 + 1;
    switch (randomMize) {
        case 1:
            randomizeEntries();         //z-values are randomized (normal way)
            break;
        case 2:                         //z-values are sorted (ascending)
            mineField.clear();
            for (int i = 0; i < 5; i++) {
                vector<vector<int> > w;
                mineField.push_back(w);
                for (int j = 0; j < 5; j++) {
                    vector<int> v;
                    mineField[i].push_back(v);
                    for (int k = 0; k < 10; k++) {
                        //Minus Werte??
                        randomInt = rand() % 10 + 1;
                        insert(mineField[i][j], randomInt); //2
                        totalPoints += randomInt;
                    }
                }
            }
            break;
        case 3:                         //z-values are sorted (descending)
            mineField.clear();
            for (int i = 0; i < 5; i++) {
                vector<vector<int> > w;
                mineField.push_back(w);
                for (int j = 0; j < 5; j++) {
                    vector<int> v;
                    mineField[i].push_back(v);
                    for (int k = 0; k < 10; k++) {
                        //Minus Werte??
                        randomInt = rand() % 10 + 1;
                         auto it =  lower_bound(mineField[i][j].cbegin(), mineField[i][j].cend(), randomInt, [](int a, int b) {return
                                   a >= b;}); //1*/
                        mineField[i][j].insert(it, randomInt);       Missing: https://stackoverflow.com/questions/15843525/how-do-you-insert-the-value-in-a-sorted-vector
                        totalPoints += randomInt;
                    }
                }
            }
    }
    searchForPositionWithLowestValueOnLevel9();
}


int Mine::getValueFromPosition(Position *pos) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == pos->getX() && j == pos->getY()) {
                return mineField[i][j][9];
            }
        }
    }
    return 0;
}

void Mine::chooseRobot() {

//    int randomX = rand() % 3 + 1;
//    int randomY = rand() % 3 + 1;
//    char chooseRobot;
//    while (true) {
//        cout << "Choose your robot: !" << endl;
//        cout << "Allrounder (a)" << endl;
//        cout << "Golddigger (g)" << endl;
//        cout << "Leprechaun (l)" << endl;
//         cin >> chooseRobot;
//        if ((chooseRobot == 'a') || (chooseRobot == 'g') || (chooseRobot == 'l')) {
//            break;
//        }
//         cin.clear();
//         cin.ignore();
//    }
//    switch (chooseRobot) {
//        case 'a':
//            this->robot = new AllrounderDigger(0, 0);
//            this->botOne = new GoldDigger(randomX + 1, randomY);
//            this->botTwo = new Leprechaun(randomY + 1, randomX);
//            break;
//        case 'g':
//            this->robot = new GoldDigger(0, 0);
//            this->botOne = new AllrounderDigger(randomX + 1, randomY);
//            this->botTwo = new Leprechaun(randomY + 1, randomX);
//            break;
//        case 'l':
//            this->robot = new Leprechaun(0, 0);
//            this->botOne = new GoldDigger(randomX + 1, randomY);
//            this->botTwo = new AllrounderDigger(randomY + 1, randomX);
//            break;
//    }
}

void Mine::printMineLevel9() {



    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (j % 5 == 0) {
                cout << endl;
            }
            for(int k = 0; k< botCount; k++) {
                Position *storePosRobot = bots[k]->getPos();
                int storeVal = this->getValueFromPosition(storePosRobot);
                if (i == storePosRobot->getX() && j == storePosRobot->getY()) {
                    cout << setw(2) <<  bots[k]->getId() << " ";
                } else {
                    cout << setw(2) << mineField[i][j][9] << " ";
                }
                mineField[storePosRobot->getX()][storePosRobot->getY()][9] = storeVal;
            }
            cout << endl;
        }
    }


}

void Mine::searchForPositionWithLowestValueOnLevel9() {
    int minVal = INT32_MAX;
    auto* storedPos = new Position(0, 0, 0);
    for(int i = 0; i< 5; i++) {
        for(int j = 0; j< 5; j++) {
            if(mineField[i][j][9] < minVal) {
                minVal = mineField[i][j][9];
                storedPos->setX(i);
                storedPos->setY(j);
                storedPos->setZ(9);
            }
        }
    }
    positionWithLowestValueOnLevel9= storedPos;
}

void Mine::threadRobot() {
    thread threads[botCount];
    for(int i = 0; i< botCount; i++) {
        threads[i] = thread(&Robot::threadMining,  ref(bots[i]),   ref(*this));
    }
    for(int i =0; i <botCount; i++) {
        threads[i].join();
    }
}

void Mine::setField(int x, int y, int value) {
    m.lock();
    mineField[x][y][9] = value;
    m.unlock();
}


template< typename T, typename Pred >
typename  vector<T>::iterator
insert_sorted(  vector<T> & vec, T const& item, Pred pred ){
    return vec.insert( upper_bound( vec.begin(), vec.end(), item, pred ),item);
}


