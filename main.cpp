#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "world.h"
#include "viewworldinterface.h"
#include <iostream>

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    ViewWorldInterface worldInterface;
    worldInterface.read_drone_info("top_by_top.txt");

    QQmlApplicationEngine engine;
    QQmlContext * ctx = engine.rootContext();

    /* //top by top
    for (int i = 0; i < 100; i++)
    {
        std::cout << 0 << " " << i << " " << 99 << " " << i << " " << i + 1 << std::endl;
        std::cout << 99 << " " << i << " " << 0 << " " << i << " " << i + 101 << std::endl;
    }
    */
     //corners
    /*
    for (int i = 1; i < 99; i++) {
        std::cout << 0 << " " << i << " " << 99 << " " << i << " " << i + 1 << std::endl;
        std::cout << 99 << " " << i << " " << 0 << " " << i << " " << i + 101 << std::endl;
    }
    for (int i = 1; i < 99; i++) {
        std::cout << i << " " << 0 << " " << i << " " << 99 << " " << i + 201 << std::endl;
        std::cout << i << " " << 99 << " " << i << " " << 0 << " " << i + 301 << std::endl;
    }
    */


    ctx->setContextProperty("worldInterface", &worldInterface);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
