#ifndef KEYBOARDMODEL_H
#define KEYBOARDMODEL_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QAbstractListModel>
#include <QVector>
#include <QStringList>
#include <QXmlStreamReader>
class MyKey {
    public:
        void printOut();
        bool isEmtpy;
        bool isIcon;
        bool isFunc;
        int span;
        QString keyColor;
        QString pic;
        QString text;
        QString seq;
        QString func;
};

class KeyboardModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int keyRows READ keyRows NOTIFY keyRowsChanged)
    Q_PROPERTY(int rowCells READ rowCells NOTIFY rowCellsChanged)
    Q_PROPERTY(int keySpacing READ keySpacing NOTIFY keySpacingChanged)
    Q_PROPERTY(QString currKbd READ currKbd NOTIFY currKbdChanged)
    Q_PROPERTY(bool isCaps READ isCaps NOTIFY isCapsChanged)
    Q_PROPERTY(QString currString READ currString WRITE setCurrString NOTIFY currStringChanged)
    Q_PROPERTY(QString inputMode READ inputMode WRITE setInputMode NOTIFY inputModeChanged)
public:
    enum {
        FIELD_ISEMPTY = Qt::UserRole + 1,
        FIELD_ISICON,
        FIELD_ISFUNC,
        FIELD_KEYCOLOR,
        FIELD_PIC,
        FIELD_TXT,
        FIELD_SPAN,
        FIELD_MAX
    };
    explicit KeyboardModel(QObject *parent = nullptr);
    virtual ~KeyboardModel();

    void loadKbd(const QString& kbdFile);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    //related the button key of virtual keyboard.
    int keyRows() const;
    int rowCells() const;
    int keySpacing() const;
    QString currKbd() const;
    QString currString() const;
    QString inputMode() const;
    bool isCaps() const;

signals:
    void keyRowsChanged(int kr);
    void rowCellsChanged(int rc);
    void keySpacingChanged(int ks);
    void currKbdChanged(const QString& ck);
    void currStringChanged(const QString& currStr);
    void inputModeChanged(const QString& im);
    void isCapsChanged(const bool isCaps);
    void enterKeyVal(int keyVal);
    void enterKeyChar(QChar c);

public slots:
    void setCurrString(const QString& currStr);
    void setInputMode(const QString &im);
    void keyRelease(int keyIndex);
    void handleInputChar(const QString &c,bool bCase);
private:
    void readKeyboard(QXmlStreamReader *pXmlReader);
    void readKey(QXmlStreamReader* pXmlReader);
    QString kbdPath();
    QString formatKeyText(MyKey* pKey) const;

    QHash<int, QByteArray> m_roles;
    QVector<MyKey*> m_vecKeys;
    int           m_keyCount;
    int           m_keyRows;
    int           m_rowCells;
    int           m_keySpacing;
    QString   m_kbdName;
    QString   m_currKbdFile;
    QString   m_currString;
    QString   m_inputMode;
    bool        m_isCapsLock;
    bool        m_isShift;
};

#endif // KEYBOARDMODEL_H
