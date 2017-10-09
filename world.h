#ifndef WORLD_H
#define WORLD_H

#include <unit.h>
#include <queue>

class World
{
private:
    int mashinesSolved;
public:
    std::queue<Unit> units;

    World();
    void add_unit(int startX, int startY,
                  int endX, int endY, int number);
    void dump();
    float point_potential(int x, int y, Unit unit);
    void dump_for_units();
    void move_units();
    int check_solved();
};

#endif // WORLD_H
