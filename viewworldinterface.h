#ifndef VIEWWORLDINTERFACE_H
#define VIEWWORLDINTERFACE_H

#include "world.h"
#include <QObject>
#include "string"


class ViewWorldInterface : public QObject
{
    Q_OBJECT
private:
    int map[100][100] = {};
    std::string colors[7] = {
        "black",
        "red",
        "white",
        "yellow",
        "blue",
        "lightgrey",
        "darkblue",
        //7 elems
    };
public:
    World world;
    ViewWorldInterface();
    Q_INVOKABLE void read_drone_info(QString filepath);
    Q_INVOKABLE void make_one_step();
    Q_INVOKABLE int get_map_point(int x, int y);
    Q_INVOKABLE QString get_color(int number);
    Q_INVOKABLE void dump();
};

#endif // VIEWWORLDINTERFACE_H
