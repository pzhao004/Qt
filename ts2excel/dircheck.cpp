#include "dircheck.h"

DirCheck::DirCheck()
{

}
void DirCheck::xml2excel(){
    QString filePath = "/111/";
    QString fileName = "sss.xlsx";
    QString absuExcelPath=createFile(filePath,fileName);
    m_worksheet=getWorkSheet(absuExcelPath);
    getDirObject("../ts2excel/language");
    getTargetTsFilesListInfo();
    parseXMLfile();
}

QDir * DirCheck::getDirObject(QString dirpath){
    QDir directory(dirpath);
    if(directory.exists()==false){
        printf("the target directory is not correct.\n");
    }
    dir=new QDir(directory);
    return dir;
}

QList<QFileInfo>* DirCheck::getTargetTsFilesListInfo(){
    QStringList filter;
    filter << "*.ts";
    dir->setNameFilters(filter);
    fileinfo = new QList<QFileInfo>(dir->entryInfoList(filter));
    return fileinfo;
}

void DirCheck::parseXMLfile(){
    int count = fileinfo->count();
    if(count==0){
        qDebug() << "target ts files are not exist!";
    }
    else{
        for(int i=0;i<count;i++){
            QString ts_file_path = dir->absoluteFilePath(fileinfo->at(i).fileName());
            qDebug() <<"parseXMLfile:" + ts_file_path;
            readXmlFile(ts_file_path);
        }
        workbook->dynamicCall("Save()");
        workbook->dynamicCall("Close()");
        excel->dynamicCall("Quit()");
        if (excel)
        {
           delete excel;
           excel = NULL;
        }
    }
}

void DirCheck::readXmlFile(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "can't open the the file:" + fileName;
    }
    reader.setDevice(&file);
    reader.readNext();
    while (!reader.atEnd())
    {
        if (reader.isStartElement()){
            if (reader.name() == "TS"){
                int numb=2;
                if(reader.attributes().value("language")=="en_AS"){
                   QAxObject *range2 = m_worksheet->querySubObject("Range(QString)", "A1");
                   range2->setProperty("Value", "English");
                   readContextlMembers("A",numb);
                }else if(reader.attributes().value("language")=="zh_CN"){
                    QAxObject *range2 = m_worksheet->querySubObject("Range(QString)", "B1");
                    range2->setProperty("Value", "Chinese");
                    readContextlMembers("B",numb);
                }else if(reader.attributes().value("language")=="ja_JP"){
                    QAxObject *range2 = m_worksheet->querySubObject("Range(QString)", "C1");
                    range2->setProperty("Value", "Japanse");
                    readContextlMembers("C",numb);
                }
            }else{
                reader.raiseError(QObject::tr("Not a language file"));
            }
        }else{
            reader.readNext();
        }
    }
    file.close();
}

void DirCheck::readContextlMembers(QString pst,int number){
    QString pstionInsert = QString::number(number,'f',0);
    pstionInsert = pst+pstionInsert;
    reader.readNext();
    while (!reader.atEnd())
    {
        if (reader.isEndElement())
        {
            reader.readNext();
        }
        if (reader.isStartElement()){
            if (reader.name() == "translation"){
                QAxObject *range = m_worksheet->querySubObject("Range(QString)", pstionInsert);
                range->setProperty("Value", reader.readElementText());
                number++;
            }else{
                readContextlMembers(pst,number);
            }
        }else{
            reader.readNext();
        }
    }
}

QString DirCheck::createFile(QString filePath,QString fileName)
{
    QDir tempDir;
    QString currentDir = tempDir.currentPath();
    if(!tempDir.exists(filePath))
    {
        qDebug()<<"doesn't exist this path.";
        tempDir.mkpath(filePath);
    }else{
        qDebug() << "tartget directory already exist.";
    }
    QFile *tempFile = new QFile;
    tempDir.setCurrent(filePath);
    if(tempFile->exists(fileName))
    {
        qDebug()<<QObject::tr("file has already existed.");
    }else{
        fileName = tempDir.currentPath()+"/"+fileName;
        QAxObject _excel("Excel.Application");
        _excel.setProperty("Visiblie", false);
        QAxObject *_workbooks = _excel.querySubObject("WorkBooks");
        _workbooks->dynamicCall("Add");
        QAxObject *_workbook = _excel.querySubObject("ActiveWorkBook");
        _workbook->dynamicCall("SaveAs(const QString &)",QDir::toNativeSeparators(fileName));
        _workbook->dynamicCall("Close (Boolean)", false);
        _excel.dynamicCall("Quit (void)");
    }
    QString excelpath=tempDir.absoluteFilePath(fileName);
    //set the path to origin path
    tempDir.setCurrent(currentDir);
    return excelpath;
}
QAxObject * DirCheck::getWorkSheet(QString absuExcelPath){
    excel=new QAxObject();
    excel->setControl("Excel.Application");
    excel->dynamicCall("SetVisible(bool Visible)","false");
    excel->setProperty("DisplayAlerts",false);
    QAxObject *workbooks = excel->querySubObject("WorkBooks");
    //excel_file_path need to use the absuote path.
    qDebug() << "getWorkSheet: " + absuExcelPath;
    workbook = workbooks->querySubObject("Open(const QString&)",absuExcelPath);
    QAxObject * worksheets = workbook->querySubObject("WorkSheets");
    int iWorkSheet = worksheets->property("Count").toInt();
    qDebug() << QString("the number of the worksheet of the excel: %1").arg(QString::number(iWorkSheet));
    QAxObject * worksheet = worksheets->querySubObject("Item(int)", 1);//get first worksheet.
    return worksheet;
}
