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
    Q_PROPERTY(QString curr1Str READ curr1Str NOTIFY curr1StrChanged)
    Q_PROPERTY(QString curr2Str READ curr2Str NOTIFY curr2StrChanged)
    Q_PROPERTY(QString obName READ obName NOTIFY obNameChanged)
    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(QString currIM READ currIM  NOTIFY currIMChanged)
    Q_PROPERTY(QString nextIM READ nextIM NOTIFY nextIMChanged)
public:
    explicit KBContext(QObject *parent=nullptr);
    virtual ~KBContext();

    void setOwner(QQmlApplicationEngine &engine);
    void getTextInputFocus();
    QString curr1Str() const;
    QString curr2Str() const;
    QString obName() const;
    bool active() const;
    QString currIM() const;
    QString nextIM() const;

signals:
    void curr1StrChanged(const QString &c);
    void curr2StrChanged(const QString &c);
    void obNameChanged(const QString &o);
    void activeChanged();
    void currIMChanged(const QString &c);
    void nextIMChanged(const QString &n);

public slots:
    void doInput(const QString &objectName);
    void toggleIM();
    void sendKeyVal(const int i);
    void sendKeyChar(const QChar q);

private:
    void updateKeyBoard();
    QStringList m_listIMs;
    int               m_idxIM;
    bool            m_active;
    QString      m_objectName;
    QString       m_curr1Str;
    QString       m_curr2Str;
    KeyboardModel              *  m_keyboardmodel;
    QQmlApplicationEngine * m_engine;
    QObject * m_textInputFocus;
};

#endif // KBCONTEXT_H
