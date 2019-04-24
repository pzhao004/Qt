#include "tngmanager.h"
#include "sortfilterproxymodel.h"
TngManager::TngManager(QGuiApplication &app, QQmlApplicationEngine &engine,
                       Configuration &cfg, TableViewModel &tvm)
{
    qmlRegisterType<SortFilterProxyModel>("SFPM", 1 ,0, "SortFilterProxyModel");
    m_app = &app;
    m_engine = &engine;
    m_cfg = &cfg;
    m_tvm = &tvm;
}
void TngManager::initialObjects(){
    m_cfg->readLine();
    m_tvm->initialDatas();
    registerObjectsIntoQml();
}
void TngManager::registerObjectsIntoQml(){
    m_engine->rootContext()->setContextProperty("MANAGE", this);
    m_engine->rootContext()->setContextProperty("CONFIG", m_cfg);
    m_engine->rootContext()->setContextProperty("TABLEMODEL", m_tvm);
}

