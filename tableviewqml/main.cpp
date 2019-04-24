/*!
*@file main.cpp
*@brief main function, it is the GUI Application entrance.
*@version 1.0
*@author zhao albert.
*/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "tngmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Configuration cfg;
    TableViewModel tvm;
    TngManager tmg(app,engine,cfg,tvm);
    tmg.initialObjects();
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
