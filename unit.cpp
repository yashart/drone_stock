#include "unit.h"

Unit::Unit(int x, int y, float potential, int number)
{
    this->point = Point(x, y);
    this->endPoint = Point(-1, -1);
    this->potential = potential;
    this->machineNumber = number;

    this->pheromones.push(Point(x, y));
    this->pheromones.push(Point(x, y));
    this->pheromones.push(Point(x, y));
    this->pheromones.push(Point(x, y));
    this->pheromones.push(Point(x, y));
}

void Unit::set_path(int x, int y) {
    this->static_potential.distribute_potential(x, y, 9);
    this->endPoint = Point(x, y);
}

Grid Unit::get_static_potential() {
    return this->static_potential;
}

int Unit::get_number() {
    return this->machineNumber;
}
