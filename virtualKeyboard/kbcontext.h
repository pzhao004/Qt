#ifndef KBCONTEXT_H
#define KBCONTEXT_H

#include <QObject>
#include <QDebug>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "keyboardmodel.h"

class KBContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currStr READ currStr NOTIFY currStrChanged)
    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
public:
    explicit KBContext(QObject *parent=nullptr);
    virtual ~KBContext();

    void setOwner(QQmlApplicationEngine &engine);
    QString currStr() const;
    bool active() const;

signals:
    void currStrChanged(const QString& c);
    void activeChanged();

public slots:
    void doInput(const QString &initStr);

private:
    void updateKeyBoard();
    QStringList m_listIMs;
    int               m_idxIM;
    bool            m_active;
    QString       m_currStr;
    KeyboardModel              *  m_keyboardmodel;
    QQmlApplicationEngine * m_engine;
};

#endif // KBCONTEXT_H
