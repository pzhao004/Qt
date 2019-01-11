#ifndef EXCEL2TS_H
#define EXCEL2TS_H

#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QFileInfo>
#include <QAxObject>
#include <QFileDialog>
#include <QXmlStreamReader>

class excel2ts
{
public:
    excel2ts();

    QAxObject * getWrokSheet(QString absuExcelPath);
    bool operateXml();
    //void compareXMLandExcel(QString pst,int number);
private:
    QAxObject *excel;
    QAxObject *workbook;
    QAxObject *s_worksheet;
    QAxObject *range;
    QXmlStreamReader reader;
};

#endif // EXCEL2TS_H
