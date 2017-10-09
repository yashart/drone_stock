#ifndef GRID_H
#define GRID_H

#include "cellnode.h"

class Grid
{
private:
    static const int GRID_WIDTH = 100;
    static const int GRID_HEIGHT = 100;
    int** mask_grid;
public:
    CellNode** grid;
    Grid();
    void distribute_potential(int x, int y, float potential);
    void dump();
    int get_grid_width();
    int get_grid_height();
    ~Grid();
};

#endif // GRID_H
