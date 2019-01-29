#include "designdatamodel.h"

DesignDataModel::DesignDataModel(
        const QString str,
        const QString str2,
        const bool textFocus,
        QObject *parent): QObject(parent)
{
    m_str=str;
    m_str2=str2;
    m_textFocus=textFocus;
}
QString DesignDataModel::str() const
{
    return m_str;
}

void DesignDataModel::setStr(const QString str){
    m_str=str;
    emit strChanged();
}
QString DesignDataModel::str2() const
{
    return m_str2;
}

void DesignDataModel::setStr2(const QString str2){
    m_str2=str2;
    emit str2Changed();
}

bool DesignDataModel::textFocus() const
{
    return m_textFocus;
}

void DesignDataModel::setTextFocus(const bool &textFocus){
    m_textFocus=textFocus;
    emit textFocusChanged();
}

