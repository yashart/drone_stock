#ifndef UNIT_H
#define UNIT_H

#include "grid.h"
#include "point.h"
#include <queue>

class Unit
{
private:
    float potential;
    Grid static_potential;
    int machineNumber;
public:
    Point point;
    Point endPoint;
    std::queue<Point> pheromones;
    Unit(int x, int y, float potential, int number);
    void set_path(int x, int y);
    Grid get_static_potential();
    int get_number();
};

#endif // UNIT_H
