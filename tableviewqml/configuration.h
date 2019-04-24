/*!
*@file main.cpp.
*@brief define interface to read the configure.txt for getting the configurations.
*@version 1.0.
*@author zhao albert.
*/
#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QFile>
#include <QObject>
#include <QDebug>
#include <QCoreApplication>

class Configuration : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int mainScreenWidth READ mainScreenWidth NOTIFY mainScreenWidthChanged)
    Q_PROPERTY(int mainScreenHeight READ mainScreenHeight NOTIFY mainScreenHeightChanged)
public:
    explicit Configuration(QObject * parent=nullptr);

    int mainScreenWidth() const;
    int mainScreenHeight() const;
    void readLine();

signals:
    void mainScreenWidthChanged();
    void mainScreenHeightChanged();

private:
    int m_MainScreenWidth;
    int m_MainScreenHeight;
};

#endif // CONFIGURATION_H
