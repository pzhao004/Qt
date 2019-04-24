/*!
*@file main.cpp.
*@brief implement the  interfaces.
*@version 1.0.
*@author zhao albert.
*/
#include "configuration.h"
#ifdef linux
#define CONFIGURE_PATH "/workspace/tableviewqml/configuration/configure.txt"
#endif
#define CONFIGURE_PATH "/workspace/tableviewqml/configuration/configure.txt"

Configuration::Configuration(QObject *parent) : QObject (parent)
{

}

int Configuration::mainScreenWidth() const{
    return m_MainScreenWidth;
}
int Configuration::mainScreenHeight() const{
    return m_MainScreenHeight;
}
void Configuration::readLine(){
    QFile file(CONFIGURE_PATH);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        while(!file.atEnd()){
            QByteArray line = file.readLine();
            QString str(line);
            if(str != "\n"){
                str =str.trimmed();
                int index = str.lastIndexOf(":");
                if(str.mid(0,index) == "main_screen_width"){
                    m_MainScreenWidth = str.mid(index + 1).toInt();
                }else if(str.mid(0,index) == "main_screen_height"){
                    m_MainScreenHeight = str.mid(index + 1).toInt();
                }
            }
        }
        file.close();
        emit mainScreenWidthChanged();
        emit mainScreenHeightChanged();
    }else {
        qDebug() << "Configure File Is Not Found..." << QCoreApplication::applicationDirPath();
    }
}
