#include "phdata.h"

PHData::PHData()
{
    m_phvalue=0;
    m_timeValue=0;
    m_endtag=true;
}

int PHData::getPhValue(){
    return m_phvalue;
}

void PHData::setPhValue(const int phValue){
    m_phvalue=phValue;
}

int PHData::getTimeValue(){
    return m_timeValue;
}

void PHData::setTimeValue(const int timeValue){
    m_timeValue=timeValue;
}

bool PHData::getEndtag(){
    return m_endtag;
}

void PHData::setEndtag(const bool endtag){
    m_endtag=endtag;
}

void PHData::handleBtnEvent(){
    for(int i=1;i<1000;i++){
        this->setPhValue(qrand()%50);
        this->setTimeValue(i*10);
        emit phValueChanged();
        emit timeValueChanged();
        this->setEndtag(false);
        emit endtagChanged();
        QThread::msleep(1000);

        //QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
