#ifndef DIRCHECK_H
#define DIRCHECK_H

#include <QFile>
#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QFileInfo>
#include <QAxObject>
#include <QFileDialog>
#include <QXmlStreamReader>

class DirCheck : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
public:
    DirCheck();

    QDir * getDirObject(QString dirpath);
    QList<QFileInfo>* getTargetTsFilesListInfo();
    void parseXMLfile();

    QString message() const;
    void setMessage(const QString msg);

    Q_INVOKABLE void xml2excel();
    Q_INVOKABLE void test();
    Q_INVOKABLE QString getDestationDirector(QString destDire);
    Q_INVOKABLE QString getResourceDirector(QString resoDire);
signals:
    void messageChanged();
private:
    QList<QFileInfo> *fileinfo;
    QDir *dir;
    QDir *dir_excel;
    QAxObject *m_worksheet;
    QAxObject *excel;
    QAxObject *workbook;
    QXmlStreamReader reader;
    void readContextlMembers(QString pst,int number);
    void readXmlFile(const QString &fileName);
    QAxObject * getWorkSheet(QString absuExcelPath);
    QString createFile(QString filePath,QString fileName);
    QString m_destDirector;
    QString m_resoDirector;
    QString m_message;
};

#endif // DIRCHECK_H
