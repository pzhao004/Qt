#include "manageclasses.h"


ManageClasses::ManageClasses(QGuiApplication &app, QQmlApplicationEngine &engine)
{
    m_app= &app;
    m_engine= &engine;
}

void ManageClasses::init(){

    QQmlContext * rootContext = m_engine->rootContext();
    rootContext->setContextProperty("phdata",&phdata);
}

void ManageClasses::signalsConnections(){
    QObject * root=NULL;
    QList<QObject*> rootObjects = m_engine->rootObjects();
    int count = rootObjects.size();
    for(int i =0; i< count;i++){
        if(rootObjects.at(i)->objectName()=="rootObject"){
            root=rootObjects.at(i);
            break;
        }
    }

    QObject::connect(root,SIGNAL(sendStartEvent()),&phdata,SLOT(handleBtnEvent()));
}

