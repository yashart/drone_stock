#include "world.h"
#include <iostream>
#include <algorithm>

World::World()
{
    this->mashinesSolved = 0;
}

void World::add_unit(int startX, int startY,
              int endX, int endY, int number) {
    Unit unit(startX, startY, -100, number);
    unit.set_path(endX, endY);
    this->units.push(unit);
}

float World::point_potential(int x, int y, Unit unit) {
    float staticPotential = unit.get_static_potential().grid[x][y].get_potential();
    std::queue<Point> pheromones = unit.pheromones;
    std::queue<Unit> units = this->units;
    float dinamicPotential = 0;
    while (!pheromones.empty()) {
        Point point = pheromones.front();
        if (point.x == x && point.y == y) {
            dinamicPotential -= 0.4;
        }
        pheromones.pop();
    }
    while (!units.empty()) {
        Point point = units.front().point;
        if (point.x == x && point.y == y) {
            dinamicPotential -= 100;
        }
        if ((point.x - x)*(point.x - x) + (point.y - y)*(point.y - y) == 1) {
            dinamicPotential -= 0.2;
        }

        units.pop();
    }
    return staticPotential + dinamicPotential;
}

void World::dump() {
    int gridWidth = this->units.front().get_static_potential().get_grid_width();
    int gridHeight = this->units.front().get_static_potential().get_grid_height();
    int array[gridWidth][gridHeight] = {};
    std::queue<Unit> units = this->units;
    while (!units.empty()) {
        array[units.front().point.x][units.front().point.y] = units.front().get_number();
        units.pop();
    }

    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void World::dump_for_units() {
    int gridWidth = this->units.front().get_static_potential().get_grid_width();
    int gridHeight = this->units.front().get_static_potential().get_grid_height();
    int array[gridWidth][gridHeight] = {};
    int unitsNum = this->units.size();
    for (int s = 0; s < unitsNum; s++) {
        Unit unit = this->units.front();
        this->units.pop();
        for (int i = 0; i < gridWidth; i++) {
            for (int j = 0; j < gridHeight; j++) {
                array[i][j] = this->point_potential(i, j, unit);
                std::cout << array[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
        this->units.push(unit);
    }
}

void World::move_units() {
    int gridWidth = this->units.front().get_static_potential().get_grid_width();
    int gridHeight = this->units.front().get_static_potential().get_grid_height();
    int unitsNum = this->units.size();
    int mashinesSolved = 0;
    for (int s = 0; s < unitsNum; s++) {
        Unit unit = this->units.front();
        if (unit.endPoint.x == unit.point.x && unit.endPoint.y == unit.point.y)
        {
            this->units.pop();
            this->units.push(unit);
            mashinesSolved++;
            continue;
        }
        this->units.pop();

        float currentPosPotential   = -10000;
        float leftPosPotential      = -10000;
        float rightPosPotential     = -10000;
        float topPosPotential       = -10000;
        float bottomPosPotential    = -10000;

        currentPosPotential = this->point_potential(unit.point.x,
                                                   unit.point.y,
                                                   unit) + rand()%100 * 0.0000001;
        if (unit.point.x != 0) {
            leftPosPotential = this->point_potential(unit.point.x - 1,
                                                     unit.point.y,
                                                     unit) + rand()%100 * 0.0000001;
        }
        if (unit.point.x != gridWidth - 1) {
            rightPosPotential = this->point_potential(unit.point.x + 1,
                                                     unit.point.y,
                                                     unit) + rand()%100 * 0.0000001;
        }
        if (unit.point.y != 0) {
            topPosPotential = this->point_potential(unit.point.x,
                                                     unit.point.y - 1,
                                                     unit) + rand()%100 * 0.0000001;
        }
        if (unit.point.y != gridHeight - 1) {
            bottomPosPotential = this->point_potential(unit.point.x,
                                                     unit.point.y + 1,
                                                     unit) + rand()%100 * 0.0000001;
        }
        if (currentPosPotential == std::max({
                                            currentPosPotential,
                                            leftPosPotential,
                                            rightPosPotential,
                                            topPosPotential,
                                            bottomPosPotential})) {
            unit.pheromones.pop();
            unit.pheromones.push(Point(unit.point.x, unit.point.y));
        }else if (leftPosPotential == std::max({
                                                  currentPosPotential,
                                                  leftPosPotential,
                                                  rightPosPotential,
                                                  topPosPotential,
                                                  bottomPosPotential})) {
            unit.point.x -= 1;
            unit.pheromones.pop();
            unit.pheromones.push(Point(unit.point.x, unit.point.y));
        }else if (rightPosPotential == std::max({
                                                   currentPosPotential,
                                                   leftPosPotential,
                                                   rightPosPotential,
                                                   topPosPotential,
                                                   bottomPosPotential})) {
            unit.point.x += 1;
            unit.pheromones.pop();
            unit.pheromones.push(Point(unit.point.x, unit.point.y));
         }else if (topPosPotential == std::max({
                                                   currentPosPotential,
                                                   leftPosPotential,
                                                   rightPosPotential,
                                                   topPosPotential,
                                                   bottomPosPotential})) {
            unit.point.y -= 1;
            unit.pheromones.pop();
            unit.pheromones.push(Point(unit.point.x, unit.point.y));
         }else if (bottomPosPotential == std::max({
                                                   currentPosPotential,
                                                   leftPosPotential,
                                                   rightPosPotential,
                                                   topPosPotential,
                                                   bottomPosPotential})) {
            unit.point.y += 1;
            unit.pheromones.pop();
            unit.pheromones.push(Point(unit.point.x, unit.point.y));
        }else {
            perror("uncnown command");
        }

        this->units.push(unit);
    }
    this->mashinesSolved = mashinesSolved;
}

int World::check_solved() {
    if (this->mashinesSolved == (int) this->units.size()) {
        return 1;
    }
    return 0;
}

