#ifndef DESIGNDATAMODEL_H
#define DESIGNDATAMODEL_H
#include <QObject>
#include <QVariant>

class DesignDataModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString str READ str WRITE setStr NOTIFY strChanged)
    Q_PROPERTY(QString str2 READ str2 WRITE setStr2 NOTIFY str2Changed)
    Q_PROPERTY(bool textFocus READ textFocus WRITE setTextFocus NOTIFY textFocusChanged)
public:
    DesignDataModel(const QString str,
                    const QString str2,
                    const bool textFocus,
                    QObject *parent=nullptr
            );

    QString str() const;
    void setStr(const  QString str);
    QString str2() const;
    void setStr2(const  QString str);

    bool textFocus() const;
    void setTextFocus(const bool &textFocus);

signals:
    void strChanged();
    void str2Changed();
    void textFocusChanged();

private:
    QString m_str;
    QString m_str2;
    bool m_textFocus;
};

#endif // DESIGNDATAMODEL_H
