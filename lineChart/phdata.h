#ifndef PHDATA_H
#define PHDATA_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QCoreApplication>
#include <QApplication>

class PHData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int phValue READ getPhValue WRITE setPhValue NOTIFY phValueChanged)
    Q_PROPERTY(int timeValue READ getTimeValue WRITE setTimeValue NOTIFY timeValueChanged)
    Q_PROPERTY(bool endtag READ getEndtag WRITE setEndtag NOTIFY endtagChanged)
public:
    PHData();
    int getPhValue();
    void setPhValue(const int phValue);
    int getTimeValue();
    void setTimeValue(const int timeValue);
    bool getEndtag();
    void setEndtag(const bool endtag);

signals:
    void phValueChanged();
    void timeValueChanged();
    void endtagChanged();

public slots:
    void handleBtnEvent();

private:
    int m_phvalue;
    int m_timeValue;
    bool m_endtag;
};

#endif // PHDATA_H
