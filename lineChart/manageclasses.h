#ifndef MANAGECLASSES_H
#define MANAGECLASSES_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QDebug>
#include "phdata.h"

class ManageClasses : public QObject
{
    Q_OBJECT
public:
    ManageClasses(QGuiApplication &app,QQmlApplicationEngine &engine);
    void init();
    void signalsConnections();

private:
    QGuiApplication *m_app;
    QQmlApplicationEngine *m_engine;
    PHData phdata;
};

#endif // MANAGECLASSES_H
