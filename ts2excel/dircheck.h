#ifndef DIRCHECK_H
#define DIRCHECK_H

#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QFileInfo>
#include <QAxObject>
#include <QFileDialog>
#include <QXmlStreamReader>

class DirCheck
{
public:
    DirCheck();

    QDir * getDirObject(QString dirpath);
    QList<QFileInfo>* getTargetTsFilesListInfo();
    void parseXMLfile();
    void xml2excel();
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
};

#endif // DIRCHECK_H
