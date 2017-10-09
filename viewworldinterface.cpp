#include "viewworldinterface.h"
#include "QFile"
#include "QTextStream"
#include <fstream>
#include "string"


ViewWorldInterface::ViewWorldInterface()
{

}

void ViewWorldInterface::read_drone_info(QString filepath) {
    while (!this->world.units.empty()) {
        this->world.units.pop();
    }
    std::ifstream infile(filepath.toStdString());
    int startX;
    int startY;
    int endX;
    int endY;
    int number;
    while (infile >> startX >> startY >> endX >> endY >> number) {
        this->world.add_unit(startX, startY, endX, endY, number);
    }
}

void ViewWorldInterface::make_one_step() {
    int gridWidth = this->world.units.front().get_static_potential().get_grid_width();
    int gridHeight = this->world.units.front().get_static_potential().get_grid_height();
    std::queue<Unit> units = this->world.units;
    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            this->map[i][j] = 0;
        }
    }
    while (!units.empty()) {
        this->map[units.front().point.x][units.front().point.y] = units.front().get_number();
        units.pop();
    }
    this->world.move_units();
}

int ViewWorldInterface::get_map_point(int x, int y) {
    return this->map[x][y];
}

QString ViewWorldInterface::get_color(int number) {
    return QString::fromStdString(this->colors[number % 7]);
}

void ViewWorldInterface::dump() {
    return this->world.dump();
}

