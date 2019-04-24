/*!
*@file main.cpp.
*@brief manage all module objects.
*@version 1.0.
*@author zhao albert.
*/
#ifndef TNGMANAGER_H
#define TNGMANAGER_H

#include <QObject>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "configuration.h"
#include "tableviewmodel.h"

class TngManager : public QObject
{
public:
    TngManager(QGuiApplication &app, QQmlApplicationEngine &engine, Configuration &cfg,
                          TableViewModel &tvm);

    void initialObjects();
    void registerObjectsIntoQml();
private:
    QGuiApplication *m_app;
    QQmlApplicationEngine *m_engine;
    Configuration *m_cfg;
    TableViewModel *m_tvm;
};

#endif // TNGMANAGER_H
