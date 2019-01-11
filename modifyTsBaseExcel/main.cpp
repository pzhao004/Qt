#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "excel2ts.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    excel2ts excel2tsOjbect;
    excel2tsOjbect.getWrokSheet("C:/111/sss.xlsx");
    excel2tsOjbect.operateXml();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
