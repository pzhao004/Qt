#include "designbll.h"

DesignBLL::DesignBLL()
{
    QList<QString> list;
    list << "one" << "two" << "three" << "four" << "five" << "six"  << "seven" << "eight" << "nine" << "ten" <<"eleven"<< "twerf"<< "thirteen" << "foutheen"<< "fitheen";
    for(int i =0;i<list.length();i++){
        datalist.append(list.at(i));
    }

    for(int s =0; s <5; s++){
        datamodel.append(new DesignDataModel(
                                                    list.at(s),
                                                    list.at(s+5),
                                                    false)
                                     );
    }
}

QList<QObject *> DesignBLL::getData(){
    return datamodel;
}

void DesignBLL::deleteChar(const int index){
    qDebug() << "Text Field index is =" << index;
    QObject *obj=datamodel[index];
    if(obj != nullptr){
        QString currS =obj->property("str").QVariant::toString() ;
        currS.truncate(currS.length()-1);
        qDebug() << "object is not null..." << currS;
        obj->setProperty("str",QVariant::fromValue(QString(currS)));
    }else{
        qDebug() << "object is null...";
    }
}
void DesignBLL::deleteChar2(const int index){
    qDebug() << "Text Field index is =" << index;
    QObject *obj=datamodel[index];
    if(obj != nullptr){
        QString currS =obj->property("str2").QVariant::toString() ;
        currS.truncate(currS.length()-1);
        qDebug() << "object is not null..." << currS;
        obj->setProperty("str2",QVariant::fromValue(QString(currS)));
    }else{
        qDebug() << "object is null...";
    }
}
void DesignBLL::addChar(const int index,const QChar q){
    qDebug() << "Text Field index is =" << index << q;
    QObject *obj=datamodel[index];
    if(obj != nullptr){
        QString currS =obj->property("str").QVariant::toString() ;
        currS.append(q);
        qDebug() << "object is not null..." << currS;
        obj->setProperty("str",QVariant::fromValue(QString(currS)));
    }else{
        qDebug() << "object is null...";
    }
}
void DesignBLL::addChar2(const int index,const QChar q){
    qDebug() << "Text Field index is =" << index << q;
    QObject *obj=datamodel[index];
    if(obj != nullptr){
        QString currS =obj->property("str2").QVariant::toString() ;
        currS.append(q);
        qDebug() << "object is not null..." << currS;
        obj->setProperty("str2",QVariant::fromValue(QString(currS)));
    }else{
        qDebug() << "object is null...";
    }
}
void DesignBLL::changeFocus(const int index){
    qDebug() << "Text Field index is :" << index;
    QObject *obj=datamodel[index];
    if(obj != nullptr){
        qDebug() << "object is not null...";
        obj->setProperty("textFocus",QVariant::fromValue(bool(false)));
    }else{
        qDebug() << "object is null...";
    }
}
