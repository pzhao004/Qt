#include "manageclasses.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    //initialize
    ManageClasses manageclass(app,engine);
    manageclass.init();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    //Connect signals
    manageclass.signalsConnections();
    return app.exec();
}
