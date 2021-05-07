//
// Created by farah on 10.04.21.
//

#ifndef DEEPMINER_POSITION_H
#define DEEPMINER_POSITION_H
class Position {
public:
    int x;
    int y;
    int z;
    Position(int x, int y, int z) ;

    Position();

    virtual ~Position();

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    int getZ() const;

    void setZ(int z);

};
#endif //DEEPMINER_POSITION_H
