#ifndef DESIGNBLL_H
#define DESIGNBLL_H

#include <QObject>
#include <QDebug>
#include <QQmlContext>
#include "designdatamodel.h"

class DesignBLL : public QObject
{
    Q_OBJECT
public:
    DesignBLL();
    Q_INVOKABLE QList<QObject *> getData();
    void deleteChar(const int index);
    void deleteChar2(const int index);
    void addChar(const int index,const QChar q);
    void addChar2(const int index,const QChar q);
    void changeFocus(const int index);

private:
    QList<QString>     datalist; //
    QList<QObject *> datamodel; //
};

#endif // DESIGNBLL_H
