#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "dircheck.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    DirCheck dircheck;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("TS2EXCEL",&dircheck);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
